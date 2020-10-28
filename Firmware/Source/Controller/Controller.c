// Header
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
#include "Regulator.h"

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
void CONTROL_StartRegulator(bool State);
bool CONTROL_ConfiguredLimitReached(float SampledVoltage, float SampledCurrent);

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

	DataTable[REG_CURRENT_RESULT] = 0;
	DataTable[REG_CURRENT_RESULT_32] = 0;
	DataTable[REG_VOLTAGE_RESULT] = 0;
	DataTable[REG_VOLTAGE_RESULT_32] = 0;

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
	LL_ResetDACOutputs();

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
				if(CONTROL_State == DS_Ready)
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
					// Нормальное завершение
					if(CONTROL_SubState == SS_PulseProcess)
						CONTROL_ForceRegulatorStop(PROBLEM_NONE);
					// Принудительная остановка
					else if(CONTROL_SubState != SS_RequestStop && CONTROL_SubState != SS_WaitDisconnection)
						CONTROL_ForceRegulatorStop(PROBLEM_FORCED_STOP);
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
	static uint64_t Timeout = 0;

	if(CONTROL_State == DS_InProcess)
	{
		switch (CONTROL_SubState)
		{
			case SS_PulsePrepare:
				{
					Timeout = CONTROL_TimeCounter + TIME_TRANSIENT_DELAY;
					VB_ConfigVIChannels(&Config);
					CONTROL_SetDeviceState(DS_InProcess, SS_PulseWaitSwitch);
				}
				break;

			case SS_PulseWaitSwitch:
				{
					if(CONTROL_TimeCounter > Timeout)
					{
						Timeout = CONTROL_TimeCounter + TIME_TRANSIENT_DELAY;
						VB_SetLimitVIOutputs(&Config);
						CONTROL_SetDeviceState(DS_InProcess, SS_PulseWaitOutSet);
					}
				}
				break;

			case SS_PulseWaitOutSet:
				{
					if(CONTROL_TimeCounter > Timeout)
					{
						if(Config.OutputMode == OM_Pulse)
							Timeout = CONTROL_TimeCounter + Config.PulseTime;
						else
							Timeout = 0;

						CONTROL_StartRegulator(true);
						CONTROL_SetDeviceState(DS_InProcess, SS_PulseProcess);
					}
				}
				break;

			case SS_PulseProcess:
				{
					if(Timeout)
					{
						if(CONTROL_TimeCounter > Timeout)
							CONTROL_ForceRegulatorStop(PROBLEM_NONE);
					}

					float LastVoltage = REGULATOR_GetLastSampleVoltage();
					float LastCurrent = REGULATOR_GetLastSampleCurrent();
					if(CONTROL_ConfiguredLimitReached(LastVoltage, LastCurrent))
						CONTROL_ForceRegulatorStop(PROBLEM_VI_LIMIT);
				}
				break;

			case SS_RequestStop:
				{
					// Раскоммутация
					Timeout = CONTROL_TimeCounter + TIME_TRANSIENT_DELAY;
					CONTROL_SetDeviceState(DS_InProcess, SS_WaitDisconnection);
				}
				break;

			case SS_WaitDisconnection:
				{
					if(CONTROL_TimeCounter > Timeout)
					{
						if(Config.Problem == PROBLEM_NONE)
						{
							DataTable[REG_OP_RESULT] = OPRESULT_OK;

							float LastVoltage = REGULATOR_GetLastSampleVoltage();
							float LastCurrent = REGULATOR_GetLastSampleCurrent();

							DT_Write32(REG_VOLTAGE_RESULT, REG_VOLTAGE_RESULT_32, (uint32_t)LastVoltage);
							DT_Write32(REG_CURRENT_RESULT, REG_CURRENT_RESULT_32, (uint32_t)LastCurrent);
						}
						else
						{
							DataTable[REG_PROBLEM] = Config.Problem;
							DataTable[REG_OP_RESULT] = OPRESULT_FAIL;
						}

						CONTROL_SetDeviceState(DS_Ready, SS_None);
					}
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

void CONTROL_ForceRegulatorStop(uint16_t Problem)
{
	Config.Problem = Problem;

	CONTROL_StartRegulator(false);
	LL_ResetDACOutputs();
	LL_SetStateExtLed(false);

	CONTROL_SetDeviceState(DS_InProcess, SS_RequestStop);
}
//------------------------------------------

bool CONTROL_ConfiguredLimitReached(float SampledVoltage, float SampledCurrent)
{
	if(Config.OutputType == OT_Voltage)
		return SampledCurrent > Config.CurrentSetpoint;
	else
		return SampledVoltage > Config.VoltageSetpoint;
}
//------------------------------------------

void CONTROL_StartRegulator(bool State)
{
	State ? TIM_Start(TIM2) : TIM_Stop(TIM2);
}
//------------------------------------------
