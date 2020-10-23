#ifndef __MEASUREMENT_H
#define __MEASUREMENT_H

#include "stdinc.h"

// Functions
float MEASURE_VoltageRaw();
float MEASURE_CurrentRaw();

float MEASURE_Voltage();
float MEASURE_Current();

void MEASURE_CacheVoltageDAC(float VoltageSetpoint);
void MEASURE_CacheCurrentDAC(float CurrentSetpoint);

void MEASURE_CacheVoltageADC(float VoltageSetpoint);
void MEASURE_CacheCurrentADC(float VoltageSetpoint);

#endif // __MEASUREMENT_H
