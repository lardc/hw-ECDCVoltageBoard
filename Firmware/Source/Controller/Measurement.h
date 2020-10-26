#ifndef __MEASUREMENT_H
#define __MEASUREMENT_H

#include "stdinc.h"

// Functions
float MEASURE_VoltageRaw();
float MEASURE_CurrentRaw();

float MEASURE_Voltage();
float MEASURE_Current();

void MEASURE_WriteVoltageLV(float Value);
void MEASURE_WriteVoltageHV(float Value);

void MEASURE_WriteCurrentLV(float Value);
void MEASURE_WriteCurrentHV(float Value);

void MEASURE_CacheConvertParametersV1();
void MEASURE_CacheConvertParametersV2();
void MEASURE_CacheConvertParametersV3();
void MEASURE_CacheConvertParametersV4();

void MEASURE_CacheConvertParametersI1();
void MEASURE_CacheConvertParametersI2();
void MEASURE_CacheConvertParametersI3();
void MEASURE_CacheConvertParametersI4();

void MEASURE_CacheConvertParametersHVI1();
void MEASURE_CacheConvertParametersHVI2();
void MEASURE_CacheConvertParametersHVI3();
void MEASURE_CacheConvertParametersHVI4();

#endif // __MEASUREMENT_H
