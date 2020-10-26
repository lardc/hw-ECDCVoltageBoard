#ifndef __REGULATOR_H
#define __REGULATOR_H

// Include
#include "stdinc.h"

// Types
typedef void (*FUNC_CallbackSetControl)(float Value);

// Functions
//
void REGULATOR_Cycle();
void REGULATOR_ActivateVoltage(FUNC_CallbackSetControl ControlFunction);
void REGULATOR_ActivateCurrent(FUNC_CallbackSetControl ControlFunction);
void REGULATOR_SetTargetMax(float TargetMaxValue);
void REGULATOR_UpdateSampleValues(float Voltage, float Current);

#endif // __REGULATOR_H
