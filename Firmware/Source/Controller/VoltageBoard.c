﻿// Header
#include "VoltageBoard.h"

// Includes
#include "Global.h"
#include "Controller.h"
#include "LowLevel.h"
#include "DataTable.h"
#include "Measurement.h"
#include "Regulator.h"

// Forward functions
void VB_ConfigVoltageChannel(ControllerConfig *Config);
void VB_ConfigCurrentChannel(ControllerConfig *Config);

// Functions
bool VB_CacheParameters(ControllerConfig *Config)
{
	Config->Problem = PROBLEM_NONE;

	Config->OutputLine = DataTable[DCV_REG_OUTPUT_LINE];
	Config->OutputType = DataTable[DCV_REG_OUTPUT_TYPE];
	Config->OutputMode = DataTable[DCV_REG_OUTPUT_MODE];
	Config->PulseTime = DataTable[DCV_REG_PULSE_LENGTH];

	Config->VoltageSetpoint = (float)DT_Read32(DCV_REG_VOLTAGE_SETPOINT, DCV_REG_VOLTAGE_SETPOINT_32);
	Config->CurrentSetpoint = (float)DT_Read32(DCV_REG_CURRENT_SETPOINT, DCV_REG_CURRENT_SETPOINT_32);
	Config->HWCurrentLimit = Config->CurrentSetpoint * (1 + (float)DataTable[REG_CURRENT_LIMIT_MARGIN] / 100);

	Config->VoltageHighRange = (Config->VoltageSetpoint > DataTable[REG_V_RANGE3_LIMIT]);
	Config->CurrentHighRange = (Config->CurrentSetpoint > DataTable[REG_I_RANGE3_LIMIT]);

	bool result = true;
	// Проверка границ тока и напряжения
	result &= Config->VoltageSetpoint >= VB_VOUT_MIN && Config->VoltageSetpoint <= VB_VOUT_MAX;
	result &= Config->CurrentSetpoint >= VB_IOUT_MIN && Config->CurrentSetpoint <= VB_IOUT_MAX;
	// Провекра границы напряжения для режима источника тока
	if(Config->OutputType == OT_Current)
		result &= Config->VoltageSetpoint <= DataTable[REG_V_RANGE3_LIMIT];

	return result;
}
//------------------------------------------

void VB_ConfigVoltageChannel(ControllerConfig *Config)
{
	// Режим источника напряжения
	if(Config->OutputType == OT_Voltage)
	{
		// Параметры канала напряжения
		if(Config->VoltageSetpoint <= DataTable[REG_V_RANGE1_LIMIT])
		{
			LL_SelectRgK12();
			LL_SelectVOutMaxV200();
			MEASURE_CacheConvertParametersV1();
			REGULATOR_ActivateVoltage(&MEASURE_WriteVoltageLV);
		}
		else if(Config->VoltageSetpoint <= DataTable[REG_V_RANGE2_LIMIT])
		{
			LL_SelectRg7K70();
			LL_SelectVOutMax2V00();
			MEASURE_CacheConvertParametersV2();
			REGULATOR_ActivateVoltage(&MEASURE_WriteVoltageLV);
		}
		else if(Config->VoltageSetpoint <= DataTable[REG_V_RANGE3_LIMIT])
		{
			LL_SelectRg720K();
			LL_SelectVOutMax20V0();
			MEASURE_CacheConvertParametersV3();
			REGULATOR_ActivateVoltage(&MEASURE_WriteVoltageLV);
		}
		else
		{
			LL_SelectRg720K();
			LL_SelectVOutMax20V0();
			MEASURE_CacheConvertParametersV4();
			REGULATOR_ActivateVoltage(&MEASURE_WriteVoltageHV);
		}
		REGULATOR_SetTargetMax(Config->VoltageSetpoint);
	}
	// Режим источника тока
	else
	{
		LL_SelectRg720K();
		LL_SelectVOutMax20V0();
		MEASURE_CacheConvertParametersV3();
	}
}
//------------------------------------------

