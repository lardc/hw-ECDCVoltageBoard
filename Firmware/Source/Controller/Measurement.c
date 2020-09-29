#include "Measurement.h"
#include "DataTable.h"
#include "DeviceObjectDictionary.h"
#include "Global.h"
#include "ZwADC.h"

Int16U MEASURE_Voltage()
{
	return ADC_Measure(ADC2, 1);
}

Int16U MEASURE_Current()
{
	return ADC_Measure(ADC1, 1);
}
