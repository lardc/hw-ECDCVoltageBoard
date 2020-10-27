// Header
#include <stdlib.h>
#include "Controller.h"
//
// Includes
#include "BCCIxParams.h"
#include "Board.h"
#include "VoltageBoard.h"
#include "Delay.h"
#include "DeviceProfile.h"
#include "Interrupts.h"
#include "Global.h"
#include "LowLevel.h"
#include "SysConfig.h"
#include "DebugActions.h"
#include "Diagnostic.h"
#include "Constraints.h"
#include "Measurement.h"

#define sign(x) ((x)<0 ? -(1) : (1))

#define EP_IMEASURE	1
#define EP_VMEASURE	2
#define EP_VERROR	3
#define EP_IERROR	4

// Types
//
typedef void (*FUNC_AsyncDelegate)();
// Storage
volatile Int16U CONTROL_IMeasure[EP_SIZE] = {0};
volatile Int16U CONTROL_VMeasure[EP_SIZE] = {0};
volatile Int16U CONTROL_Setpoint[EP_SIZE] = {0};
volatile Int16U CONTROL_Control[EP_SIZE] = {0};
volatile Int16U CONTROL_RawControl[EP_SIZE] = {0};
volatile Int16U CONTROL_Counter = 0;

// Variables
//
volatile DeviceState CONTROL_State = DS_None;
volatile DeviceSubState CONTROL_SubState = SS_None;
static Boolean CycleActive = false;
static ControllerConfig Config;
volatile Int64U CONTROL_TimeCounter = 0;

// Forward functions
//
static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
void CONTROL_SetDeviceState(DeviceState NewState, DeviceSubState NewSubState);
void CONTROL_SwitchToFault(Int16U Reason);
void CONTROL_UpdateWatchDog();
void CONTROL_ResetEPRegisters();
void CONTROL_ResetToDefaultState();
void CONTROL_ResetHardware();
void CONTROL_PulseControl();

// Functions
//
void CONTROL_EpLog(float Current, float Voltage, float Setpoint, float Control, uint16_t RawControl)
{
	static uint16_t ScopeLogStep = 0, LocalCounter = 0;
	float ControlScale = 1;

	// Выбор масштаба для данных регулятора
	if((Config.CurrentHighRange && Config.OutputType == Current) ||
		(Config.VoltageHighRange && Config.OutputType == Voltage))
	{
		ControlScale = 0.001;
	}

	// Сброс локального счётчика в начале логгирования
	if(CONTROL_Counter == 0)
		LocalCounter = 0;

	if(ScopeLogStep++ >= DataTable[REG_SCOPE_RATE])
	{
		ScopeLogStep = 0;

		CONTROL_IMeasure[LocalCounter] = Current * (Config.CurrentHighRange) ? 0.001 : 1;
		CONTROL_VMeasure[LocalCounter] = Voltage * (Config.VoltageHighRange) ? 0.001 : 1;
		CONTROL_Setpoint[LocalCounter] = Setpoint * ControlScale;
		CONTROL_Control[LocalCounter] = Control * ControlScale;
		CONTROL_RawControl[LocalCounter] = RawControl;

		// Сохранение указателя на последний элемент
		DataTable[REG_EP_LAST_POINTER] = LocalCounter;
		++LocalCounter;
	}

	// Условие обновления глобального счётчика данных
	if(CONTROL_Counter < EP_SIZE)
		CONTROL_Counter = LocalCounter;

	// Сброс локального счётчика
	if(LocalCounter >= EP_SIZE)
		LocalCounter = 0;
}
// ----------------------------------------

