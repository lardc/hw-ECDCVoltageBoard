#ifndef __MEASUREMENT_H
#define __MEASUREMENT_H

#include "stdinc.h"

Int16U MEASURE_Voltage();
Int16U MEASURE_Current();

uint16_t MEASURE_ConvertVoltageToDAC(float Value);
uint16_t MEASURE_ConvertCurrentToDAC(float Value);

void MEASURE_CacheCurrentDAC(float CurrentSetpoint);
void MEASURE_CacheVoltageDAC(float VoltageSetpoint);

#endif // __MEASUREMENT_H
