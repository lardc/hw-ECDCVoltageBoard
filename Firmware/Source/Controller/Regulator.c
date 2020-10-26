// Header
#include "Regulator.h"
// Include
#include "Global.h"
#include "DataTable.h"
#include "DeviceObjectDictionary.h"
#include "math.h"

// Types
typedef struct __RegulatorSettings
{
	float TargetValue;
	float TargetValuePrev;
	float ErrorI;
	float Kp;
	float Ki;
	float Control;
	FUNC_CallbackSetControl SetControl;
} RegulatorSettings, *pRegulatorSettings;

// Variables
static RegulatorSettings VoltageRegulator, CurrentRegulator;
static pRegulatorSettings ActiveRegulator;

// Forward functions
void REGULATOR_ActivateX(pRegulatorSettings ActiveRegulator, FUNC_CallbackSetControl ControlFunction,
		uint16_t RegP, uint16_t RegI);

// Functions
//
void REGULATOR_Cycle(float SampleValue)
{
	float ControlI = 0;
	float Error = ActiveRegulator->TargetValuePrev - SampleValue;

	// Расчёт интегральной ошибки
	if(ActiveRegulator->Ki)
	{
		ActiveRegulator->ErrorI += Error;

		// Проверка насыщения
		if(fabsf(ActiveRegulator->ErrorI) > REGLTR_ERROR_I_SAT_H)
			ActiveRegulator->ErrorI = (ActiveRegulator->ErrorI > 0) ? REGLTR_ERROR_I_SAT_H : -REGLTR_ERROR_I_SAT_H;

		ControlI = ActiveRegulator->ErrorI * ActiveRegulator->Ki;
	}
	else
	{
		ActiveRegulator->ErrorI = 0;
		ControlI = 0;
	}

	// Корректировка управления
	ActiveRegulator->Control = ActiveRegulator->TargetValue + Error * ActiveRegulator->Kp + ControlI;
	ActiveRegulator->TargetValuePrev = ActiveRegulator->TargetValue;

	// Применение значения
	ActiveRegulator->SetControl(ActiveRegulator->Control);
}
// ----------------------------------------

void REGULATOR_ActivateX(pRegulatorSettings ActiveRegulator, FUNC_CallbackSetControl ControlFunction,
		uint16_t RegP, uint16_t RegI)
{
	ActiveRegulator->Kp = (float)DataTable[RegP] / 1000;
	ActiveRegulator->Ki = (float)DataTable[RegI] / 1000;
	ActiveRegulator->SetControl = ControlFunction;

	ActiveRegulator->Control = 0;
	ActiveRegulator->ErrorI = 0;
	ActiveRegulator->TargetValue = 0;
	ActiveRegulator->TargetValuePrev = 0;
}
// ----------------------------------------

void REGULATOR_ActivateVoltage(FUNC_CallbackSetControl ControlFunction)
{
	ActiveRegulator = &VoltageRegulator;
	REGULATOR_ActivateX(ActiveRegulator, ControlFunction, REG_VOLTAGE_KP, REG_VOLTAGE_KI);
}
// ----------------------------------------

void REGULATOR_ActivateCurrent(FUNC_CallbackSetControl ControlFunction)
{
	ActiveRegulator = &CurrentRegulator;
	REGULATOR_ActivateX(ActiveRegulator, ControlFunction, REG_CURRENT_KP, REG_CURRENT_KI);
}
// ----------------------------------------

void REGULATOR_UpdateTarget(float TargetValue)
{
	ActiveRegulator->TargetValue = TargetValue;
}
// ----------------------------------------
