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
//TODO Relay MagicNumber #define?
bool DBGACT_RelayCtrlsOn()
{
	bool_val ReturnValue = false;
	Int16U Relay = DataTable[REG_DBG_STATE];

	switch(Relay)
	{
		case 1:
			{
				LL_SetStateCtrls(RLC_CTRL1,true);
				ReturnValue = true;
			}
			break;

		case 2:
			{
				LL_SetStateCtrls(RLC_CTRL2,true);
				ReturnValue = true;
			}
			break;

		case 3:
			{
				LL_SetStateCtrls(RLC_CTRL3,true);
				ReturnValue = true;
			}
			break;

		case 4:
			{
				LL_SetStateCtrls(RLC_CTRL4,true);
				ReturnValue = true;
			}
			break;

		case 5:
			{
				LL_SetStateCtrls(RLC_CTRL5,true);
				ReturnValue = true;
			}
			break;

		case 6:
			{
				LL_SetStateCtrls(RLC_CTRL6,true);
				ReturnValue = true;
			}
			break;

		case 7:
			{
				LL_SetStateCtrls(RLC_CTRL7,true);
				ReturnValue = true;
			}
			break;

		case 8:
			{
				LL_SetStateCtrls(RLC_CTRL8,true);
				ReturnValue = true;
			}
			break;
	}
	return ReturnValue;
}
//-----------------------------

bool DBGACT_RelayCtrlsOff()
{
	bool_val ReturnValue = false;
	Int16U Relay = DataTable[REG_DBG_STATE];

	switch(Relay)
	{
		case 1:
			{
				LL_SetStateCtrls(RLC_CTRL1,false);
				ReturnValue = true;
			}
			break;

		case 2:
			{
				LL_SetStateCtrls(RLC_CTRL2,false);
				ReturnValue = true;
			}
			break;

		case 3:
			{
				LL_SetStateCtrls(RLC_CTRL3,false);
				ReturnValue = true;
			}
			break;

		case 4:
			{
				LL_SetStateCtrls(RLC_CTRL4,false);
				ReturnValue = true;
			}
			break;

		case 5:
			{
				LL_SetStateCtrls(RLC_CTRL5,false);
				ReturnValue = true;
			}
			break;

		case 6:
			{
				LL_SetStateCtrls(RLC_CTRL6,false);
				ReturnValue = true;
			}
			break;

		case 7:
			{
				LL_SetStateCtrls(RLC_CTRL7,false);
				ReturnValue = true;
			}
			break;

		case 8:
			{
				LL_SetStateCtrls(RLC_CTRL8,false);
				ReturnValue = true;
			}
			break;
	}
	return ReturnValue;
}
//-----------------------------

bool DBGACT_LHVSelectLow()
{
	LL_SetStateCtrls(LV_HV_CTRL1,false);	// set together 1&2
	LL_SetStateCtrls(LV_HV_CTRL2,false);
	return true;
}
//-----------------------------

bool DBGACT_LHVSelectHigh()
{
	LL_SetStateCtrls(LV_HV_CTRL1,true);		// set together 1&2
	LL_SetStateCtrls(LV_HV_CTRL2,true);
	return true;
}
//-----------------------------


bool DBGACT_Ctrls48VEnable()
{
	LL_SetStateCtrls(EN_48V_CTRL,true);
	return true;
}
//-----------------------------

bool DBGACT_Ctrls48VDisable()
{
	LL_SetStateCtrls(EN_48V_CTRL,false);
	return true;
}
//-----------------------------

bool DBGACT_Ctrls350VEnable()
{
	LL_SetStateCtrls(HP_CTRL_350V,true);
	return true;
}
//-----------------------------

bool DBGACT_Ctrls350VDisable()
{
	LL_SetStateCtrls(HP_CTRL_350V,false);
	return true;
}
//-----------------------------

bool DBGACT_SelectRg()
{
	bool_val ReturnValue = false;
	Int16U Range = DataTable[REG_DBG_STATE];

	switch(Range)
	{
		case 1:
			{
				LL_SetStateCtrls(V_HV_CTRL_RANGE_0,false);
				//
				LL_SetStateCtrls(V_HV_CTRL_RANGE_1,true);
				LL_SetStateCtrls(V_HV_CTRL_RANGE_2,true);
				LL_SetStateCtrls(V_HV_CTRL_RANGE_3,true);
				ReturnValue = true;
			}
			break;

		case 2:
			{
				LL_SetStateCtrls(V_HV_CTRL_RANGE_1,false);
				//
				LL_SetStateCtrls(V_HV_CTRL_RANGE_0,true);
				LL_SetStateCtrls(V_HV_CTRL_RANGE_2,true);
				LL_SetStateCtrls(V_HV_CTRL_RANGE_3,true);
				ReturnValue = true;
			}
			break;

		case 3:
			{
				LL_SetStateCtrls(V_HV_CTRL_RANGE_2,false);
				//
				LL_SetStateCtrls(V_HV_CTRL_RANGE_0,true);
				LL_SetStateCtrls(V_HV_CTRL_RANGE_1,true);
				LL_SetStateCtrls(V_HV_CTRL_RANGE_3,true);
				ReturnValue = true;
			}
			break;

		case 4:
			{
				LL_SetStateCtrls(V_HV_CTRL_RANGE_3,false);
				//
				LL_SetStateCtrls(V_HV_CTRL_RANGE_0,true);
				LL_SetStateCtrls(V_HV_CTRL_RANGE_1,true);
				LL_SetStateCtrls(V_HV_CTRL_RANGE_2,true);
				ReturnValue = true;
			}
			break;
	}
	return ReturnValue;
}
//-----------------------------

