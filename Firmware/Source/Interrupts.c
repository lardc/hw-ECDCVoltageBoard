﻿// Include
#include "Interrupts.h"
//
#include "Controller.h"
#include "LowLevel.h"
#include "Board.h"
#include "SysConfig.h"
#include "Global.h"
#include "DataTable.h"
#include "DeviceObjectDictionary.h"
#include "Measurement.h"
#include "Regulator.h"
#include "Delay.h"

// Functions
//
void USART1_IRQHandler()
{
	if(ZwSCI_RecieveCheck(USART1))
	{
		ZwSCI_RegisterToFIFO(USART1);
		ZwSCI_RecieveFlagClear(USART1);
	}
}
//-----------------------------------------

void USB_LP_CAN_RX0_IRQHandler()
{
	if(NCAN_RecieveCheck())
	{
		NCAN_RecieveData();
		NCAN_RecieveFlagReset();
	}
}
//-----------------------------------------

void TIM2_IRQHandler()
{
	if(TIM_StatusCheck(TIM2))
	{
		if(CONTROL_IsHighVoltageOutput())
			LL_HVPowerSupplyOutput(false);

		// Задержка выключения Flyback
		DELAY_US(100);

		float Voltage = MEASURE_Voltage();
		float Current = MEASURE_Current();

		if(CONTROL_IsHighVoltageOutput())
			LL_HVPowerSupplyOutput(true);

		REGULATOR_UpdateSampleValues(Voltage, Current);
		RegulatorResult Result = REGULATOR_Cycle();
		CONTROL_EpLog(Current, Voltage, Result.Setpoint, Result.Control, Result.RawControl);

		if(Result.FollowingError)
			CONTROL_ForceRegulatorStop(PROBLEM_FOLLOWING_ERROR);

		TIM_StatusClear(TIM2);
	}
}
//-----------------------------------------

void TIM7_IRQHandler()
{
	static uint16_t LED_BlinkTimeCounter = 0;
	
	if(TIM_StatusCheck(TIM7))
	{
		CONTROL_TimeCounter++;
		if(++LED_BlinkTimeCounter > TIME_LED_BLINK)
		{
			LL_ToggleBoardLED();
			LED_BlinkTimeCounter = 0;
		}
		TIM_StatusClear(TIM7);
	}
}
//-----------------------------------------
