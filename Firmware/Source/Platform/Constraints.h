#ifndef __CONSTRAINTS_H
#define __CONSTRAINTS_H

// Include
#include "stdinc.h"
#include "DataTable.h"
#include "Controller.h"

//Definitions
#define NO		0
#define YES		1
#define MAX_DBG	INT16U_MAX
//CHIP physical range
#define ADC_LEVEL_MAX		4095
#define ADC_LEVEL_MIN		0
#define DAC_LEVEL_MAX		4095
#define DAC_LEVEL_MIN		0

//V_DAC physical range
#define DAC_V200_DEF		3725
#define DAC_2V00_DEF		3725
#define DAC_20V0_DEF		3725
#define DAC_270V_DEF		3725

//I_DAC physical range "Current limiter"
#define DAC_LIMIT_MIN		10
#define DAC_LIMIT_MAX		2500
#define DAC_LIMIT_DEF		2300

//V_ADC physical range
//Source:BUS_LV
#define ADC_BLV_V200_DEF		3687
#define ADC_BLV_2V00_DEF		3687
#define ADC_BLV_20V0_DEF		3687
//Source:BUS_HV
#define ADC_BHV_270V_DEF		3687
//Source:POT_LV
#define ADC_POT_V200_DEF		3687
#define ADC_POT_2V00_DEF		3687
#define ADC_POT_20V0_DEF		3687
//Source:POT_HV
#define ADC_PHV_270V_DEF		3687

//CURR_DAC physical range
#define DAC_100MKA_DEF			3680
#define DAC_1MA_DEF				3680
#define DAC_10MA_DEF			3680
#define DAC_110MA_DEF			3680

//CURR_ADC physical range
#define ADC_ILV_R1_DEF		3687
#define ADC_ILV_R2_DEF		3687
#define ADC_ILV_R3_DEF		3687
#define ADC_ILV_R4_DEF		3687
#define ADC_IHV_R1_DEF		3687
#define ADC_IHV_R2_DEF		3687
#define ADC_IHV_R3_DEF		3687

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
