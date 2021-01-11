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

typedef struct __VIPair
{
	float Voltage;
	float Current;
} VIPair, *pVIPair;

typedef struct __RegulatorSettings
{
	float TargetMax;
	float RiseStep;
	float RiseFrontLength;
	float TargetValue;
	float TargetValuePrev;
	float SampleValue;
	float ErrorI;
	float Kp;
	float Ki;
	float Control;
	float OutputReadyThreshold;
	bool FEActive;
	bool CurrentCutOffEnabled;
	uint16_t CurrentCutoffCtrlDelayCounter;
	uint16_t CurrentCutoffCtrlDelayMax;
	uint16_t FECounter;
	uint16_t FECounterMax;
	float FEThreshold;
	FUNC_CallbackSetControl SetControl;
} RegulatorSettings, *pRegulatorSettings;

// Variables
//
pRegulatorSettings ActiveRegulator;

// Functions
//
RegulatorResult REGULATOR_Cycle();
void REGULATOR_ActivateVoltage(FUNC_CallbackSetControl ControlFunction);
void REGULATOR_ActivateCurrent(FUNC_CallbackSetControl ControlFunction);
void REGULATOR_SetTargetMax(float TargetMaxValue);
void REGULATOR_UpdateSampleValues(float Voltage, float Current);
VIPair REGULATOR_GetFilteredSampleResult();

#endif // __REGULATOR_H
