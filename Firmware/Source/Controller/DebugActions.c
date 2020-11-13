// Header
#include "DebugActions.h"

// Include
//
#include "LowLevel.h"
#include "Board.h"
#include "Delay.h"
#include "Global.h"
#include "Controller.h"
#include "VoltageBoard.h"
#include "DataTable.h"
#include "Diagnostic.h"

// Functions
//
void DBGACT_BlinkExtLed()
{
	LL_SetStateExtLed(TRUE);
	DELAY_MS(TIME_DBG_PULSE);
	LL_SetStateExtLed(FALSE);
}
//-----------------------------

void DBGACT_GenerateImpulseToLineSync1()
{
	LL_SetStateLineSync1(TRUE);
	DELAY_MS(TIME_DBG_PULSE);
	LL_SetStateLineSync1(FALSE);
}
//-----------------------------

void DBGACT_GenerateImpulseToLineSync2()
{
	LL_SetStateLineSync2(TRUE);
	DELAY_MS(TIME_DBG_PULSE);
	LL_SetStateLineSync2(FALSE);
}
//-----------------------------

bool DBGACT_ReadStateLineSync1()
{
	return LL_GetStateLineSync1();
}
//-----------------------------

bool DBGACT_ReadStateLineSync2()
{
	return LL_GetStateLineSync2();
}
//-----------------------------

void DBGACT_LHVSelectSrc(SelVSrc src)
{
	if(src == SELECT_VSRC_HIGH)
	{
		LL_SetStateCtrls(LV_HV_CTRL1, true);
		LL_SetStateCtrls(LV_HV_CTRL2, true);
	}
	else
	{
		LL_SetStateCtrls(LV_HV_CTRL1, false);
		LL_SetStateCtrls(LV_HV_CTRL2, false);
	}
}
//-----------------------------

void DBGACT_Ctrls48V(bool State)
{
	LL_SetStateCtrls(EN_48V_CTRL, State);
}
//-----------------------------

void DBGACT_Ctrls350V(bool State)
{
	LL_SetStateCtrls(HP_CTRL_350V, State);
	LL_HVPowerSupplyOutput(!State);
}
//-----------------------------

void DBGACT_SelectRg()
{
	Int16U Range = DataTable[REG_DEBUG];
	
	switch (Range)
	{
		case RANGE_V_HV_R0:
			LL_SelectRgK12();
			break;
			
		case RANGE_V_HV_R1:
			LL_SelectRg1K10();
			break;
			
		case RANGE_V_HV_R2:
			LL_SelectRg7K70();
			break;
			
		case RANGE_V_HV_R3:
			LL_SelectRg720K();
			break;
	}
}
//-----------------------------

void DBGACT_SelectVSensSrc()
{
	Int16U VSrc = DataTable[REG_DEBUG];
	
	switch (VSrc)
	{
		case SENSOR_LV:
			LL_SelectAdcSrc_LowVoltagePS();
			break;
		case SENSOR_HV:
			LL_SelectAdcSrc_HighVoltage();
			break;
		case SENSOR_PT:
			LL_SelectAdcSrc_LowVoltageBUS();
			break;
		case SENSOR_PT_CTRL:
			LL_SelectAdcSrc_LowVoltageControl();
			break;
		case SENSOR_NO:
			LL_SelectAdcSrc_Disconnect();
			break;
	}
}
//-----------------------------

void DBGACT_SelectISensSrc()
{
	Int16U ISrc = DataTable[REG_DEBUG];
	
	switch (ISrc)
	{
		case SENSOR_I_LV:
			LL_SelectAdcSrcILV();
			break;
		case SENSOR_I_HV:
			LL_SelectAdcSrcIHV();
			break;
	}
}
//-----------------------------

void DBGACT_SelectLVCtrls()
{
	Int16U Range = DataTable[REG_DEBUG];
	
	switch (Range)
	{
		case SELECT_LV_R0:
			LL_SelectRs27K();
			break;
			
		case SELECT_LV_R1:
			LL_SelectRs2K7();
			break;
			
		case SELECT_LV_R2:
			LL_SelectRsK27();
			break;
			
		case SELECT_LV_R3:
			LL_SelectRsK020();
			break;
			
		default:
			LL_SelectRsNone();
			break;
	}
}
//-----------------------------

void DBGACT_SelectHVCtrls()
{
	Int16U Range = DataTable[REG_DEBUG];
	
	switch (Range)
	{
		case SELECT_HV_R1:
			LL_SelectHV_R1();
			break;
			
		case SELECT_HV_R2:
			LL_SelectHV_R2();
			break;

		case SELECT_HV_R3:
			LL_SelectHV_R3();
			break;

		case SELECT_HV_R4:
			LL_SelectHV_R4();
			break;
	}
}
//-----------------------------

void DBGACT_SelectVRange()
{
	Int16U Range = DataTable[REG_DEBUG];

	switch (Range)
	{
		case SELECT_LV_R0:
			{
				LL_SelectVOutMaxV200();
			}
			break;

		case SELECT_LV_R1:
			{
				LL_SelectVOutMax2V00();
			}
			break;

		case SELECT_LV_R2:
			{
				LL_SelectVOutMax20V0();
			}
			break;
	}
}
//-----------------------------
