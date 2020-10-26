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
	float TargetMax;
	float RiseRate;
	float TargetValue;
	float TargetValuePrev;
	float SampleValue;
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
		uint16_t RegP, uint16_t RegI, uint16_t RiseRateReg);

// Functions
//
void REGULATOR_Cycle()
{
	float ControlI = 0;
	float Error = ActiveRegulator->TargetValuePrev - ActiveRegulator->SampleValue;

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

	// Обновление уставки
	ActiveRegulator->TargetValue += ActiveRegulator->RiseRate;
	if(ActiveRegulator->TargetValue > ActiveRegulator->TargetMax)
		ActiveRegulator->TargetValue = ActiveRegulator->TargetMax;

	// Применение значения
	ActiveRegulator->SetControl(ActiveRegulator->Control);
}
// ----------------------------------------

void REGULATOR_ActivateX(pRegulatorSettings ActiveRegulator, FUNC_CallbackSetControl ControlFunction,
		uint16_t RegP, uint16_t RegI, uint16_t RiseRateReg)
{
	ActiveRegulator->Kp = (float)DataTable[RegP] / 1000;
	ActiveRegulator->Ki = (float)DataTable[RegI] / 1000;
	ActiveRegulator->SetControl = ControlFunction;
	ActiveRegulator->RiseRate = (float)DataTable[RiseRateReg] * REGLTR_PERIOD / 1000;

	ActiveRegulator->Control = 0;
	ActiveRegulator->ErrorI = 0;
	ActiveRegulator->TargetValue = 0;
	ActiveRegulator->TargetValuePrev = 0;
	ActiveRegulator->TargetMax = 0;
}
// ----------------------------------------

void REGULATOR_ActivateVoltage(FUNC_CallbackSetControl ControlFunction)
{
	ActiveRegulator = &VoltageRegulator;
	REGULATOR_ActivateX(ActiveRegulator, ControlFunction, REG_VOLTAGE_KP, REG_VOLTAGE_KI, REG_VOLTAGE_RISE_RATE);
}
// ----------------------------------------

void REGULATOR_ActivateCurrent(FUNC_CallbackSetControl ControlFunction)
{
	ActiveRegulator = &CurrentRegulator;
	REGULATOR_ActivateX(ActiveRegulator, ControlFunction, REG_CURRENT_KP, REG_CURRENT_KI, REG_CURRENT_RISE_RATE);
}
// ----------------------------------------

void REGULATOR_SetTargetMax(float TargetMaxValue)
{
	ActiveRegulator->TargetMax = TargetMaxValue;
}
// ----------------------------------------

void REGULATOR_UpdateSampleValues(float Voltage, float Current)
{
	VoltageRegulator.SampleValue = Voltage;
	CurrentRegulator.SampleValue = Current;
}
// ----------------------------------------
