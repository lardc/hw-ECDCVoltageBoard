// Header
#include "Diagnostic.h"
#include "Measurement.h"

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
				DBGACT_RelayCtrls(DataTable[REG_DBG_STATE], true);
			}
			break;
		case ACT_DBG_RELAY_OFF:
			{
				DBGACT_RelayCtrls(DataTable[REG_DBG_STATE], false);
			}
			break;
			
		case ACT_DBG_LHVSELECT_LOW:
			{
				DBGACT_LHVSelectSrc(SELECT_VSRC_LOW);
			}
			break;
			
		case ACT_DBG_LHVSELECT_HIGH:
			{
				DBGACT_LHVSelectSrc(SELECT_VSRC_HIGH);
			}
			break;
			
		case ACT_DBG_CTRL48V_ENABLE:
			{
				DBGACT_Ctrls48V(true);
			}
			break;
			
		case ACT_DBG_CTRL48V_DISABLE:
			{
				DBGACT_Ctrls48V(false);
			}
			break;
			
		case ACT_DBG_CTRL350V_ENABLE:
			{
				DBGACT_Ctrls350V(false);
			}
			break;
			
		case ACT_DBG_CTRL350V_DISABLE:
			{
				DBGACT_Ctrls350V(true);
			}
			break;
			
		case ACT_DBG_SELECT_VHV_CTRLS:
			{
				DBGACT_SelectRg();
			}
			break;
			
		case ACT_DBG_VSENS_SELECT_SRC:
			{
				DBGACT_SelectVSensSrc();
			}
			break;
			
		case ACT_DBG_ISENS_SELECT_SRC:
			{
				DBGACT_SelectISensSrc();
			}
			break;
			
		case ACT_DBG_SELECT_DAC:
			{
				DBGACT_SelectDACx();
			}
			break;
		case ACT_DBG_WRITE_DAC:
			{
				DBGACT_WriteDACx();
			}
			break;
		case ACT_DBG_SELECT_LV_CTRLS:
			{
				DBGACT_SelectLVCtrls();
			}
			break;
		case ACT_DBG_SELECT_HV_CTRLS:
			{
				DBGACT_SelectHVCtrls();
			}
			break;
		case ACT_DBG_READ_ADC_VCH:
			{
				DataTable[REG_DBG_STATE] = MEASURE_Voltage();
			}
			break;
			
		case ACT_DBG_READ_ADC_ICH:
			{
				DataTable[REG_DBG_STATE] = MEASURE_Current();
			}
			break;
			
		case ACT_DBG_TEST_WAVEFORM:
			{
				DBGACT_TestWaveform();
			}
			break;
			
		default:
			return false;
	}
	
	return true;
}

