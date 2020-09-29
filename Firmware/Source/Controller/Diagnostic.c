// Header
#include "Diagnostic.h"

// Includes
#include "DataTable.h"
#include "LowLevel.h"
#include "Controller.h"
#include "DebugActions.h"
#include "Board.h"

// Functions
bool DIAG_HandleDiagnosticAction(uint16_t ActionID, uint16_t *pUserError)
{
	switch (ActionID)
	{
		case ACT_DBG_PULSE_SYNC1:
			{
				DBGACT_GenerateImpulseToLineSync1();
			}
			break;

		case ACT_DBG_PULSE_SYNC2:
			{
				DBGACT_GenerateImpulseToLineSync2();
			}
			break;

		case ACT_DBG_IS_STATE_SYNC_1:
			{
				DataTable[REG_DBG_SYNC1] = DBGACT_ReadStateLineSync1();	//see DeviceObjectDictionary.h
			}
			break;

		case ACT_DBG_IS_STATE_SYNC_2:
			{
				DataTable[REG_DBG_SYNC2] = DBGACT_ReadStateLineSync2();	//see DeviceObjectDictionary.h
			}
			break;

		case ACT_DBG_PULSE_EXT_LED:
			{
				DBGACT_BlinkExtLed();
			}
			break;

		case ACT_DBG_RELAY_ON:
			{
				DBGACT_RelayCtrlsOn();	//Relay = DataTable[REG_DBG_STATE]; //1..8
			}
			break;
		case ACT_DBG_RELAY_OFF:
			{
				DBGACT_RelayCtrlsOff();	//Relay = DataTable[REG_DBG_STATE]; //1..8
			}
			break;

		case ACT_DBG_LHVSELECT_LOW:
			{
				DBGACT_LHVSelectLow();
			}
			break;

		case ACT_DBG_LHVSELECT_HIGH:
			{
				DBGACT_LHVSelectHigh();
			}
			break;

		case ACT_DBG_CTRL48V_ENABLE:
			{
				DBGACT_Ctrls48VEnable();
			}
			break;

		case ACT_DBG_CTRL48V_DISABLE:
			{
				DBGACT_Ctrls48VDisable();
			}
			break;

		case ACT_DBG_CTRL350V_ENABLE:
			{
				DBGACT_Ctrls350VEnable();
			}
			break;

		case ACT_DBG_CTRL350V_DISABLE:
			{
				DBGACT_Ctrls350VDisable();
			}
			break;

		case ACT_DBG_SELECT_VHV_CTRLS:
			{
				DBGACT_SelectRg();		//Range = DataTable[REG_DBG_STATE]; //1..4
			}
			break;

		case ACT_DBG_VSENS_SELECT_SRC:
			{
				DBGACT_SelectVSensSrc();		//Src = DataTable[REG_DBG_STATE]; //1:LV_SENS_EN, 2:HV_SENS_EN
			}
			break;

		case ACT_DBG_ISENS_SELECT_SRC:
			{
				DBGACT_SelectISensSrc();		//Src = DataTable[REG_DBG_STATE]; //1:LV_CUR_SENS_EN, 2:HV_CUR_SENS_EN
			}
			break;

		case ACT_DBG_SELECT_DAC:
			{
				DBGACT_SelectDACx();		//dacx = DataTable[REG_DBG_STATE]; //
			}
			break;
		case ACT_DBG_WRITE_DAC:
			{
				DBGACT_WriteDACx();			//data = DataTable[REG_DBG_STATE]; //
			}
			break;
		case ACT_DBG_SELECT_LV_CTRLS:
			{
				DBGACT_SelectLVCtrls();			//data = DataTable[REG_DBG_STATE]; //
			}
			break;
		case ACT_DBG_SELECT_HV_CTRLS:
			{
				DBGACT_SelectHVCtrls();			//data = DataTable[REG_DBG_STATE]; //
			}
			break;
		case ACT_DBG_READ_ADC_VCH:
			{
				DataTable[REG_DBG_STATE] = ADC_Measure(ADC2, 1);			//ADC V-chanel
			}
			break;

		case ACT_DBG_READ_ADC_ICH:
			{
				DataTable[REG_DBG_STATE] = ADC_Measure(ADC1, 1);			//ADC I-chanel
			}
			break;

		case ACT_DBG_TEST_WAVEFORM:
			{
				DBGACT_TestWaveform();			//Triangle channel A&B (LV/LC domain)
			}
			break;

		default:
			return false;
	}

	return true;
}

