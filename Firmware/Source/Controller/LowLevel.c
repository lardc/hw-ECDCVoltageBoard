// Header
#include "LowLevel.h"
// Include
#include "Board.h"
#include "Delay.h"
#include "Global.h"
#include <string.h>

// Defines
#define DAC_CHANNEL_B		BIT15
#define CTRL_SIZE			3		// Три восьмибитных регистра

// Variables
//
uint8_t CONTROL_UnitCtrls[CTRL_SIZE];
uint8_t CONTROL_UnitRanges;

// Forward functions
void LL_WriteDACx(uint16_t Data, GPIO_PortPinSetting GPIO_LDACx);

// Functions
//
void LL_ToggleBoardLED()
{
	GPIO_Toggle(GPIO_LED);
}
//-----------------------------

void LL_SetStateExtLed(bool State)
{
	GPIO_SetState(GPIO_EXT_LED, State);
}
//-----------------------------

void LL_SetStateLineSync1(bool State)
{
	GPIO_SetState(GPIO_SYNC1_OUT, State);
}
//-----------------------------

void LL_SetStateLineSync2(bool State)
{
	GPIO_SetState(GPIO_SYNC2_OUT, State);
}
//-----------------------------

bool LL_GetStateLineSync1()
{
	return GPIO_GetState(GPIO_SYNC1_IN);
}
//-----------------------------

bool LL_GetStateLineSync2()
{
	return GPIO_GetState(GPIO_SYNC2_IN);
}
//-----------------------------

void LL_HVPowerSupplyOutput(bool State)
{
	GPIO_SetState(GPIO_HVPS_DISABLE, !State);
}
//-----------------------------

// Управление выходами CTRL
void LL_UpdateStateCtrls()
{
	SPI_InvertClockPolarity(SPI1, false);

	for(uint8_t i = CTRL_SIZE; i >= 1; i--)
		SPI_WriteByte8b(SPI1, CONTROL_UnitCtrls[i - 1]);

	GPIO_SetState(GPIO_RCK, true);
	GPIO_SetState(GPIO_RCK, false);
}
//-----------------------------

void LL_ResetStateCtrls()
{
	memset(CONTROL_UnitCtrls, 0, CTRL_SIZE);
	LL_UpdateStateCtrls();
}
//-----------------------------

void LL_SetStateCtrls(SetCtrls Pin, bool State)
{
	uint32_t Nbyte;
	uint32_t Nbit;
	
	Nbyte = Pin / 8;
	Nbit = Pin % 8;
	if(State)
	{
		CONTROL_UnitCtrls[Nbyte] |= 1 << Nbit;
	}
	else
	{
		CONTROL_UnitCtrls[Nbyte] &= ~(1 << Nbit);
	}
	LL_UpdateStateCtrls();
}
//-----------------------------

// Управление выходами RANGE
void LL_UpdateStateRanges()
{
	SPI_InvertClockPolarity(SPI1, false);

	GPIO_SetState(GPIO_SREG_CS, false);
	SPI_WriteByte8b(SPI1, CONTROL_UnitRanges);
	GPIO_SetState(GPIO_SREG_CS, true);
}
//-----------------------------

void LL_ResetStateRanges()
{
	CONTROL_UnitRanges = 0;
	LL_UpdateStateRanges();
}
//-----------------------------

void LL_SetStateRanges(SetRanges Pin, bool State)
{
	uint32_t Nbit;
	
	Nbit = Pin % 8;
	if(State)
	{
		CONTROL_UnitRanges |= 1 << Nbit;
	}
	else
	{
		CONTROL_UnitRanges &= ~(1 << Nbit);
	}
	LL_UpdateStateRanges();
}
//-----------------------------

void LL_WriteDACx(uint16_t Data, GPIO_PortPinSetting GPIO_LDACx)
{
	SPI_InvertClockPolarity(SPI1, true);

	GPIO_SetState(GPIO_DAC_CS, false);
	SPI_WriteByte8b(SPI1, (Data >> 8) & 0xff);
	SPI_WriteByte8b(SPI1, Data & 0xff);
	GPIO_SetState(GPIO_DAC_CS, true);
	DELAY_US(1);

	GPIO_SetState(GPIO_LDACx, false);
	DELAY_US(5);
	GPIO_SetState(GPIO_LDACx, true);
	DELAY_US(5);
}
//-----------------------------

