﻿#include "Controller.h"
#include "InitConfig.h"
#include "SysConfig.h"

int main()
{
	__disable_irq();
	SCB->VTOR = (uint32_t)BOOT_LOADER_MAIN_PR_ADDR;
	__enable_irq();
	
	// Настройка системной частоты тактирования
	INITCFG_ConfigSystemClock();
	
	// Настройка портов
	INITCFG_ConfigIO();
	
	// Настройка SPI
	INITCFG_ConfigSPI();
	
	// Настройка CAN
	INITCFG_ConfigCAN();
	
	// Настройка UART
	INITCFG_ConfigUART();
	
	// Настройка ADC
	INITCFG_ConfigADC();
	
	// Настройка таймера регулятора
	INITCFG_ConfigTimer2();

	// Настройка системного счетчика
	INITCFG_ConfigTimer7();
	
	// Настройка сторожевого таймера
	INITCFG_ConfigWatchDog();
	
	// Инициализация логики контроллера
	CONTROL_Init();
	
	// Фоновый цикл
	while(TRUE)
		CONTROL_Idle();
	
	return 0;
}
