﻿#ifndef __SYSCONFIG_H
#define __SYSCONFIG_H

// Flash loader options
#define BOOT_LOADER_VARIABLE			(*((volatile uint32_t *)0x20000000))
#define BOOT_LOADER_REQUEST				0x12345678
#define BOOT_LOADER_MAIN_PR_ADDR		0x08008000
//-----------------------------------------------

// System clock
#define SYSCLK							70000000	// Тактовая частота системной шины процессора
#define QUARTZ_FREQUENCY				20000000	// Частота кварца
// ----------------------------------------------

// USART
#define USART_BAUDRATE					115200		// Скорость USART
#define USART_FIFOlen					32			// Длина FIFO USART
// ----------------------------------------------

// Timers
#define TIMER2_uS						1000		// в мкс
#define TIMER7_uS						1000		// в мкс
// ----------------------------------------------

// CAN
#define CAN_BAUDRATE					1000000		// Битрейт CAN
// ----------------------------------------------

// SPI
#define SPI1_BAUDRATE_BITS				0x5			//101b:pClk/64	// Baud rate control
#define SPI1_LSB_FIRST					false
// ----------------------------------------------

// ADC
#define ADC_CHANEL_V					1			// Номер канала АЦП напряжения
#define ADC_CHANEL_I					1			// Номер канала АЦП тока
// ----------------------------------------------

#endif // __SYSCONFIG_H
