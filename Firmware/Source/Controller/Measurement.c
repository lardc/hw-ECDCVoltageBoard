// Header
#include "Measurement.h"

// Includes
#include "DataTable.h"
#include "DeviceObjectDictionary.h"
#include "Global.h"
#include "ZwADC.h"

// Definitions
#define ADC_TO_VOLTAGE		0
#define ADC_TO_CURRENT		1

// Types
typedef struct __DACConvertParameters
{
	float K;
	float Offset;
} DACConvertParameters, *pDACConvertParameters;

typedef struct __ADCConvertParameters
{
	float K;
	float Offset;
	float P2;
	float P1;
	float P0;
} ADCConvertParameters, *pADCConvertParameters;

// Variables
static DACConvertParameters VoltageDAC, CurrentDAC;
static ADCConvertParameters VoltageADC, CurrentADC;
static float ShuntResistance;

// Forward functions
void MEASURE_CacheDACx(pDACConvertParameters Storage, uint16_t RegK_N, uint16_t RegK_D, uint16_t RegOffset);
float MEASURE_ConvertADCToX(ADCConvertParameters Storage, float Value, bool ADCToCurrent);
void MEASURE_CacheADCx(pADCConvertParameters Storage, uint16_t RegK_N, uint16_t RegK_D, uint16_t RegOffset,
		uint16_t RegP2, uint16_t RegP1, uint16_t RegP0);
void MEASURE_CacheVoltageDAC(float VoltageSetpoint);
void MEASURE_CacheCurrentDAC(float CurrentSetpoint);
void MEASURE_CacheVoltageADC(float VoltageSetpoint);
void MEASURE_CacheCurrentADC(float VoltageSetpoint);
void MEASURE_CacheCurrentShunt(float CurrentSetpoint);
uint16_t MEASURE_ConvertVoltageToDAC(float Value);
uint16_t MEASURE_ConvertCurrentToDAC(float Value);
float MEASURE_ConvertADCToVoltage(float Value);
float MEASURE_ConvertADCToCurrent(float Value);
float MEASURE_SampleX(ADC_TypeDef *ADCx, uint16_t Channel);

// Functions
float MEASURE_SampleX(ADC_TypeDef *ADCx, uint16_t Channel)
{
	// dummy sample
	ADC_Measure(ADCx, Channel);

	float result = 0;
	for(uint8_t i = 0; i < ADC_AVG_COUNT; ++i)
		result += (float)ADC_Measure(ADCx, Channel);

	return result / ADC_AVG_COUNT;
}
//------------------------------------------

float MEASURE_VoltageRaw()
{
	return MEASURE_SampleX(ADC2, ADC_CHANEL_V);
}
//------------------------------------------

float MEASURE_CurrentRaw()
{
	return MEASURE_SampleX(ADC1, ADC_CHANEL_I);
}
//------------------------------------------

float MEASURE_Voltage()
{
	return MEASURE_ConvertADCToVoltage(MEASURE_VoltageRaw());
}
//------------------------------------------

