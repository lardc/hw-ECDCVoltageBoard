#ifndef __MEASUREMENT_H
#define __MEASUREMENT_H

#include "stdinc.h"

// Functions
float MEASURE_VoltageRaw();
float MEASURE_CurrentRaw();

float MEASURE_Voltage();
float MEASURE_Current();

void MEASURE_CacheConvertParameters(float VoltageSetpoint, float CurrentSetpoint);

#endif // __MEASUREMENT_H