void CONTROL_Init()
{
	// Переменные для конфигурации EndPoint
	Int16U EPIndexes[EP_COUNT] = {EP_I_MEASURE, EP_V_MEASURE, EP_SETPOINT, EP_CONTROL, EP_RAW_CONTROL};
	Int16U EPSized[EP_COUNT] = {EP_SIZE, EP_SIZE, EP_SIZE, EP_SIZE, EP_SIZE};
	// Сокращения
	pInt16U cc = (pInt16U)&CONTROL_Counter;
	pInt16U EPCounters[EP_COUNT] = {cc, cc, cc, cc, cc};
	pInt16U EPDatas[EP_COUNT] = {(pInt16U)CONTROL_IMeasure, (pInt16U)CONTROL_VMeasure, (pInt16U)CONTROL_Setpoint,
			(pInt16U)CONTROL_Control, (pInt16U)CONTROL_RawControl};

	// Конфигурация сервиса работы Data-table и EPROM
	EPROMServiceConfig EPROMService = {(FUNC_EPROM_WriteValues)&NFLASH_WriteDT, (FUNC_EPROM_ReadValues)&NFLASH_ReadDT};

	// Инициализация data table
	DT_Init(EPROMService, false);
	DT_SaveFirmwareInfo(CAN_SLAVE_NID, 0);

	// Инициализация device profile
	DEVPROFILE_Init(&CONTROL_DispatchAction, &CycleActive);
	DEVPROFILE_InitEPService(EPIndexes, EPSized, EPCounters, EPDatas);

	// Сброс значений
	DEVPROFILE_ResetControlSection();
	CONTROL_ResetToDefaultState();
}
//------------------------------------------

void CONTROL_ResetEPRegisters()
{
	DataTable[REG_FAULT_REASON] = DF_NONE;
	DataTable[REG_DISABLE_REASON] = DF_NONE;
	DataTable[REG_WARNING] = WARNING_NONE;
	DataTable[REG_PROBLEM] = PROBLEM_NONE;
	DataTable[REG_OP_RESULT] = OPRESULT_NONE;

	DataTable[DCV_REG_CURRENT_RESULT] = 0;
	DataTable[DCV_REG_CURRENT_RESULT_32] = 0;
	DataTable[DCV_REG_VOLTAGE_RESULT] = 0;
	DataTable[DCV_REG_VOLTAGE_RESULT_32] = 0;

	DEVPROFILE_ResetScopes(0);
	DEVPROFILE_ResetEPReadState();
}
//------------------------------------------

void CONTROL_ResetToDefaultState()
{
	CONTROL_ResetEPRegisters();
	CONTROL_ResetHardware();
	CONTROL_SetDeviceState(DS_None, SS_None);
}
//------------------------------------------

void CONTROL_ResetHardware()
{
	LL_WriteDACLV_Voltage(0);
	LL_WriteDACLV_Current(0);

	LL_WriteDACHV_Voltage(0);
	LL_WriteDACHV_Current(0);

	LL_SetStateExtLed(false);
	GPIO_SetState(GPIO_CS1, false);
	GPIO_SetState(GPIO_CS2, false);
	GPIO_SetState(GPIO_CS3, false);

	LL_SetStateCtrls(HP_CTRL_350V, true);
	LL_SetStateCtrls(EN_48V_CTRL, true);
}
//------------------------------------------

void CONTROL_Idle()
{
	DEVPROFILE_ProcessRequests();
	CONTROL_PulseControl();
	CONTROL_UpdateWatchDog();
}
//------------------------------------------

static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError)
{
	*pUserError = ERR_NONE;
	
	switch (ActionID)
	{
		case ACT_ENABLE_POWER:
			{
				if(CONTROL_State == DS_None)
					CONTROL_SetDeviceState(DS_Ready, SS_None);
				else if(CONTROL_State != DS_Ready)
					*pUserError = ERR_DEVICE_NOT_READY;
			}
			break;
			
		case ACT_DISABLE_POWER:
			{
				if(CONTROL_State == DS_Ready)
					CONTROL_ResetToDefaultState();
				else if(CONTROL_State != DS_None)
					*pUserError = ERR_OPERATION_BLOCKED;
			}
			break;
			
		case ACT_FAULT_CLEAR:
			{
				if(CONTROL_State == DS_Fault)
					CONTROL_ResetToDefaultState();
			}
			break;
			
		case ACT_WARNING_CLEAR:
			DataTable[REG_WARNING] = 0;
			break;
			
		case ACT_START_PROCESS:
			{
				if((CONTROL_State == DS_Ready) && (CONTROL_SubState == SS_None))
				{
					if(VB_CacheParameters(&Config))
					{
						CONTROL_ResetEPRegisters();
						CONTROL_SetDeviceState(DS_InProcess, SS_PulsePrepare);
						LL_SetStateExtLed(true);
					}
					else
						*pUserError = ERR_BAD_CONFIG;
				}
				else
					*pUserError = ERR_DEVICE_NOT_READY;
			}
			break;

		case ACT_STOP_PROCESS:
			{
				if(CONTROL_State == DS_InProcess)
				{
					//
				}
				else
					*pUserError = ERR_OPERATION_BLOCKED;
			}

		default:
			return DIAG_HandleDiagnosticAction(ActionID, pUserError);
			
	}
	return true;
}
//-----------------------------------------------

