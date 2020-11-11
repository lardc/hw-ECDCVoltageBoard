#ifndef __GLOBAL_H
#define __GLOBAL_H

// Includes
#include "SysConfig.h"

// Definitions
// 
#define	SCCI_TIMEOUT_TICKS			1000	// Таймаут интерфейса SCCI (в мс)
#define EP_WRITE_COUNT				0		// Количество массивов для записи
#define EP_COUNT					5		// Количество массивов для чтения
#define ENABLE_LOCKING				FALSE	// Защита NV регистров паролем
#define EP_SIZE						1000	// Размер буферов логгирования

// Временные параметры
//
#define TIME_LED_BLINK				500		// Мигание светодиодом (в мс)
#define TIME_DBG_PULSE				1000	// Длительность отладочного импульса (в мс)
#define TIME_TRANSIENT_DELAY		100		// Задержка коммутации и переходных процессов (в мс)

// Параметры выхода
#define VB_VOUT_MIN					40			// в мВ
#define VB_VOUT_MAX					270000		// в мВ
#define VB_IOUT_MIN					8			// в мкА
#define VB_IOUT_MAX					110000		// в мкА

// Параметры АЦП, ЦАП
#define DAC_MAX_RESOLUTION			0xFFF
#define DAC_REF_VOLTAGE				5000		// в мВ

#define ADC_MAX_RESOLUTION			0xFFF
#define ADC_REF_VOLTAGE				3000		// в мВ

#define ADC_AVG_COUNT				4

// Параметры регулятора
#define REGLTR_AVERAGE_RESULT_NUM	(1000000 / (50 * REGLTR_PERIOD))	// Количество усреднений результата
#define REGLTR_ERROR_I_SAT_H		1000000
#define REGLTR_PERIOD				TIMER2_uS

#endif //  __GLOBAL_H