bool DBGACT_SelectVSensSrc()
{
	bool_val ReturnValue = false;
	Int16U VSrc = DataTable[REG_DBG_STATE];

	switch(VSrc)
	{
		case 1:
			{
				LL_SetStateCtrls(LV_SENS_EN,true);//off&off then ONE on
				LL_SetStateCtrls(HV_SENS_EN,true);
				//
				LL_SetStateCtrls(LV_SENS_EN,false);
				ReturnValue = true;
			}
			break;
		case 2:
			{
				LL_SetStateCtrls(LV_SENS_EN,true); //off&off then ONE on
				LL_SetStateCtrls(HV_SENS_EN,true);
				//
				LL_SetStateCtrls(HV_SENS_EN,false);

				ReturnValue = true;
			}
			break;
	}
	return ReturnValue;
}
//-----------------------------

bool DBGACT_SelectISensSrc()
{
	bool_val ReturnValue = false;
	Int16U ISrc = DataTable[REG_DBG_STATE];

	switch(ISrc)
	{
		case 1:
			{
				LL_SetStateCtrls(LV_CUR_SENS_EN,true);//off&off then ONE on
				LL_SetStateCtrls(HV_CUR_SENS_EN,true);
				//
				LL_SetStateCtrls(LV_CUR_SENS_EN,false);
				ReturnValue = true;
			}
			break;
		case 2:
			{
				LL_SetStateCtrls(LV_CUR_SENS_EN,true); //off&off then ONE on
				LL_SetStateCtrls(HV_CUR_SENS_EN,true);
				//
				LL_SetStateCtrls(HV_CUR_SENS_EN,false);

				ReturnValue = true;
			}
			break;
	}
	return ReturnValue;
}
//-----------------------------

bool DBGACT_SelectDACx()
{
	bool_val ReturnValue = false;
	SelDacX dac = DataTable[REG_DBG_STATE];

	LL_SelectDACx(dac);
	return ReturnValue;
}
//-----------------------------
bool DBGACT_WriteDACx()
{
	bool_val ReturnValue = false;
	uint16_t Data = DataTable[REG_DBG_STATE];

	LL_WriteDAC_LH(Data);
	return ReturnValue;
}

//-----------------------------
bool DBGACT_SelectLVCtrls()
{
	bool_val ReturnValue = false;
	Int16U Range = DataTable[REG_DBG_STATE];

	switch(Range)
	{
		case 1:
			{
				LL_SetStateCtrls(LV_CTRL_RANGE_0,false);
				//
				LL_SetStateCtrls(LV_CTRL_RANGE_1,true);
				LL_SetStateCtrls(LV_CTRL_RANGE_2,true);
				LL_SetStateCtrls(LV_CTRL_RANGE_3,true);
				ReturnValue = true;
			}
			break;

		case 2:
			{
				LL_SetStateCtrls(LV_CTRL_RANGE_1,false);
				//
				LL_SetStateCtrls(LV_CTRL_RANGE_0,true);
				LL_SetStateCtrls(LV_CTRL_RANGE_2,true);
				LL_SetStateCtrls(LV_CTRL_RANGE_3,true);
				ReturnValue = true;
			}
			break;

		case 3:
			{
				LL_SetStateCtrls(LV_CTRL_RANGE_2,false);
				//
				LL_SetStateCtrls(LV_CTRL_RANGE_0,true);
				LL_SetStateCtrls(LV_CTRL_RANGE_1,true);
				LL_SetStateCtrls(LV_CTRL_RANGE_3,true);
				ReturnValue = true;
			}
			break;

		case 4:
			{
				LL_SetStateCtrls(LV_CTRL_RANGE_3,false);
				//
				LL_SetStateCtrls(LV_CTRL_RANGE_0,true);
				LL_SetStateCtrls(LV_CTRL_RANGE_1,true);
				LL_SetStateCtrls(LV_CTRL_RANGE_2,true);
				ReturnValue = true;
			}
			break;
	}
	return ReturnValue;
}
//-----------------------------

//-----------------------------
bool DBGACT_SelectHVCtrls()
{
	bool_val ReturnValue = false;
	Int16U Range = DataTable[REG_DBG_STATE];

	switch(Range)
	{
		case 1:
			{
				LL_SetStateCtrls(HV_CTRL_RANGE_0,false);
				//
				LL_SetStateCtrls(HV_CTRL_RANGE_1,true);
				LL_SetStateCtrls(HV_CTRL_RANGE_2,true);
				ReturnValue = true;
			}
			break;

		case 2:
			{
				LL_SetStateCtrls(HV_CTRL_RANGE_1,false);
				//
				LL_SetStateCtrls(HV_CTRL_RANGE_0,true);
				LL_SetStateCtrls(HV_CTRL_RANGE_2,true);
				ReturnValue = true;
			}
			break;

		case 3:
			{
				LL_SetStateCtrls(HV_CTRL_RANGE_2,false);
				//
				LL_SetStateCtrls(HV_CTRL_RANGE_0,true);
				LL_SetStateCtrls(HV_CTRL_RANGE_1,true);
				ReturnValue = true;
			}
			break;
	}
	return ReturnValue;
}
//-----------------------------
