#ifndef __CONSTRAINTS_H
#define __CONSTRAINTS_H

// Include
#include "stdinc.h"
#include "DataTable.h"
#include "Controller.h"

// Definitions
#define NO		0
#define YES		1

// Границы диапазонов тока (мкА / мА)
#define I_RANGE_MIN			1
#define I_RANGE_MAX			10000
// в мкА
#define I_RANGE_DEF1		100
#define I_RANGE_DEF2		1000
#define I_RANGE_DEF3		10000
// в мА
#define I_RANGE_DEF4		110

// в Омах
#define I_SHUNT_RES_MIN		1
#define I_SHUNT_RES_MAX		INT16U_MAX
#define I_SHUNT_RES_DEF		100

// в %
#define ILIM_MARGIN_MIN		1
#define ILIM_MARGIN_MAX		50
#define ILIM_MARGIN_DEF		20

// Границы диапазонов напряжения (мВ / В)
#define V_RANGE_MIN			1
#define V_RANGE_MAX			30000
// в мВ
#define V_RANGE_DEF1		200
#define V_RANGE_DEF2		2000
#define V_RANGE_DEF3		20000
// в В
#define V_RANGE_DEF4		270

#define KPI_MIN				0
#define KPI_MAX				10000
#define KPI_DEF				0

// в мс х10
#define RISE_FRONT_MIN		1
#define RISE_FRONT_MAX		100
#define RISE_FRONT_DEF		10

// в мс
#define PULSE_LENGH_MIN		5
#define PULSE_LENGH_MAX		500
#define PULSE_LENGH_DEF		10

// в %
#define OUTPUT_READY_MIN	1
#define OUTPUT_READY_MAX	10
#define OUTPUT_READY_DEF	3

#define FE_COUNTER_MIN		1
#define FE_COUNTER_MAX		200
#define FE_COUNTER_DEF		5

// в %
#define FE_TRIG_LEVEL_MIN	1
#define FE_TRIG_LEVEL_MAX	30
#define FE_TRIG_LEVEL_DEF	10

// Types
typedef struct __TableItemConstraint
{
	Int16U Min;
	Int16U Max;
	Int16U Default;
} TableItemConstraint;

// Variables
extern const TableItemConstraint NVConstraint[DATA_TABLE_NV_SIZE];
extern const TableItemConstraint VConstraint[DATA_TABLE_WP_START - DATA_TABLE_WR_START];

#endif // __CONSTRAINTS_H