void LL_WriteDACLV_Voltage(uint16_t Data)
{
	LL_WriteDACx(Data & ~DAC_CHANNEL_B, GPIO_LDAC1);
}
//-----------------------------

void LL_WriteDACLV_Current(uint16_t Data)
{
	LL_WriteDACx(Data | DAC_CHANNEL_B, GPIO_LDAC1);
}
//-----------------------------

void LL_WriteDACHV_Voltage(uint16_t Data)
{
	LL_WriteDACx(Data | DAC_CHANNEL_B, GPIO_LDAC2);
}
//-----------------------------

void LL_WriteDACHV_Current(uint16_t Data)
{
	LL_WriteDACx(Data & ~DAC_CHANNEL_B, GPIO_LDAC2);
}
//-----------------------------

void LL_ResetDACOutputs()
{
	LL_WriteDACLV_Voltage(0);
	LL_WriteDACLV_Current(0);
	LL_WriteDACHV_Voltage(0);
	LL_WriteDACHV_Current(0);
}
//-----------------------------

void LL_SelectVOutMaxV200()
{
	LL_SetStateCtrls(LV_RANGE0, true);
	LL_SetStateCtrls(LV_RANGE1, false);
	LL_SetStateCtrls(LV_RANGE2, false);
}
//-----------------------------

void LL_SelectVOutMax2V00()
{
	LL_SetStateCtrls(LV_RANGE0, false);
	LL_SetStateCtrls(LV_RANGE1, true);
	LL_SetStateCtrls(LV_RANGE2, false);
}
//-----------------------------

void LL_SelectVOutMax20V0()
{
	LL_SetStateCtrls(LV_RANGE0, false);
	LL_SetStateCtrls(LV_RANGE1, false);
	LL_SetStateCtrls(LV_RANGE2, true);
}
//-----------------------------

void LL_SelectRs27K()
{
	LL_SetStateRanges(LV_CTRL_RANGE_0, true);
	LL_SetStateRanges(LV_CTRL_RANGE_1, false);
	LL_SetStateRanges(LV_CTRL_RANGE_2, false);
	LL_SetStateRanges(LV_CTRL_RANGE_3, false);
}
//-----------------------------

void LL_SelectRs2K7()
{
	LL_SetStateRanges(LV_CTRL_RANGE_0, false);
	LL_SetStateRanges(LV_CTRL_RANGE_1, false);
	LL_SetStateRanges(LV_CTRL_RANGE_2, false);
	LL_SetStateRanges(LV_CTRL_RANGE_3, true);
}
//-----------------------------

void LL_SelectRsK27()
{
	LL_SetStateRanges(LV_CTRL_RANGE_0, false);
	LL_SetStateRanges(LV_CTRL_RANGE_1, false);
	LL_SetStateRanges(LV_CTRL_RANGE_2, true);
	LL_SetStateRanges(LV_CTRL_RANGE_3, false);
}
//-----------------------------

void LL_SelectRsK020()
{
	LL_SetStateRanges(LV_CTRL_RANGE_0, false);
	LL_SetStateRanges(LV_CTRL_RANGE_1, true);
	LL_SetStateRanges(LV_CTRL_RANGE_2, false);
	LL_SetStateRanges(LV_CTRL_RANGE_3, false);
}
//-----------------------------

void LL_SelectRsNone()
{
	LL_SetStateRanges(LV_CTRL_RANGE_0, false);
	LL_SetStateRanges(LV_CTRL_RANGE_1, false);
	LL_SetStateRanges(LV_CTRL_RANGE_2, false);
	LL_SetStateRanges(LV_CTRL_RANGE_3, false);
}
//-----------------------------

