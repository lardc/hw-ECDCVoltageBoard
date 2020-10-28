#ifndef __REGULATOR_H
#define __REGULATOR_H

// Include
#include "stdinc.h"

// Types
typedef uint16_t (*FUNC_CallbackSetControl)(float Value);

typedef struct __RegulatorResult
{
	float Setpoint;
	float Control;
	uint16_t RawControl;
	bool FollowingError;
} RegulatorResult, *pRegulatorResult;

// Functions
//
RegulatorResult REGULATOR_Cycle();
void REGULATOR_ActivateVoltage(FUNC_CallbackSetControl ControlFunction);
void REGULATOR_ActivateCurrent(FUNC_CallbackSetControl ControlFunction);
void REGULATOR_SetTargetMax(float TargetMaxValue);
void REGULATOR_UpdateSampleValues(float Voltage, float Current);
float REGULATOR_GetLastSampleVoltage();
float REGULATOR_GetLastSampleCurrent();

#endif // __REGULATOR_H
