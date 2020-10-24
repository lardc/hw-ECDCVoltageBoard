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
} RegulatorSettings, *pRegulatorSettings;

// Variables
static RegulatorSettings VoltageRegulator, CurrentRegulator;

// Functions
//
void REGULATOR_CycleX(pRegulatorSettings Regulator, float SampleValue, FUNC_CallbackSetControl CallbackFunc)
{
	float ControlI = 0;
	float Error = Regulator->TargetValuePrev - SampleValue;

	// Расчёт интегральной ошибки
	if(Regulator->Ki)
	{
		Regulator->ErrorI += Error;

		// Проверка насыщения
		if(fabsf(Regulator->ErrorI) > REGLTR_ERROR_I_SAT_H)
			Regulator->ErrorI = (Regulator->ErrorI > 0) ? REGLTR_ERROR_I_SAT_H : -REGLTR_ERROR_I_SAT_H;

		ControlI = Regulator->ErrorI * Regulator->Ki;
	}
	else
	{
		Regulator->ErrorI = 0;
		ControlI = 0;
	}

	// Корректировка управления
	Regulator->Control = Regulator->TargetValue + Error * Regulator->Kp + ControlI;
	Regulator->TargetValuePrev = Regulator->TargetValue;

	// Применение значения
	CallbackFunc(Regulator->Control);
}
// ----------------------------------------