void CONTROL_SwitchToFault(Int16U Reason)
{
	CONTROL_SetDeviceState(DS_Fault, SS_None);
	DataTable[REG_FAULT_REASON] = Reason;
}
//------------------------------------------

void CONTROL_PulseControl()
{
	int16_t TempValue;
	int16_t VTempValue;
	int16_t ITempValue;
	int16_t VNewDac;
	int16_t INewDac;
	uint64_t Time;

	static uint64_t Timeout = 0;

	if(CONTROL_State == DS_InProcess)
	{
		switch (CONTROL_SubState)
		{
			case SS_PulsePrepare:
				{
					Timeout = CONTROL_TimeCounter + TIME_SWITCH_DELAY;
					VB_ConfigVIChannels(&Config);
					CONTROL_SetDeviceState(DS_InProcess, SS_PulseWaitSwitch);
				}
				break;

			case SS_PulseWaitSwitch:
				{
					if(CONTROL_TimeCounter > Timeout)
						CONTROL_SetDeviceState(DS_InProcess, SS_PulseProcess);
				}
				break;

			case SS_PulseProcess:
				{

				}
				break;

			case SS_PulseStart:
				{
					Config.StartTime = CONTROL_TimeCounter;
					switch (Config.WorkMode)
					{
						case WORK_MODE_VOLT:
							// отключено LL_WriteDAC_LH(Config.VDac);
							break;
						case WORK_MODE_CURR:
							// отключено LL_WriteDAC_LH(Config.CurrDac);
							break;
					}
					//CONTROL_SetDeviceSubState(SS_PulseProcess);
					Config.VError = 0;
					Config.IError = 0;
				}
				break;
			case SS_PulseProcess2:
				{
					//контроль длительности
					if(Config.PulseTime)
					{
						Time = CONTROL_TimeCounter;
						if(Time >= Config.StartTime)
						{
							Time -= Config.StartTime;
						}
						else
						{
							Time = Config.StartTime - Time;
						}
						if(Time >= Config.PulseTime)
						{

							//CONTROL_SetDeviceSubState(SS_PulseStop);
						}
					}
					//регулятор напряжения
					Config.VReal = MEASURE_Voltage();
					VTempValue = Config.VWant - Config.VReal;
					//масштабирование ошибки ADC->DAC
					VTempValue = (VTempValue * Config.VDacRegionSize) / Config.VAdcRegionSize;
					do
					{
						if(abs(VTempValue) > 4)
						{
							VTempValue /= 2;
							break;
						}
						if(abs(VTempValue) > 0)
						{
							VTempValue = sign(VTempValue);
							break;
						}
					}
					while(0);
					Config.VError += VTempValue;
					if(abs(Config.VError) > DAC_MAX_VALUE)
						Config.VError = sign(Config.VError) * DAC_MAX_VALUE;
					VNewDac = Config.VDac + Config.VError;
					//регулятор тока
					Config.CurrReal = MEASURE_Current();
					ITempValue = Config.CurrWant - Config.CurrReal;
					//масштабирование ошибки ADC->DAC
					ITempValue = (ITempValue * Config.VDacRegionSize) / Config.VAdcRegionSize;
					do
					{
						if(abs(ITempValue) > 4)
						{
							ITempValue /= 2;
							break;
						}
						if(abs(ITempValue) > 0)
						{
							ITempValue = sign(ITempValue);
							break;
						}
					}
					while(0);
					Config.IError += ITempValue;
					if(abs(Config.IError) > DAC_MAX_VALUE)
						Config.IError = sign(Config.IError) * DAC_MAX_VALUE;
					INewDac = Config.CurrDac + Config.IError;

					//ограничение по току или напряжению
					if(INewDac < VNewDac)
					{
						TempValue = INewDac;
						Config.VError -= VTempValue;
					}
					else
					{
						TempValue = VNewDac;
						Config.IError -= ITempValue;
					}

					if(TempValue < 0)
					{
						TempValue = 0;
					}
					if(TempValue > DAC_MAX_VALUE)
					{
						TempValue = DAC_MAX_VALUE;
					}

					//CONTROL_EpLog(Config.CurrReal, Config.IError, Config.VReal, Config.VError);
					// отключено  LL_WriteDAC_LH(TempValue);
				}
				break;

			case SS_PulseStop:
				{
					Config.CurrReal = MEASURE_Current();
					switch (Config.CurrChanel)
					{
						case CHANEL_LV_R1:
							Config.CurrMeas = (Config.CurrReal * IRANGE_R1_MAX) / DataTable[ADC_ILV_R1_TOP];
							break;
						case CHANEL_LV_R2:
							Config.CurrMeas = (Config.CurrReal * IRANGE_R2_MAX) / DataTable[ADC_ILV_R2_TOP];
							break;
						case CHANEL_LV_R3:
							Config.CurrMeas = (Config.CurrReal * IRANGE_R3_MAX) / DataTable[ADC_ILV_R3_TOP];
							break;
						case CHANEL_LV_R4:
							Config.CurrMeas = (Config.CurrReal * IRANGE_R4_MAX) / DataTable[ADC_ILV_R4_TOP];
							break;
					}
					Config.CurrMeas = Config.CurrReal;

					Config.VReal = MEASURE_Current();
					switch (Config.VChanel)
					{
						case CHANEL_V200:
							Config.VMeas = (Config.VReal * VRANGE_0V20_MAX) / DataTable[ADC_BLV_V200_TOP];
							break;
						case CHANEL_2V00:
							Config.VMeas = (Config.VReal * VRANGE_2V00_MAX) / DataTable[ADC_BLV_2V00_TOP];
							break;
						case CHANEL_20V0:
							Config.VMeas = (Config.VReal * VRANGE_20V0_MAX) / DataTable[ADC_BLV_20V0_TOP];
							break;
						case CHANEL_NONE:
						default:
							break;
					}

					DT_Write32(REG_I_MEAS_L, REG_I_MEAS_M, Config.CurrMeas);
					DT_Write32(REG_V_MEAS_L, REG_V_MEAS_M, Config.VMeas);
					// отключено LL_WriteDAC_LH(0 | DAC_SELECT_CHV);
					// отключено LL_WriteDAC_LH(0 | DAC_SELECT_CHI);

					LL_SetStateExtLed(false);

					//clean configuration
					Config.WorkMode = WORK_MODE_OFF;
					Config.PulseType = SRC_TYPE_NONE;
					Config.PulseTime = 0;
					Config.OutLine = OUT_LINE_NONE;
					Config.CurrSet = 0;
					Config.CurrCut = 0;
					Config.VSet = 0;
					Config.VCut = 0;
					//VB_RelayCommutation(&Config);
					//CONTROL_SetDeviceSubState(SS_None);
					CONTROL_SetDeviceState(DS_Ready, 0);
				}
				break;

			default:
				break;
		}
	}
}
//------------------------------------------

void CONTROL_SetDeviceState(DeviceState NewState, DeviceSubState NewSubState)
{
	CONTROL_State = NewState;
	DataTable[REG_DEV_STATE] = NewState;

	CONTROL_SubState = NewSubState;
	DataTable[REG_SUB_STATE] = NewSubState;
}
//------------------------------------------

void CONTROL_UpdateWatchDog()
{
	if(BOOT_LOADER_VARIABLE != BOOT_LOADER_REQUEST)
		IWDG_Refresh();
}
//------------------------------------------
