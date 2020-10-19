#include "Measurement.h"
#include "DataTable.h"
#include "DeviceObjectDictionary.h"
#include "Global.h"
#include "ZwADC.h"

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