void LL_SelectAdcSrc_LowVoltagePS()
{
	// Выбор внутреннего низковольтного источника потенциального сигнала твердотельными реле
	LL_SetStateCtrls(LV_SENS_EN, true);
	LL_SetStateCtrls(HV_SENS_EN, false);
	LL_SetStateCtrls(POT_COMM_INPUT, false);

	// Выбор низковольтного источника для подачи на выход механическими реле
	LL_SetStateCtrls(LV_HV_CTRL1, false);
	LL_SetStateCtrls(LV_HV_CTRL2, false);

	// Отключение механических реле потенциальных входов
	LL_SetStateCtrls(RLC_POT, false);
	LL_SetStateCtrls(RLC_POT_CRL, false);
}
//-----------------------------

void LL_SelectAdcSrc_LowVoltageX(bool IsControl)
{
	// Выбор внешнего низковольтного источника потенциального сигнала твердотельными реле
	LL_SetStateCtrls(LV_SENS_EN, false);
	LL_SetStateCtrls(HV_SENS_EN, false);
	LL_SetStateCtrls(POT_COMM_INPUT, true);

	// Выбор низковольтного источника для подачи на выход механическими реле
	LL_SetStateCtrls(LV_HV_CTRL1, false);
	LL_SetStateCtrls(LV_HV_CTRL2, false);

	// Включение механических реле потенциальных входов
	if(IsControl)
	{
		LL_SetStateCtrls(RLC_POT, false);
		LL_SetStateCtrls(RLC_POT_CRL, true);
	}
	else
	{
		LL_SetStateCtrls(RLC_POT, true);
		LL_SetStateCtrls(RLC_POT_CRL, false);
	}
}
//-----------------------------

void LL_SelectAdcSrc_LowVoltageControl()
{
	LL_SelectAdcSrc_LowVoltageX(true);
}
//-----------------------------

void LL_SelectAdcSrc_LowVoltageBUS()
{
	LL_SelectAdcSrc_LowVoltageX(false);
}
//-----------------------------

void LL_SelectAdcSrc_HighVoltage()
{
	// Выбор внутреннего высоковольтного источника потенциального сигнала твердотельными реле
	LL_SetStateCtrls(LV_SENS_EN, false);
	LL_SetStateCtrls(HV_SENS_EN, true);
	LL_SetStateCtrls(POT_COMM_INPUT, false);

	// Выбор высоковольтного источника для подачи на выход механическими реле
	LL_SetStateCtrls(LV_HV_CTRL1, true);
	LL_SetStateCtrls(LV_HV_CTRL2, true);

	// Отключение механических реле потенциальных входов
	LL_SetStateCtrls(RLC_POT, false);
	LL_SetStateCtrls(RLC_POT_CRL, false);
}
//-----------------------------

void LL_SelectAdcSrc_Disconnect()
{
	// Отключение всей коммутации с замыканием входа на низковольтный источник
	LL_SelectAdcSrc_LowVoltagePS();
}
//-----------------------------

void LL_SelectRgK12()
{
	LL_SetStateCtrls(V_HV_CTRL_RANGE_0, true);
	//
	LL_SetStateCtrls(V_HV_CTRL_RANGE_1, false);
	LL_SetStateCtrls(V_HV_CTRL_RANGE_2, false);
	LL_SetStateCtrls(V_HV_CTRL_RANGE_3, false);
}
//-----------------------------

void LL_SelectRg1K10()
{
	LL_SetStateCtrls(V_HV_CTRL_RANGE_1, true);
	//
	LL_SetStateCtrls(V_HV_CTRL_RANGE_0, false);
	LL_SetStateCtrls(V_HV_CTRL_RANGE_2, false);
	LL_SetStateCtrls(V_HV_CTRL_RANGE_3, false);
}
//-----------------------------

void LL_SelectRg7K70()
{
	LL_SetStateCtrls(V_HV_CTRL_RANGE_2, true);
	//
	LL_SetStateCtrls(V_HV_CTRL_RANGE_0, false);
	LL_SetStateCtrls(V_HV_CTRL_RANGE_1, false);
	LL_SetStateCtrls(V_HV_CTRL_RANGE_3, false);
}
//-----------------------------

