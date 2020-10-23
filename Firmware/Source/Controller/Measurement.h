#ifndef __MEASUREMENT_H
#define __MEASUREMENT_H

#include "stdinc.h"

Int16U MEASURE_Voltage();
Int16U MEASURE_Current();

void MEASURE_CacheVoltageDAC(float VoltageSetpoint);
void MEASURE_CacheCurrentDAC(float CurrentSetpoint);

void MEASURE_CacheVoltageADC(float VoltageSetpoint);
void MEASURE_CacheCurrentADC(float VoltageSetpoint);

#endif // __MEASUREMENT_H
