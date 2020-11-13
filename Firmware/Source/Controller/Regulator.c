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
	uint16_t FECounter;
	uint16_t FECounterMax;
	float FEThreshold;
	FUNC_CallbackSetControl SetControl;
} RegulatorSettings, *pRegulatorSettings;

// Variables
static RegulatorSettings VoltageRegulator, CurrentRegulator;
static pRegulatorSettings ActiveRegulator;
static VIPair AverageResult[REGLTR_AVERAGE_RESULT_NUM];
static uint16_t AverageCounter, AverageResultCounter;
static bool OutputReady;

// Forward functions
void REGULATOR_SaveSample(float Voltage, float Current);
void REGULATOR_ActivateX(pRegulatorSettings ActiveRegulator, FUNC_CallbackSetControl ControlFunction,
		uint16_t RegP, uint16_t RegI, uint16_t RiseFrontReg);

// Functions
//
RegulatorResult REGULATOR_Cycle()
{
	RegulatorResult result;

	float ControlI = 0;
	float Error = ActiveRegulator->TargetValuePrev - ActiveRegulator->SampleValue;
	float RelativeError = Error / ActiveRegulator->TargetValuePrev;

	// Настройка шага нарастания при первом запуске
	if(ActiveRegulator->RiseStep == 0)
		ActiveRegulator->RiseStep = (ActiveRegulator->TargetMax / ActiveRegulator->RiseFrontLength * REGLTR_PERIOD) / 1000;

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
	ActiveRegulator->TargetValue += ActiveRegulator->RiseStep;
	if(ActiveRegulator->TargetValue > ActiveRegulator->TargetMax)
		ActiveRegulator->TargetValue = ActiveRegulator->TargetMax;

	// Применение значения
	uint16_t RawControl = ActiveRegulator->SetControl(ActiveRegulator->Control);

	// Проверка срабатывания ошибки
	if(ActiveRegulator->FEActive)
	{
		if(RelativeError > ActiveRegulator->FEThreshold)
			ActiveRegulator->FECounter++;
		else
			ActiveRegulator->FECounter = 0;
	}

	// Проверка условия запуска усреднения
	if(RelativeError <= ActiveRegulator->OutputReadyThreshold &&
			ActiveRegulator->TargetValuePrev == ActiveRegulator->TargetMax)
	{
		OutputReady = true;
	}

	// Сбор результатов измерения
	if(OutputReady && AverageResultCounter < REGLTR_AVERAGE_RESULT_NUM)
		++AverageResultCounter;

	// Проверка готовности значений
	if(OutputReady && AverageResultCounter >= REGLTR_AVERAGE_RESULT_NUM)
		DataTable[REG_VOLTAGE_READY] = 1;

	// Формирование возвращаемого результата
	result.RawControl = RawControl;
	result.Control = ActiveRegulator->Control;
	result.Setpoint = ActiveRegulator->TargetValuePrev;
	result.FollowingError = (ActiveRegulator->FEActive &&
			(ActiveRegulator->FECounter >= ActiveRegulator->FECounterMax));

	return result;
}
// ----------------------------------------

void REGULATOR_ActivateX(pRegulatorSettings ActiveRegulator, FUNC_CallbackSetControl ControlFunction,
		uint16_t RegP, uint16_t RegI, uint16_t RiseFrontReg)
{
	ActiveRegulator->Kp = (float)DataTable[RegP] / 1000;
	ActiveRegulator->Ki = (float)DataTable[RegI] / 1000;
	ActiveRegulator->SetControl = ControlFunction;
	ActiveRegulator->RiseFrontLength = (float)DataTable[RiseFrontReg] / 10;
	ActiveRegulator->RiseStep = 0;

	ActiveRegulator->OutputReadyThreshold = (float)DataTable[REG_OUTPUT_READY_THR] / 100;

	ActiveRegulator->FEActive = DataTable[REG_ENABLE_FE];
	ActiveRegulator->FECounter = 0;
	ActiveRegulator->FECounterMax = DataTable[REG_FE_COUNTER_MAX];
	ActiveRegulator->FEThreshold = (float)DataTable[REG_FE_TRIG_LEVEL] / 100;

	ActiveRegulator->Control = 0;
	ActiveRegulator->ErrorI = 0;
	ActiveRegulator->TargetValue = 0;
	ActiveRegulator->TargetValuePrev = 0;
	ActiveRegulator->TargetMax = 0;

	AverageCounter = AverageResultCounter = 0;
	OutputReady = false;
}
// ----------------------------------------

void REGULATOR_ActivateVoltage(FUNC_CallbackSetControl ControlFunction)
{
	ActiveRegulator = &VoltageRegulator;
	REGULATOR_ActivateX(ActiveRegulator, ControlFunction, REG_VOLTAGE_KP, REG_VOLTAGE_KI, REG_VOLTAGE_RISE_FRONT_LEN);
}
// ----------------------------------------

void REGULATOR_ActivateCurrent(FUNC_CallbackSetControl ControlFunction)
{
	ActiveRegulator = &CurrentRegulator;
	REGULATOR_ActivateX(ActiveRegulator, ControlFunction, REG_CURRENT_KP, REG_CURRENT_KI, REG_CURRENT_RISE_FRONT_LEN);
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

	REGULATOR_SaveSample(Voltage, Current);
}
// ----------------------------------------

VIPair REGULATOR_GetFilteredSampleResult()
{
	VIPair Result;
	float AvgVoltage = 0, AvgCurrent = 0;

	for(uint16_t i = 0; i < AverageCounter; ++i)
	{
		AvgVoltage += AverageResult[i].Voltage;
		AvgCurrent += AverageResult[i].Current;
	}

	Result.Voltage = AvgVoltage / AverageCounter;
	Result.Current = AvgCurrent / AverageCounter;
	return Result;
}
// ----------------------------------------

void REGULATOR_SaveSample(float Voltage, float Current)
{
	for(uint16_t i = (REGLTR_AVERAGE_RESULT_NUM - 1); i >= 1; --i)
		AverageResult[i] = AverageResult[i - 1];

	AverageResult[0].Voltage = Voltage;
	AverageResult[0].Current = Current;

	if(AverageCounter < REGLTR_AVERAGE_RESULT_NUM)
		++AverageCounter;
}
// ----------------------------------------
