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

// Types
//
typedef void (*FUNC_AsyncDelegate)();

// Variables
//
volatile DeviceState CONTROL_State = DS_None;
volatile DeviceSubState CONTROL_SubState = SS_None;
static Boolean CycleActive = false;

ControllerConfig Config;

volatile Int64U CONTROL_TimeCounter = 0;

/// Forward functions
//
static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
void CONTROL_SetDeviceState(DeviceState NewState);
void CONTROL_SetDeviceSubState(DeviceSubState NewSubState);
void CONTROL_SwitchToFault(Int16U Reason);
void CONTROL_DelayMs(uint32_t Delay);
void CONTROL_UpdateWatchDog();
void CONTROL_ResetToDefaultState();
void CONTROL_ResetHardware();
void CONTROL_PulseControl();

// Functions
//
void CONTROL_Init()
{
	
	// Переменные для конфигурации EndPoint
	// Конфигурация сервиса работы Data-table и EPROM
	EPROMServiceConfig EPROMService = {(FUNC_EPROM_WriteValues)&NFLASH_WriteDT, (FUNC_EPROM_ReadValues)&NFLASH_ReadDT};
	// Инициализация data table
	DT_Init(EPROMService, false);
	DT_SaveFirmwareInfo(CAN_SLAVE_NID, 0);
	// Инициализация device profile
	DEVPROFILE_Init(&CONTROL_DispatchAction, &CycleActive);
	// Сброс значений
	DEVPROFILE_ResetControlSection();
	CONTROL_ResetToDefaultState();
}
//------------------------------------------

void CONTROL_ResetToDefaultState()
{
	DataTable[REG_FAULT_REASON] = DF_NONE;
	DataTable[REG_DISABLE_REASON] = DF_NONE;
	DataTable[REG_WARNING] = WARNING_NONE;
	DataTable[REG_PROBLEM] = PROBLEM_NONE;
	DataTable[REG_OP_RESULT] = OPRESULT_NONE;
	
	DEVPROFILE_ResetScopes(0);
	DEVPROFILE_ResetEPReadState();
	
	CONTROL_ResetHardware();
	
	CONTROL_SetDeviceState(DS_None);
}
//------------------------------------------

void CONTROL_ResetHardware()
{
	LL_SetStateExtLed(false);
	GPIO_SetState(GPIO_CS1, false);
	GPIO_SetState(GPIO_CS2, false);
	GPIO_SetState(GPIO_CS3, false);
	//safe state
	LL_SetStateCtrls(HP_CTRL_350V, true);
}
//------------------------------------------

