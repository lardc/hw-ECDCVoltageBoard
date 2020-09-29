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

void DBGACT_RelayCtrls(uint16_t Relay, bool State)
{
	switch (Relay)
	{
		case 1:
			{
				LL_SetStateCtrls(RLC_CTRL1, State);
			}
			break;

		case 2:
			{
				LL_SetStateCtrls(RLC_CTRL2, State);
			}
			break;

		case 3:
			{
				LL_SetStateCtrls(RLC_CTRL3, State);
			}
			break;

		case 4:
			{
				LL_SetStateCtrls(RLC_CTRL4, State);
			}
			break;

		case 5:
			{
				LL_SetStateCtrls(RLC_CTRL5, State);
			}
			break;

		case 6:
			{
				LL_SetStateCtrls(RLC_CTRL6, State);
			}
			break;

		case 7:
			{
				LL_SetStateCtrls(RLC_CTRL7, State);
			}
			break;

		case 8:
			{
				LL_SetStateCtrls(RLC_CTRL8, State);
			}
			break;
	}
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
				LL_SetStateCtrls(LV_SENS_EN, true);
				LL_SetStateCtrls(HV_SENS_EN, true);
				//
				LL_SetStateCtrls(LV_SENS_EN, false);
			}
			break;
		case 2:
			{
				LL_SetStateCtrls(LV_SENS_EN, true);
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
				LL_SetStateCtrls(LV_CUR_SENS_EN, true);
				LL_SetStateCtrls(HV_CUR_SENS_EN, true);
				//
				LL_SetStateCtrls(LV_CUR_SENS_EN, false);
			}
			break;
		case 2:
			{
				LL_SetStateCtrls(LV_CUR_SENS_EN, true);
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