void LL_SelectRg720K()
{
	LL_SetStateCtrls(V_HV_CTRL_RANGE_3, true);
	//
	LL_SetStateCtrls(V_HV_CTRL_RANGE_0, false);
	LL_SetStateCtrls(V_HV_CTRL_RANGE_1, false);
	LL_SetStateCtrls(V_HV_CTRL_RANGE_2, false);
}
//-----------------------------

void LL_SelectHV_R1()
{
	LL_SetStateRanges(HV_CTRL_RANGE_0, true);
	LL_SetStateRanges(HV_CTRL_RANGE_1, true);
	LL_SetStateRanges(HV_CTRL_RANGE_2, true);
}
//-----------------------------

void LL_SelectHV_R2()
{
	LL_SetStateRanges(HV_CTRL_RANGE_0, false);
	LL_SetStateRanges(HV_CTRL_RANGE_1, true);
	LL_SetStateRanges(HV_CTRL_RANGE_2, true);
}
//-----------------------------

void LL_SelectHV_R3()
{
	LL_SetStateRanges(HV_CTRL_RANGE_0, false);
	LL_SetStateRanges(HV_CTRL_RANGE_1, false);
	LL_SetStateRanges(HV_CTRL_RANGE_2, true);
}
//-----------------------------

void LL_SelectHV_R4()
{
	LL_SetStateRanges(HV_CTRL_RANGE_0, false);
	LL_SetStateRanges(HV_CTRL_RANGE_1, false);
	LL_SetStateRanges(HV_CTRL_RANGE_2, false);
}
//-----------------------------

void LL_RelayCtrlsDisconnect()
{
	LL_RelayCtrls(RELAY_BUS, false);
	LL_RelayCtrls(RELAY_PS1, false);
	LL_RelayCtrls(RELAY_PS2, false);
	LL_RelayCtrls(RELAY_CTRL, false);
}
//-----------------------------

void LL_RelayCtrls(uint16_t Relay, bool State)
{
	switch (Relay)
	{
		case RELAY_BUS:
			{
				LL_SetStateCtrls(RLC_CTRL1, State);
			}
			break;

		case RELAY_PS1:
			{
				LL_SetStateCtrls(RLC_CTRL2, State);
			}
			break;

		case RELAY_PS2:
			{
				LL_SetStateCtrls(RLC_CTRL3, State);
			}
			break;

		case RELAY_CTRL:
			{
				LL_SetStateCtrls(RLC_CTRL4, State);
			}
			break;

		default:
			break;
	}
}
//-----------------------------

void LL_SelectAdcSrcILV()
{
	LL_SetStateCtrls(LV_CUR_SENS_EN, false);
	LL_SetStateCtrls(HV_CUR_SENS_EN, false);
	//
	LL_SetStateCtrls(LV_CUR_SENS_EN, true);
}
//-----------------------------

void LL_SelectAdcSrcIHV()
{
	LL_SetStateCtrls(LV_CUR_SENS_EN, false);
	LL_SetStateCtrls(HV_CUR_SENS_EN, false);
	//
	LL_SetStateCtrls(HV_CUR_SENS_EN, true);
}
//-----------------------------

void LL_InitTimerChannel1(TIM_TypeDef* TIMx, uint32_t TimerPeriod, uint32_t ChannelPeriod)
{
	// Установка времени срабатывания
	TIMx->CCR1 = TIMx->ARR * ChannelPeriod / TimerPeriod;

	// Разрешение сравнения CCR1 со счётчиком
	TIMx->CCMR1 |= TIM_CCMR1_OC1M_0;

	// Канал 1 настроен на выход
	TIMx->CCMR1 &= ~TIM_CCMR1_CC1S;

	// Разрешение прерывания
	TIMx->DIER |= TIM_DIER_CC1IE;

	// Включение канала 1
	TIMx->CCER |= TIM_CCER_CC1E;
}
//-----------------------------

bool LL_TimerChannel1IsInterrupt(TIM_TypeDef* TIMx)
{
	return (TIMx->SR & TIM_DIER_CC1IE);
}
//-----------------------------

void LL_TimerChannel1InterruptClear(TIM_TypeDef* TIMx)
{
	TIMx->SR &= ~TIM_DIER_CC1IE;
}
//-----------------------------