void CONTROL_Idle()
{
	DEVPROFILE_ProcessRequests();
	LL_SetStateExtLed(true);
	CONTROL_PulseControl();
	//Config.VReal = MEASURE_Voltage();
	//Config.CurrReal = MEASURE_Current();
	LL_SetStateExtLed(false);
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
				{
					CONTROL_SetDeviceState(DS_Enabled);
				}
				else if(CONTROL_State != DS_Enabled)
				{
					*pUserError = ERR_DEVICE_NOT_READY;
				}
				break;
			}
			
		case ACT_DISABLE_POWER:
			if(CONTROL_State == DS_Enabled)
			{
				CONTROL_SetDeviceState(DS_None);
			}
			else
				*pUserError = ERR_OPERATION_BLOCKED;
			break;
			
		case ACT_FAULT_CLEAR:
			{
				if(CONTROL_State == DS_Fault)
				{
					CONTROL_ResetToDefaultState();
				}
			}
			break;
			
		case ACT_WARNING_CLEAR:
			DataTable[REG_WARNING] = 0;
			break;
			
		case ACT_START_PROCESS:
			{
				if((CONTROL_State == DS_Enabled) && (CONTROL_SubState == SS_None))
				{
					CONTROL_SetDeviceState(DS_InProcess);
					CONTROL_SetDeviceSubState(SS_PulsePrepare);
					LL_SetStateExtLed(true);
				}
				else
					*pUserError = ERR_DEVICE_NOT_READY;
			}
			break;

		case ACT_STOP_PROCESS:
			{
				if(CONTROL_State == DS_InProcess)
				{
					CONTROL_SetDeviceSubState(SS_PulseStop);
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
	CONTROL_SetDeviceState(DS_Fault);
	DataTable[REG_FAULT_REASON] = Reason;
}
//------------------------------------------

void CONTROL_PulseControl()
{
	bool ReturnValue;
	int16_t TempValue;
	int16_t VTempValue;
	int16_t ITempValue;
	uint64_t Time;

	if(CONTROL_State == DS_InProcess)
	{
		switch (CONTROL_SubState)
		{
			case SS_PulsePrepare:
				{
					VB_SaveParam(&Config);
					ReturnValue = VB_CheckParam(&Config);



					if(ReturnValue)
					{
						VB_EnableVoltageChannel(&Config);
						VB_EnableCurrentChannel(&Config);

						switch (Config.VChanel)
						{
							case CHANEL_V200:
								{
									LL_SelectRgK12();
									Config.VWant = (Config.VSet * DataTable[ADC_BLV_V200_TOP]) / VRANGE_0V20_MAX;
									//Config.VDac = (Config.VSet * DataTable[DAC_V200_TOP]) / VRANGE_0V20_MAX;
									Config.VDacRegionSize = DataTable[DAC_V200_TOP] - DataTable[DAC_V200_NULL];
									Config.VAdcRegionSize = DataTable[ADC_BLV_V200_TOP] - DataTable[ADC_BLV_V200_NULL];
								}
								break;
							case CHANEL_2V00:
								{
									LL_SelectRg7K70();
									Config.VWant = (Config.VSet * DataTable[ADC_BLV_2V00_TOP]) / VRANGE_2V00_MAX;
									//Config.VDac = (Config.VSet * DataTable[DAC_2V00_TOP]) / VRANGE_2V00_MAX;
									Config.VDacRegionSize = DataTable[DAC_2V00_TOP] - DataTable[DAC_2V00_NULL];
									Config.VAdcRegionSize = DataTable[ADC_BLV_2V00_TOP] - DataTable[ADC_BLV_2V00_NULL];
								}
								break;
							case CHANEL_20V0:
							default:
								{
									LL_SelectRg720K();
									Config.VWant = (Config.VSet * DataTable[ADC_BLV_20V0_TOP]) / VRANGE_20V0_MAX;
									//Config.VDac = (Config.VSet * DataTable[DAC_20V0_TOP]) / VRANGE_20V0_MAX;
									Config.VDacRegionSize = DataTable[DAC_20V0_TOP] - DataTable[DAC_20V0_NULL];
									Config.VAdcRegionSize = DataTable[ADC_BLV_20V0_TOP] - DataTable[ADC_BLV_20V0_NULL];
								}
								break;
						}

						switch (Config.CurrChanel)
						{
							case CHANEL_LV_R1:
								{
									Config.CurrWant = (Config.CurrSet * DataTable[ADC_ILV_R1_TOP]) / IRANGE_R1_MAX;
									Config.CurrDacRegionSize = DataTable[DAC_100MKA_TOP] - DataTable[DAC_100MKA_NULL];
									Config.CurrAdcRegionSize = DataTable[ADC_ILV_R1_TOP] - DataTable[ADC_ILV_R1_NULL];
								}
								break;
							case CHANEL_LV_R2:
								{
									Config.CurrWant = (Config.CurrSet * DataTable[ADC_ILV_R2_TOP]) / IRANGE_R2_MAX;
									Config.CurrDacRegionSize = DataTable[DAC_1MA_TOP] - DataTable[DAC_1MA_NULL];
									Config.CurrAdcRegionSize = DataTable[ADC_ILV_R1_TOP] - DataTable[ADC_ILV_R1_NULL];
								}
								break;
							case CHANEL_LV_R3:
							{
								Config.CurrWant = (Config.CurrSet * DataTable[ADC_ILV_R3_TOP]) / IRANGE_R3_MAX;
								Config.CurrDacRegionSize = DataTable[DAC_10MA_TOP] - DataTable[DAC_10MA_NULL];
								Config.CurrAdcRegionSize = DataTable[ADC_ILV_R1_TOP] - DataTable[ADC_ILV_R1_NULL];
							}
							break;
							case CHANEL_LV_R4:
							default:
								{
									Config.CurrWant = (Config.CurrSet * DataTable[ADC_ILV_R4_TOP]) / IRANGE_R4_MAX;
									Config.CurrDacRegionSize = DataTable[DAC_110MA_TOP] - DataTable[DAC_110MA_NULL];
									Config.CurrAdcRegionSize = DataTable[ADC_ILV_R1_TOP] - DataTable[ADC_ILV_R1_NULL];
								}
								break;
						}

						LL_SelectAdcSrcVLV();
						LL_SelectAdcSrcILV();
						VB_SetCurrentLimit();
						VB_RelayCommutation(&Config);
						Config.CurrDac = 0;
						Config.VDac = 0;
						CONTROL_SetDeviceSubState(SS_PulseStart);
						LL_SetStateExtLed(true);
					}
					else
					{
						CONTROL_SetDeviceSubState(SS_PulseStop);
					}
				}
				break;
			case SS_PulseStart:
				{
					Config.StartTime = CONTROL_TimeCounter;
					switch (Config.WorkMode)
					{
						case WORK_MODE_VOLT:
							LL_WriteDAC_LH(Config.VDac);
							break;
						case WORK_MODE_CURR:
							LL_WriteDAC_LH(Config.CurrDac);
							break;
					}
					CONTROL_SetDeviceSubState(SS_PulseProcess);
					Config.VError = 0;
					Config.IError = 0;
				}
				break;
			case SS_PulseProcess:
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

							CONTROL_SetDeviceSubState(SS_PulseStop);
						}
					}
					//выход на заданные параметры
					//регулятор напряжения
					Config.VReal = MEASURE_Voltage();
					VTempValue = Config.VWant - Config.VReal;
					//масштабирование ошибки ADC->DAC
					VTempValue = (VTempValue * Config.VDacRegionSize) / Config.VAdcRegionSize;
					do
					{
						if(abs(VTempValue) > 10)
						{
							VTempValue /= 10;
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
					VTempValue = Config.VDac + Config.VError;

					//регулятор тока
					Config.CurrReal = MEASURE_Current();
					ITempValue = Config.CurrWant - Config.CurrReal;
					//масштабирование ошибки ADC->DAC
					ITempValue = (ITempValue * Config.VDacRegionSize) / Config.VAdcRegionSize;
					if(abs(ITempValue) > 25)
						{
							ITempValue = 25*sign(ITempValue);
						}
					Config.IError += ITempValue;
					ITempValue = Config.CurrDac + Config.IError;

					//ограничение по току или напряжению
					TempValue = (ITempValue<VTempValue) ? ITempValue : VTempValue;
					if(TempValue < 0)
					{
						TempValue = 0;
					}
					if(TempValue > DAC_MAX_VALUE)
					{
						TempValue = DAC_MAX_VALUE;
					}

					LL_WriteDAC_LH(TempValue);
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
					LL_WriteDAC_LH(0 | DAC_SELECT_CHV);
					LL_WriteDAC_LH(0 | DAC_SELECT_CHI);
					VB_DisableVoltageChannel();

					LL_SetStateExtLed(false);
					;
					//clean configuration
					Config.WorkMode = WORK_MODE_OFF;
					Config.PulseType = SRC_TYPE_NONE;
					Config.PulseTime = 0;
					Config.OutLine = OUT_LINE_NONE;
					Config.CurrSet = 0;
					Config.CurrCut = 0;
					Config.VSet = 0;
					Config.VCut = 0;
					VB_RelayCommutation(&Config);
					CONTROL_SetDeviceSubState(SS_None);
					CONTROL_SetDeviceState(DS_Enabled);
				}
				break;

			default:
				break;
		}
	}
}
//------------------------------------------

void CONTROL_SetDeviceState(DeviceState NewState)
{
	CONTROL_State = NewState;
	DataTable[REG_DEV_STATE] = NewState;
}
//------------------------------------------

void CONTROL_SetDeviceSubState(DeviceSubState NewSubState)
{
	CONTROL_SubState = NewSubState;
}
//------------------------------------------

void CONTROL_DelayMs(uint32_t Delay)
{
	uint64_t Counter = (uint64_t)CONTROL_TimeCounter + Delay;
	while(Counter > CONTROL_TimeCounter)
		CONTROL_UpdateWatchDog();
}
//------------------------------------------

void CONTROL_UpdateWatchDog()
{
	if(BOOT_LOADER_VARIABLE != BOOT_LOADER_REQUEST)
		IWDG_Refresh();
}
//------------------------------------------

