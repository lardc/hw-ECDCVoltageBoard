// Header
#include "Diagnostic.h"
#include "Measurement.h"

// Includes
#include "DataTable.h"
#include "LowLevel.h"
#include "Controller.h"
#include "DebugActions.h"
#include "Board.h"
#include "VoltageBoard.h"

//Externs
//
extern ControllerConfig Config;

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
				DataTable[REG_DBG_SYNC1] = DBGACT_ReadStateLineSync1();
			}
			break;
			
		case ACT_DBG_IS_STATE_SYNC_2:
			{
				DataTable[REG_DBG_SYNC2] = DBGACT_ReadStateLineSync2();
			}
			break;
			
		case ACT_DBG_PULSE_EXT_LED:
			{
				DBGACT_BlinkExtLed();
			}
			break;
			
		case ACT_DBG_RELAY_ON:
			{
				LL_RelayCtrls(DataTable[REG_DEBUG], true);
			}
			break;
		case ACT_DBG_RELAY_OFF:
			{
				LL_RelayCtrls(DataTable[REG_DEBUG], false);
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
			
		case ACT_DBG_SELECT_LV_CTRLS:
			{
				DBGACT_SelectLVCtrls();
				DBGACT_SelectVRange();
			}
			break;

		case ACT_DBG_SELECT_HV_CTRLS:
			{
				DBGACT_SelectHVCtrls();
			}
			break;

		case ACT_DBG_READ_ADC_VCH:
			{
				DataTable[REG_DEBUG] = MEASURE_VoltageRaw();
			}
			break;
			
		case ACT_DBG_READ_ADC_ICH:
			{
				DataTable[REG_DEBUG] = MEASURE_CurrentRaw();
			}
			break;

		case ACT_DBG_WRITE_DAC_LV_VOLTAGE:
			LL_WriteDACLV_Voltage(DataTable[REG_DEBUG]);
			break;

		case ACT_DBG_WRITE_DAC_LV_CURRENT:
			LL_WriteDACLV_Current(DataTable[REG_DEBUG]);
			break;

		case ACT_DBG_WRITE_DAC_HV_VOLTAGE:
			LL_WriteDACHV_Voltage(DataTable[REG_DEBUG]);
			break;

		case ACT_DBG_WRITE_DAC_HV_CURRENT:
			LL_WriteDACHV_Current(DataTable[REG_DEBUG]);
			break;

		default:
			return false;
	}
	
	return true;
}
