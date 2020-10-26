// Header
#include "Global.h"
#include "Controller.h"
#include "LowLevel.h"
#include "VoltageBoard.h"
#include "DataTable.h"

bool VB_SaveOutputParameters(ControllerConfig *Config)
{
	Config->OutputLine = DataTable[DCV_REG_OUTPUT_LINE];
	Config->OutputType = DataTable[DCV_REG_OUTPUT_TYPE];
	Config->OutputMode = DataTable[DCV_REG_OUTPUT_MODE];
	Config->PulseTime = DataTable[DCV_REG_PULSE_LENGTH];

	Config->VoltageSetpoint = (float)DT_Read32(DCV_REG_VOLTAGE_SETPOINT, DCV_REG_VOLTAGE_SETPOINT_32);
	Config->CurrentSetpoint = (float)DT_Read32(DCV_REG_CURRENT_SETPOINT, DCV_REG_CURRENT_SETPOINT_32);

	return !(Config->VoltageSetpoint > VB_VOUT_MAX || Config->VoltageSetpoint < VB_VOUT_MIN ||
			Config->CurrentSetpoint > VB_IOUT_MAX || Config->VoltageSetpoint < VB_IOUT_MIN);
}
//------------------------------------------

void VB_EnableVoltageChannel(ControllerConfig *Config)
{
	do
	{
		if((Config->VSet >= VRANGE_0V20_MIN) && (Config->VSet < VRANGE_0V20_MAX))
		{
			Config->VChanel = CHANEL_V200;
			LL_SelectVOutMaxV200();
			break;
		}
		if((Config->VSet >= VRANGE_2V00_MIN) && (Config->VSet < VRANGE_2V00_MAX))
		{
			Config->VChanel = CHANEL_2V00;
			LL_SelectVOutMax2V00();
			break;
		}
		if((Config->VSet >= VRANGE_20V0_MIN) && (Config->VSet < VRANGE_20V0_MAX))
		{
			Config->VChanel = CHANEL_20V0;
			LL_SelectVOutMax20V0();
			break;
		}
		if((Config->VSet >= VRANGE_270V_MIN) && (Config->VSet < VRANGE_270V_MAX))
		{
			Config->VChanel = CHANEL_270V;
			//фиктивное переключение низковольтного канала
			LL_SelectVOutMax20V0();
			break;
		}
		Config->VChanel = CHANEL_NONE;
		//фиктивное переключение низковольтного канала
		LL_SelectVOutMaxV200();
	}
	while(0);

	switch (Config->VChanel)
	{
		case CHANEL_V200:
		case CHANEL_2V00:
		case CHANEL_20V0:
			// отключено LL_SelectDACx(SELECT_DAC_LV);
			//Issue: disable 350V & delay
			break;
		case CHANEL_270V:
			// отключено LL_SelectDACx(SELECT_DAC_HV);
			//Issue: enable 350V & delay
			break;
		default:
			// отключено LL_SelectDACx(SELECT_DAC_NONE);
			break;
	}
}
//---------------------

void VB_EnableCurrentChannel(ControllerConfig *Config)
{
	do
	{
		if((Config->CurrSet >= IRANGE_R1_MIN) && (Config->CurrSet < IRANGE_R1_MAX))
		{
			Config->CurrChanel = CHANEL_LV_R1;
			LL_SelectRs27K();
			break;
		}

		if((Config->CurrSet >= IRANGE_R2_MIN) && (Config->CurrSet < IRANGE_R2_MAX))
		{
			Config->CurrChanel = CHANEL_LV_R2;
			LL_SelectRs2K7();
			break;
		}

		if((Config->CurrSet >= IRANGE_R3_MIN) && (Config->CurrSet < IRANGE_R3_MAX))
		{
			Config->CurrChanel = CHANEL_LV_R3;
			LL_SelectRsK27();
			break;
		}

		if((Config->CurrSet >= IRANGE_R4_MIN) && (Config->CurrSet < IRANGE_R4_MAX))
		{
			Config->CurrChanel = CHANEL_LV_R4;
			LL_SelectRsK020();
			break;
		}
		//если значение вне допустимого диапазона
		Config->CurrChanel = CHANEL_LV_R4;
		//максимальный ток
		LL_SelectRsK020();
	}
	while(0);
}
//---------------------

void VB_RelayCommutation(ControllerConfig *Config)
{
//all OFF
	LL_RelayCtrls(RELAY_BUS, false);
	LL_RelayCtrls(RELAY_PS1, false);
	LL_RelayCtrls(RELAY_PS2, false);
	LL_RelayCtrls(RELAY_CTRL, false);
//POT_CTRL+-
	LL_RelayCtrls(RELAY_POT_CTRLN, false);
	LL_RelayCtrls(RELAY_POT_CTRLP, false);

	switch (Config->VChanel)
	{
		case CHANEL_V200:
		case CHANEL_2V00:
		case CHANEL_20V0:
			LL_RelayCtrls(RELAY_LV_HV_CTRL1, false);
			LL_RelayCtrls(RELAY_LV_HV_CTRL2, false);
			LL_RelayCtrls(RELAY_POT, false);
			break;
		case CHANEL_270V:
			LL_RelayCtrls(RELAY_LV_HV_CTRL1, true);
			LL_RelayCtrls(RELAY_LV_HV_CTRL2, true);
			LL_RelayCtrls(RELAY_POT, true);
			break;
		case CHANEL_NONE:
			break;
	}

	if(Config->VChanel != CHANEL_NONE)
	{
		LL_RelayCtrls(Config->OutLine, true);
	}
}
//---------------------
