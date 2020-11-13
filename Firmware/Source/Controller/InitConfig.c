﻿#include "InitConfig.h"
#include "Board.h"
#include "SysConfig.h"
#include "BCCIxParams.h"

// Functions
//
Boolean INITCFG_ConfigSystemClock()
{
	return RCC_PLL_HSE_Config(QUARTZ_FREQUENCY, PREDIV_4, PLL_14);
}
//------------------------------------------------

void INITCFG_ConfigIO()
{
	// Включение тактирования портов
	RCC_GPIO_Clk_EN(PORTA);
	RCC_GPIO_Clk_EN(PORTB);
	RCC_GPIO_Clk_EN(PORTC);
	
	// Аналоговые входы
	GPIO_InitAnalog(GPIO_MEASURE_V);
	GPIO_InitAnalog(GPIO_MEASURE_I);
	
	// Выходы
	GPIO_InitPushPullOutput(GPIO_CS1);
	GPIO_InitPushPullOutput(GPIO_CS2);
	GPIO_InitPushPullOutput(GPIO_CS3);
	GPIO_InitPushPullOutput(GPIO_DAC_CS);
	GPIO_InitPushPullOutput(GPIO_LDAC1);
	GPIO_InitPushPullOutput(GPIO_LDAC2);
	GPIO_InitPushPullOutput(GPIO_SREG_CS);
	GPIO_InitPushPullOutput(GPIO_SREG_OE1);
	GPIO_InitPushPullOutput(GPIO_RCK);
	GPIO_InitPushPullOutput(GPIO_LED);
	GPIO_InitPushPullOutput(GPIO_EXT_LED);
	GPIO_InitPushPullOutput(GPIO_HVPS_DISABLE);
	
	// Линия синхронизации (выходы)
	GPIO_InitPushPullOutput(GPIO_SYNC1_OUT);
	GPIO_InitPushPullOutput(GPIO_SYNC2_OUT);
	
	// Альтернативные функции
	GPIO_InitAltFunction(GPIO_ALT_CAN_RX, AltFn_9);
	GPIO_InitAltFunction(GPIO_ALT_CAN_TX, AltFn_9);
	
	GPIO_InitAltFunction(GPIO_ALT_UART1_RX, AltFn_7);
	GPIO_InitAltFunction(GPIO_ALT_UART1_TX, AltFn_7);
	
	GPIO_InitAltFunction(GPIO_ALT_SPI1_CLK, AltFn_5);
	GPIO_InitAltFunction(GPIO_ALT_SPI1_MOSI, AltFn_5);
}
//------------------------------------------------

void INITCFG_ConfigCAN()
{
	RCC_CAN_Clk_EN(CAN_1_ClkEN);
	NCAN_Init(SYSCLK, CAN_BAUDRATE, false);
	NCAN_FIFOInterrupt(true);
	NCAN_FilterInit(0, CAN_SLAVE_FILTER_ID, CAN_SLAVE_NID_MASK);
}
//------------------------------------------------

void INITCFG_ConfigUART()
{
	USART_Init(USART1, SYSCLK, USART_BAUDRATE);
	USART_Recieve_Interupt(USART1, 0, true);
}
//------------------------------------------------

void INITCFG_ConfigSPI()
{
	SPI_Init8b(SPI1, SPI1_BAUDRATE_BITS, SPI1_LSB_FIRST);
}
//------------------------------------------------

void INITCFG_ConfigADC()
{
	RCC_ADC_Clk_EN(ADC_12_ClkEN);
	ADC_Calibration(ADC1);
	ADC_Calibration(ADC2);
	ADC_SoftTrigConfig(ADC1);
	ADC_SoftTrigConfig(ADC2);
	ADC_ChannelSet_SampleTime(ADC1, 1, ADC_SMPL_TIME_7_5);
	ADC_ChannelSet_SampleTime(ADC2, 1, ADC_SMPL_TIME_7_5);
	ADC_Enable(ADC1);
	ADC_Enable(ADC2);
}
//------------------------------------------------

void INITCFG_ConfigTimer2()
{
	TIM_Clock_En(TIM_2);
	TIM_Config(TIM2, SYSCLK, TIMER2_uS);
	TIM_Interupt(TIM2, 0, true);
	// Приоритет прерывания ниже приоритета USART1
	NVIC_SetPriority(TIM2_IRQn, 50);
}
//------------------------------------------------

void INITCFG_ConfigTimer7()
{
	TIM_Clock_En(TIM_7);
	TIM_Config(TIM7, SYSCLK, TIMER7_uS);
	TIM_Interupt(TIM7, 0, true);
	TIM_Start(TIM7);
}
//------------------------------------------------

void INITCFG_ConfigWatchDog()
{
	IWDG_Config();
	IWDG_ConfigureFastUpdate();
}
//------------------------------------------------
