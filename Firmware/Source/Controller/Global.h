#ifndef __GLOBAL_H
#define __GLOBAL_H

// Definitions
// 
#define	SCCI_TIMEOUT_TICKS			1000	// Таймаут интерфейса SCCI (в мс)
#define EP_WRITE_COUNT				0		// Количество массивов для записи
#define EP_COUNT					4		// Количество массивов для чтения
#define ENABLE_LOCKING				FALSE	// Защита NV регистров паролем

// Временные параметры
//
#define TIME_LED_BLINK				500		// Мигание светодиодом (в мс)
#define TIME_EXT_LED_BLINK			500		// Время загорания внешнего светодиода (в мс)

//Технические параметры :
//диапазоны напряжения, мВ
#define VRANGE_0V20_MIN		40
#define VRANGE_0V20_MAX		200
#define VRANGE_2V00_MIN		180
#define VRANGE_2V00_MAX		2000
#define VRANGE_20V0_MIN		1800
#define VRANGE_20V0_MAX		20000
#define VRANGE_270V_MIN		18000
#define VRANGE_270V_MAX		270000
//диапазоны тока, мкА
#define IRANGE_R1_MIN		8
#define IRANGE_R1_MAX		100
#define IRANGE_R2_MIN		80
#define IRANGE_R2_MAX		1000
#define IRANGE_R3_MIN		800
#define IRANGE_R3_MAX		10000
#define IRANGE_R4_MIN		8000
#define IRANGE_R4_MAX		110000

// Параметры АЦП, ЦАП
#define DAC_MAX_RESOLUTION		0xFFF
#define DAC_REF_VOLTAGE			5000		// в мВ

#define ADC_MAX_RESOLUTION		0xFFF
#define ADC_REF_VOLTAGE			3000		// в мВ

#define ADC_AVG_COUNT			4

// Параметры регулятора
#define REGLTR_ERROR_I_SAT_H	10000

#endif //  __GLOBAL_H