void VB_ConfigCurrentChannel(ControllerConfig *Config)
{
	bool LowVoltageMode = (Config->VoltageSetpoint <= DataTable[REG_V_RANGE3_LIMIT]);

	if(Config->CurrentSetpoint <= DataTable[REG_I_RANGE1_LIMIT])
	{
		if(LowVoltageMode)
		{
			MEASURE_CacheConvertParametersI1();
			LL_SelectRs27K();
		}
		else
		{
			 MEASURE_CacheConvertParametersHVI1();
			 LL_SelectHV_R1();
		}
	}
	else if(Config->CurrentSetpoint <= DataTable[REG_I_RANGE2_LIMIT])
	{
		if(LowVoltageMode)
		{
			MEASURE_CacheConvertParametersI2();
			LL_SelectRs2K7();
		}
		else
		{
			 MEASURE_CacheConvertParametersHVI2();
			 LL_SelectHV_R2();
		}
	}
	else if(Config->CurrentSetpoint <= DataTable[REG_I_RANGE3_LIMIT])
	{
		if(LowVoltageMode)
		{
			MEASURE_CacheConvertParametersI3();
			LL_SelectRsK27();
		}
		else
		{
			 MEASURE_CacheConvertParametersHVI3();
			 LL_SelectHV_R3();
		}
	}
	else
	{
		if(LowVoltageMode)
		{
			MEASURE_CacheConvertParametersI4();
			LL_SelectRsK020();
		}
		else
		{
			 MEASURE_CacheConvertParametersHVI4();
			 LL_SelectHV_R4();
		}
	}

	if(LowVoltageMode)
		LL_SelectAdcSrcILV();
	else
		LL_SelectAdcSrcIHV();

	// Режим источника тока
	if(Config->OutputType == OT_Current)
	{
		REGULATOR_ActivateCurrent(&MEASURE_WriteCurrentLV);
		REGULATOR_SetTargetMax(Config->CurrentSetpoint);
	}
}
//------------------------------------------

void VB_SetLimitVIOutputs(ControllerConfig *Config)
{
	// Режим формирования напряжения
	if(Config->OutputType == OT_Voltage)
	{
		// Низковольтный
		if(Config->VoltageSetpoint <= DataTable[REG_V_RANGE3_LIMIT])
			MEASURE_WriteCurrentLV(Config->HWCurrentLimit);
		else
			DataTable[REG_DIAG_IHV_DAC] = MEASURE_WriteCurrentHV(Config->HWCurrentLimit);
	}
	// Режим формирования тока
	else
		MEASURE_WriteVoltageLV(DataTable[REG_V_RANGE3_LIMIT]);
}
//------------------------------------------

void VB_RelayCommutation(ControllerConfig *Config)
{
	bool LowVoltageMode = (Config->VoltageSetpoint <= DataTable[REG_V_RANGE3_LIMIT]);
	LL_RelayCtrlsDisconnect();

	switch(Config->OutputLine)
	{
		case DC_BUS_LV:
			{
				LL_RelayCtrls(RELAY_BUS, true);
				if(LowVoltageMode)
					LL_SelectAdcSrc_LowVoltageBUS();
			}
			break;

		case DC_CTRL:
			{
				LL_RelayCtrls(RELAY_CTRL, true);
				if(LowVoltageMode)
					LL_SelectAdcSrc_LowVoltageControl();
			}
			break;

		case PS1:
			{
				LL_RelayCtrls(RELAY_PS1, true);
				if(LowVoltageMode)
					LL_SelectAdcSrc_LowVoltagePS();
			}
			break;

		case PS2:
			{
				LL_RelayCtrls(RELAY_PS2, true);
				if(LowVoltageMode)
					LL_SelectAdcSrc_LowVoltagePS();
			}
			break;

		default:
			break;
	}

	if(!LowVoltageMode)
		LL_SelectAdcSrc_HighVoltage();
}
//------------------------------------------

void VB_ConfigVIChannels(ControllerConfig *Config)
{
	VB_ConfigVoltageChannel(Config);
	VB_ConfigCurrentChannel(Config);
	VB_RelayCommutation(Config);
}
//------------------------------------------
