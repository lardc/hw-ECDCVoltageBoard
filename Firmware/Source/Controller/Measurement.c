// Header
#include "Measurement.h"

// Includes
#include "DataTable.h"
#include "DeviceObjectDictionary.h"
#include "Global.h"
#include "ZwADC.h"

// Types
typedef struct __DACConvertParameters
{
	float K;
	float Offset;
} DACConvertParameters, *pDACConvertParameters;

// Variables
static DACConvertParameters VoltageDAC, CurrentDAC;

// Forward functions
void MEASURE_CacheDACx(pDACConvertParameters Storage, uint16_t RegK_N, uint16_t RegK_D, uint16_t RegOffset);
uint16_t MEASURE_ConvertXToDAC(DACConvertParameters Storage, float Value);

// Functions
Int16U MEASURE_Voltage()
{
	Int16U ReturnValue;
	//dummy read;
	ADC_Measure(ADC2, ADC_CHANEL_V);
	ReturnValue = ADC_Measure(ADC2, ADC_CHANEL_V);
	ReturnValue += ADC_Measure(ADC2, ADC_CHANEL_V);
	ReturnValue += ADC_Measure(ADC2, ADC_CHANEL_V);

	return ReturnValue/3;
}
//------------------------------------------

Int16U MEASURE_Current()
{
	Int16U ReturnValue;
	//dummy read;
	ADC_Measure(ADC1, ADC_CHANEL_I);
	ReturnValue = ADC_Measure(ADC1, ADC_CHANEL_I);
	ReturnValue += ADC_Measure(ADC1, ADC_CHANEL_I);
	ReturnValue += ADC_Measure(ADC1, ADC_CHANEL_I);

	return ReturnValue/3;
}
//------------------------------------------

uint16_t MEASURE_ConvertXToDAC(DACConvertParameters Storage, float Value)
{
	float result = (Value / Storage.K + Storage.Offset) / DAC_REF_VOLTAGE * DAC_MAX_RESOLUTION;
	return (result > 0) ? (uint16_t)result : 0;
}
//------------------------------------------

uint16_t MEASURE_ConvertVoltageToDAC(float Value)
{
	return MEASURE_ConvertXToDAC(VoltageDAC, Value);
}
//------------------------------------------

uint16_t MEASURE_ConvertCurrentToDAC(float Value)
{
	return MEASURE_ConvertXToDAC(CurrentDAC, Value);
}
//------------------------------------------

void MEASURE_CacheDACx(pDACConvertParameters Storage, uint16_t RegK_N, uint16_t RegK_D, uint16_t RegOffset)
{
	Storage->K = (float)DataTable[RegK_N] / DataTable[RegK_D];
	Storage->Offset = (float)((int16_t)DataTable[RegOffset]);
}
//------------------------------------------

void MEASURE_CacheCurrentDAC(float CurrentSetpoint)
{
	if(CurrentSetpoint <= DataTable[REG_I_RANGE1_LIMIT])
	{
		MEASURE_CacheDACx(&CurrentDAC, REG_DAC_I1_CONV_K_N, REG_DAC_I1_CONV_K_D, REG_DAC_I1_OFFSET);
	}
	else if(CurrentSetpoint <= DataTable[REG_I_RANGE2_LIMIT])
	{
		MEASURE_CacheDACx(&CurrentDAC, REG_DAC_I2_CONV_K_N, REG_DAC_I2_CONV_K_D, REG_DAC_I2_OFFSET);
	}
	else if(CurrentSetpoint <= DataTable[REG_I_RANGE3_LIMIT])
	{
		MEASURE_CacheDACx(&CurrentDAC, REG_DAC_I3_CONV_K_N, REG_DAC_I3_CONV_K_D, REG_DAC_I3_OFFSET);
	}
	else
		MEASURE_CacheDACx(&CurrentDAC, REG_DAC_I4_CONV_K_N, REG_DAC_I4_CONV_K_D, REG_DAC_I4_OFFSET);
}
//------------------------------------------

void MEASURE_CacheVoltageDAC(float VoltageSetpoint)
{
	if(VoltageSetpoint <= DataTable[REG_V_RANGE1_LIMIT])
	{
		MEASURE_CacheDACx(&VoltageDAC, REG_DAC_V1_CONV_K_N, REG_DAC_V1_CONV_K_D, REG_DAC_V1_OFFSET);
	}
	else if(VoltageSetpoint <= DataTable[REG_V_RANGE2_LIMIT])
	{
		MEASURE_CacheDACx(&VoltageDAC, REG_DAC_V2_CONV_K_N, REG_DAC_V2_CONV_K_D, REG_DAC_V2_OFFSET);
	}
	else if(VoltageSetpoint <= DataTable[REG_V_RANGE3_LIMIT])
	{
		MEASURE_CacheDACx(&VoltageDAC, REG_DAC_V3_CONV_K_N, REG_DAC_V3_CONV_K_D, REG_DAC_V3_OFFSET);
	}
	else
		MEASURE_CacheDACx(&VoltageDAC, REG_DAC_V4_CONV_K_N, REG_DAC_V4_CONV_K_D, REG_DAC_V4_OFFSET);
}
//------------------------------------------
