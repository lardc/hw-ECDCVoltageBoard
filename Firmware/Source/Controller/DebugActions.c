// Header
#include "DebugActions.h"

// Include
//
#include "LowLevel.h"
#include "Board.h"
#include "Delay.h"
#include "Controller.h"
#include "DataTable.h"

// Functions
//
void DBGACT_BlinkExtLed()
{
	LL_SetStateExtLed(TRUE);
	CONTROL_DelayMs(1000);
	LL_SetStateExtLed(FALSE);
}
//-----------------------------

void DBGACT_GenerateImpulseToLineSync1()
{
	LL_SetStateLineSync1(TRUE);
	CONTROL_DelayMs(100);
	LL_SetStateLineSync1(FALSE);
}
//-----------------------------

void DBGACT_GenerateImpulseToLineSync2()
{
	LL_SetStateLineSync2(TRUE);
	CONTROL_DelayMs(100);
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

void DBGACT_RelayCtrlsOn()
{
	Int16U Relay = DataTable[REG_DBG_STATE];

	switch (Relay)
	{
		case 1:
			{
				LL_SetStateCtrls(RLC_CTRL1, true);
			}
			break;

		case 2:
			{
				LL_SetStateCtrls(RLC_CTRL2, true);
			}
			break;

		case 3:
			{
				LL_SetStateCtrls(RLC_CTRL3, true);
			}
			break;

		case 4:
			{
				LL_SetStateCtrls(RLC_CTRL4, true);
			}
			break;

		case 5:
			{
				LL_SetStateCtrls(RLC_CTRL5, true);
			}
			break;

		case 6:
			{
				LL_SetStateCtrls(RLC_CTRL6, true);
			}
			break;

		case 7:
			{
				LL_SetStateCtrls(RLC_CTRL7, true);
			}
			break;

		case 8:
			{
				LL_SetStateCtrls(RLC_CTRL8, true);
			}
			break;
	}
}
//-----------------------------

void DBGACT_RelayCtrlsOff()
{
	Int16U Relay = DataTable[REG_DBG_STATE];

	switch (Relay)
	{
		case 1:
			{
				LL_SetStateCtrls(RLC_CTRL1, false);
			}
			break;

		case 2:
			{
				LL_SetStateCtrls(RLC_CTRL2, false);
			}
			break;

		case 3:
			{
				LL_SetStateCtrls(RLC_CTRL3, false);
			}
			break;

		case 4:
			{
				LL_SetStateCtrls(RLC_CTRL4, false);
			}
			break;

		case 5:
			{
				LL_SetStateCtrls(RLC_CTRL5, false);
			}
			break;

		case 6:
			{
				LL_SetStateCtrls(RLC_CTRL6, false);
			}
			break;

		case 7:
			{
				LL_SetStateCtrls(RLC_CTRL7, false);
			}
			break;

		case 8:
			{
				LL_SetStateCtrls(RLC_CTRL8, false);
			}
			break;
	}
}
//-----------------------------

void DBGACT_LHVSelectLow()
{
	LL_SetStateCtrls(LV_HV_CTRL1, false);	// set together 1&2
	LL_SetStateCtrls(LV_HV_CTRL2, false);
}
//-----------------------------

void DBGACT_LHVSelectHigh()
{
	LL_SetStateCtrls(LV_HV_CTRL1, true);		// set together 1&2
	LL_SetStateCtrls(LV_HV_CTRL2, true);
}
//-----------------------------

void DBGACT_Ctrls48VEnable()
{
	LL_SetStateCtrls(EN_48V_CTRL, true);
}
//-----------------------------

void DBGACT_Ctrls48VDisable()
{
	LL_SetStateCtrls(EN_48V_CTRL, false);
}
//-----------------------------

void DBGACT_Ctrls350VEnable()
{
	LL_SetStateCtrls(HP_CTRL_350V, true);
}
//-----------------------------

void DBGACT_Ctrls350VDisable()
{
	LL_SetStateCtrls(HP_CTRL_350V, false);
}
//-----------------------------

void DBGACT_SelectRg()
{
	Int16U Range = DataTable[REG_DBG_STATE];

	switch (Range)
	{
		case 1:
			{
				LL_SetStateCtrls(V_HV_CTRL_RANGE_0, false);
				//
				LL_SetStateCtrls(V_HV_CTRL_RANGE_1, true);
				LL_SetStateCtrls(V_HV_CTRL_RANGE_2, true);
				LL_SetStateCtrls(V_HV_CTRL_RANGE_3, true);
			}
			break;

		case 2:
			{
				LL_SetStateCtrls(V_HV_CTRL_RANGE_1, false);
				//
				LL_SetStateCtrls(V_HV_CTRL_RANGE_0, true);
				LL_SetStateCtrls(V_HV_CTRL_RANGE_2, true);
				LL_SetStateCtrls(V_HV_CTRL_RANGE_3, true);
			}
			break;

		case 3:
			{
				LL_SetStateCtrls(V_HV_CTRL_RANGE_2, false);
				//
				LL_SetStateCtrls(V_HV_CTRL_RANGE_0, true);
				LL_SetStateCtrls(V_HV_CTRL_RANGE_1, true);
				LL_SetStateCtrls(V_HV_CTRL_RANGE_3, true);
			}
			break;

		case 4:
			{
				LL_SetStateCtrls(V_HV_CTRL_RANGE_3, false);
				//
				LL_SetStateCtrls(V_HV_CTRL_RANGE_0, true);
				LL_SetStateCtrls(V_HV_CTRL_RANGE_1, true);
				LL_SetStateCtrls(V_HV_CTRL_RANGE_2, true);
			}
			break;
	}
}
//-----------------------------

void DBGACT_SelectVSensSrc()
{
	Int16U VSrc = DataTable[REG_DBG_STATE];

	switch (VSrc)
	{
		case 1:
			{
				LL_SetStateCtrls(LV_SENS_EN, true);		//off&off then ONE on
				LL_SetStateCtrls(HV_SENS_EN, true);
				//
				LL_SetStateCtrls(LV_SENS_EN, false);
			}
			break;
		case 2:
			{
				LL_SetStateCtrls(LV_SENS_EN, true); //off&off then ONE on
				LL_SetStateCtrls(HV_SENS_EN, true);
				//
				LL_SetStateCtrls(HV_SENS_EN, false);
			}
			break;
	}
}
//-----------------------------

void DBGACT_SelectISensSrc()
{
	Int16U ISrc = DataTable[REG_DBG_STATE];

	switch (ISrc)
	{
		case 1:
			{
				LL_SetStateCtrls(LV_CUR_SENS_EN, true); //off&off then ONE on
				LL_SetStateCtrls(HV_CUR_SENS_EN, true);
				//
				LL_SetStateCtrls(LV_CUR_SENS_EN, false);
			}
			break;
		case 2:
			{
				LL_SetStateCtrls(LV_CUR_SENS_EN, true); //off&off then ONE on
				LL_SetStateCtrls(HV_CUR_SENS_EN, true);
				//
				LL_SetStateCtrls(HV_CUR_SENS_EN, false);
			}
			break;
	}
}
//-----------------------------

void DBGACT_SelectDACx()
{
	SelDacX dac = DataTable[REG_DBG_STATE];

	LL_SelectDACx(dac);
}
//-----------------------------
void DBGACT_WriteDACx()
{
	uint16_t Data = DataTable[REG_DBG_STATE];

	LL_WriteDAC_LH(Data);
}

//-----------------------------
void DBGACT_SelectLVCtrls()
{
	Int16U Range = DataTable[REG_DBG_STATE];

	switch (Range)
	{
		case 1:
			{
				LL_SetStateRanges(LV_CTRL_RANGE_0, true);
				//
				LL_SetStateRanges(LV_CTRL_RANGE_1, false);
				LL_SetStateRanges(LV_CTRL_RANGE_2, false);
				LL_SetStateRanges(LV_CTRL_RANGE_3, false);
			}
			break;

		case 2:
			{
				LL_SetStateRanges(LV_CTRL_RANGE_1, true);
				//
				LL_SetStateRanges(LV_CTRL_RANGE_0, false);
				LL_SetStateRanges(LV_CTRL_RANGE_2, false);
				LL_SetStateRanges(LV_CTRL_RANGE_3, false);
			}
			break;

		case 3:
			{
				LL_SetStateRanges(LV_CTRL_RANGE_2, true);
				//
				LL_SetStateRanges(LV_CTRL_RANGE_0, false);
				LL_SetStateRanges(LV_CTRL_RANGE_1, false);
				LL_SetStateRanges(LV_CTRL_RANGE_3, false);
			}
			break;

		case 4:
			{
				LL_SetStateRanges(LV_CTRL_RANGE_3, true);
				//
				LL_SetStateRanges(LV_CTRL_RANGE_0, false);
				LL_SetStateRanges(LV_CTRL_RANGE_1, false);
				LL_SetStateRanges(LV_CTRL_RANGE_2, false);
			}
			break;

		default:
			{
				LL_SetStateRanges(LV_CTRL_RANGE_0, false);
				LL_SetStateRanges(LV_CTRL_RANGE_1, false);
				LL_SetStateRanges(LV_CTRL_RANGE_2, false);
				LL_SetStateRanges(LV_CTRL_RANGE_3, false);
			}
			break;
	}
}
//-----------------------------

void DBGACT_SelectHVCtrls()
{
	Int16U Range = DataTable[REG_DBG_STATE];

	switch (Range)
	{
		case 1:
			{
				LL_SetStateRanges(HV_CTRL_RANGE_0, false);
				//
				LL_SetStateRanges(HV_CTRL_RANGE_1, true);
				LL_SetStateRanges(HV_CTRL_RANGE_2, true);
			}
			break;

		case 2:
			{
				LL_SetStateRanges(HV_CTRL_RANGE_1, false);
				//
				LL_SetStateRanges(HV_CTRL_RANGE_0, true);
				LL_SetStateRanges(HV_CTRL_RANGE_2, true);
			}
			break;

		case 3:
			{
				LL_SetStateRanges(HV_CTRL_RANGE_2, false);
				//
				LL_SetStateRanges(HV_CTRL_RANGE_0, true);
				LL_SetStateRanges(HV_CTRL_RANGE_1, true);
			}
			break;
	}
}
//-----------------------------

void DBGACT_TestWaveform()
{
	uint16_t i = 0;

	LL_SelectDACx(SELECT_DAC_LV);
	do
	{
		LL_WriteDAC_LH(i | DAC_SELECT_CHU);
		LL_WriteDAC_LH((DAC_MAX_VALUE - i) | DAC_SELECT_CHI);
		i++;
	}
	while(i <= DAC_MAX_VALUE);
	i--;
	CONTROL_UpdateWatchDog();
	do
	{
		LL_WriteDAC_LH(i | DAC_SELECT_CHU);
		LL_WriteDAC_LH((DAC_MAX_VALUE - i) | DAC_SELECT_CHI);
	}
	while(i--);
	CONTROL_UpdateWatchDog();

	LL_SelectDACx(SELECT_DAC_NONE);

}
//-----------------------------

