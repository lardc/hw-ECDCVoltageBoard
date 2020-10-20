// Header
#include "DebugActions.h"

// Include
//
#include "LowLevel.h"
#include "Board.h"
#include "Delay.h"
#include "Controller.h"
#include "VoltageBoard.h"
#include "DataTable.h"
#include "Diagnostic.h"

// Functions
//
void DBGACT_BlinkExtLed()
{
	LL_SetStateExtLed(TRUE);
	CONTROL_DelayMs(TIME_EXT_LED_BLINK * 2);
	LL_SetStateExtLed(FALSE);
}
//-----------------------------

void DBGACT_GenerateImpulseToLineSync1()
{
	LL_SetStateLineSync1(TRUE);
	CONTROL_DelayMs(TIME_PULSE_LINE_SYNC);
	LL_SetStateLineSync1(FALSE);
}
//-----------------------------

void DBGACT_GenerateImpulseToLineSync2()
{
	LL_SetStateLineSync2(TRUE);
	CONTROL_DelayMs(TIME_PULSE_LINE_SYNC);
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
}
//-----------------------------

void DBGACT_SelectRg()
{
	Int16U Range = DataTable[REG_DBG_STATE];
	
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
	Int16U VSrc = DataTable[REG_DBG_STATE];
	
	switch (VSrc)
	{
		case SENSOR_LV:
			LL_SelectAdcSrcVLV();
			break;
		case SENSOR_HV:
			LL_SelectAdcSrcHV();
			break;
		case SENSOR_PT:
			LL_SelectAdcSrcPT();
			break;
		case SENSOR_NO:
			LL_SelectAdcSrcNO();
			break;
	}
}
//-----------------------------

void DBGACT_SelectISensSrc()
{
	Int16U ISrc = DataTable[REG_DBG_STATE];
	
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
		case SELECT_LV_R0:
			{
				LL_SetStateRanges(LV_CTRL_RANGE_0, true);
				//
				LL_SetStateRanges(LV_CTRL_RANGE_1, false);
				LL_SetStateRanges(LV_CTRL_RANGE_2, false);
				LL_SetStateRanges(LV_CTRL_RANGE_3, false);
			}
			break;
			
		case SELECT_LV_R1:
			{
				LL_SetStateRanges(LV_CTRL_RANGE_1, true);
				//
				LL_SetStateRanges(LV_CTRL_RANGE_0, false);
				LL_SetStateRanges(LV_CTRL_RANGE_2, false);
				LL_SetStateRanges(LV_CTRL_RANGE_3, false);
			}
			break;
			
		case SELECT_LV_R2:
			{
				LL_SetStateRanges(LV_CTRL_RANGE_2, true);
				//
				LL_SetStateRanges(LV_CTRL_RANGE_0, false);
				LL_SetStateRanges(LV_CTRL_RANGE_1, false);
				LL_SetStateRanges(LV_CTRL_RANGE_3, false);
			}
			break;
			
		case SELECT_LV_R3:
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
		case SELECT_HV_R0:
			{
				LL_SetStateRanges(HV_CTRL_RANGE_0, false);
				//
				LL_SetStateRanges(HV_CTRL_RANGE_1, true);
				LL_SetStateRanges(HV_CTRL_RANGE_2, true);
			}
			break;
			
		case SELECT_HV_R1:
			{
				LL_SetStateRanges(HV_CTRL_RANGE_1, false);
				//
				LL_SetStateRanges(HV_CTRL_RANGE_0, true);
				LL_SetStateRanges(HV_CTRL_RANGE_2, true);
			}
			break;
			
		case SELECT_HV_R2:
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

void DBGACT_TestVWaveform()
{
	uint16_t i = 0;
	
	LL_SelectDACx(SELECT_DAC_LV);
	do
	{
		LL_WriteDAC_LH(i | DAC_SELECT_CHV);
		i++;
	}
	while(i <= DAC_MAX_VALUE);
	i--;
	CONTROL_UpdateWatchDog();
	do
	{
		LL_WriteDAC_LH(i | DAC_SELECT_CHV);
	}
	while(i--);
	CONTROL_UpdateWatchDog();

	LL_SelectDACx(SELECT_DAC_NONE);

}
//-----------------------------

void DBGACT_TestIWaveform()
{
	uint16_t i = 0;

	LL_SelectDACx(SELECT_DAC_LV);
	do
	{
		LL_WriteDAC_LH((DAC_MAX_VALUE - i) | DAC_SELECT_CHI);
		i++;
	}
	while(i <= DAC_MAX_VALUE);
	i--;
	CONTROL_UpdateWatchDog();
	do
	{
		LL_WriteDAC_LH((DAC_MAX_VALUE - i) | DAC_SELECT_CHI);
	}
	while(i--);
	CONTROL_UpdateWatchDog();
	
	LL_SelectDACx(SELECT_DAC_NONE);
	
}
//-----------------------------

void DBGACT_SelectVRange() {
	Int16U Range = DataTable[REG_DBG_STATE];

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
