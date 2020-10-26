#ifndef __REGULATOR_H
#define __REGULATOR_H

// Include
#include "stdinc.h"

// Types
typedef void (*FUNC_CallbackSetControl)(float Value);

// Functions
//
void REGULATOR_Cycle(float SampleValue);
void REGULATOR_ActivateVoltage(FUNC_CallbackSetControl ControlFunction);
void REGULATOR_ActivateCurrent(FUNC_CallbackSetControl ControlFunction);
void REGULATOR_UpdateTarget(float TargetValue);

#endif // __REGULATOR_H