float MEASURE_Current()
{
	return MEASURE_ConvertADCToCurrent(MEASURE_CurrentRaw());
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

void MEASURE_CacheADCx(pADCConvertParameters Storage, uint16_t RegK_N, uint16_t RegK_D, uint16_t RegOffset,
		uint16_t RegP2, uint16_t RegP1, uint16_t RegP0)
{
	Storage->K = (float)DataTable[RegK_N] / DataTable[RegK_D];
	Storage->Offset = (float)((int16_t)DataTable[RegOffset]);

	Storage->P2 = (float)((int16_t)DataTable[RegP2]) / 1e6;
	Storage->P1 = (float)DataTable[RegP1] / 1000;
	Storage->P0 = (float)((int16_t)DataTable[RegP0]);
}
//------------------------------------------

void MEASURE_CacheVoltageADC(float VoltageSetpoint)
{
	if(VoltageSetpoint <= DataTable[REG_V_RANGE1_LIMIT])
	{
		MEASURE_CacheADCx(&VoltageADC, REG_ADC_V1_CONV_K_N, REG_ADC_V1_CONV_K_D, REG_ADC_V1_CONV_OFFSET,
				REG_ADC_V1_FINE_P2, REG_ADC_V1_FINE_P1, REG_ADC_V1_FINE_P0);
	}
	else if(VoltageSetpoint <= DataTable[REG_V_RANGE2_LIMIT])
	{
		MEASURE_CacheADCx(&VoltageADC, REG_ADC_V2_CONV_K_N, REG_ADC_V2_CONV_K_D, REG_ADC_V2_CONV_OFFSET,
				REG_ADC_V2_FINE_P2, REG_ADC_V2_FINE_P1, REG_ADC_V2_FINE_P0);
	}
	else if(VoltageSetpoint <= DataTable[REG_V_RANGE3_LIMIT])
	{
		MEASURE_CacheADCx(&VoltageADC, REG_ADC_V3_CONV_K_N, REG_ADC_V3_CONV_K_D, REG_ADC_V3_CONV_OFFSET,
				REG_ADC_V3_FINE_P2, REG_ADC_V3_FINE_P1, REG_ADC_V3_FINE_P0);
	}
	else
		MEASURE_CacheADCx(&VoltageADC, REG_ADC_V4_CONV_K_N, REG_ADC_V4_CONV_K_D, REG_ADC_V4_CONV_OFFSET,
				REG_ADC_V4_FINE_P2, REG_ADC_V4_FINE_P1, REG_ADC_V4_FINE_P0);
}
//------------------------------------------

void MEASURE_CacheCurrentADC(float CurrentSetpoint)
{
	if(CurrentSetpoint <= DataTable[REG_I_RANGE1_LIMIT])
	{
		MEASURE_CacheADCx(&CurrentADC, REG_ADC_I1_CONV_K_N, REG_ADC_I1_CONV_K_D, REG_ADC_I1_CONV_OFFSET,
				REG_ADC_I1_FINE_P2, REG_ADC_I1_FINE_P1, REG_ADC_I1_FINE_P0);
	}
	else if(CurrentSetpoint <= DataTable[REG_I_RANGE2_LIMIT])
	{
		MEASURE_CacheADCx(&CurrentADC, REG_ADC_I2_CONV_K_N, REG_ADC_I2_CONV_K_D, REG_ADC_I2_CONV_OFFSET,
				REG_ADC_I2_FINE_P2, REG_ADC_I2_FINE_P1, REG_ADC_I2_FINE_P0);
	}
	else if(CurrentSetpoint <= DataTable[REG_I_RANGE3_LIMIT])
	{
		MEASURE_CacheADCx(&CurrentADC, REG_ADC_I3_CONV_K_N, REG_ADC_I3_CONV_K_D, REG_ADC_I3_CONV_OFFSET,
				REG_ADC_I3_FINE_P2, REG_ADC_I3_FINE_P1, REG_ADC_I3_FINE_P0);
	}
	else
		MEASURE_CacheADCx(&CurrentADC, REG_ADC_I4_CONV_K_N, REG_ADC_I4_CONV_K_D, REG_ADC_I4_CONV_OFFSET,
				REG_ADC_I4_FINE_P2, REG_ADC_I4_FINE_P1, REG_ADC_I4_FINE_P0);
}
//------------------------------------------

float MEASURE_ConvertADCToX(ADCConvertParameters Storage, float Value, bool ADCToCurrent)
{
	float tmp = (Value / ADC_MAX_RESOLUTION * ADC_REF_VOLTAGE + Storage.Offset) * Storage.K;
	if(ADCToCurrent)
		tmp /= ShuntResistance;
	tmp = tmp * tmp * Storage.P2 + tmp * Storage.P1 + Storage.P0;
	return (tmp > 0) ? tmp : 0;
}
//------------------------------------------

float MEASURE_ConvertADCToVoltage(float Value)
{
	return MEASURE_ConvertADCToX(VoltageADC, Value, ADC_TO_VOLTAGE);
}
//------------------------------------------

float MEASURE_ConvertADCToCurrent(float Value)
{
	return MEASURE_ConvertADCToX(CurrentADC, Value, ADC_TO_CURRENT);
}
//------------------------------------------

void MEASURE_CacheCurrentShunt(float CurrentSetpoint)
{
	if(CurrentSetpoint <= DataTable[REG_I_RANGE1_LIMIT])
	{
		ShuntResistance = DataTable[REG_I_RANGE1_RES];
	}
	else if(CurrentSetpoint <= DataTable[REG_I_RANGE2_LIMIT])
	{
		ShuntResistance = DataTable[REG_I_RANGE2_RES];
	}
	else if(CurrentSetpoint <= DataTable[REG_I_RANGE3_LIMIT])
	{
		ShuntResistance = DataTable[REG_I_RANGE3_RES];
	}
	else
		ShuntResistance = DataTable[REG_I_RANGE4_RES];
}
//------------------------------------------

void MEASURE_CacheConvertParameters(float VoltageSetpoint, float CurrentSetpoint)
{
	MEASURE_CacheVoltageDAC(VoltageSetpoint);
	MEASURE_CacheVoltageADC(VoltageSetpoint);

	MEASURE_CacheCurrentDAC(CurrentSetpoint);
	MEASURE_CacheCurrentADC(CurrentSetpoint);

	MEASURE_CacheCurrentShunt(CurrentSetpoint);
}
//------------------------------------------
