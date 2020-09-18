#ifndef __CONTROLLER_H
#define __CONTROLLER_H

// Include
//
#include "stdinc.h"

// Types
//
typedef enum __DeviceState
{
	DS_None = 0,
	DS_Fault = 1,
	DS_Disabled = 2,
	DS_Enabled = 3,
	DS_InProcess = 4
} DeviceState;

typedef enum {
	V_HV_CTRL_RANGE_2 = 0,	//@CS1.0
	V_HV_CTRL_RANGE_3,		//@CS1.1
	LV_SENS_EN,				//@CS1.2
	HV_SENS_EN,				//@CS1.3
	LV_CUR_SENS_EN,			//@CS1.4
	HV_CUR_SENS_EN,			//@CS1.5
	V_HV_CTRL_RANGE_0,		//@CS1.6
	V_HV_CTRL_RANGE_1,		//@CS1.7

	RESERVED_01,			//@CS2.0
	RLC_CTRL2,				//@CS2.1
	RLC_CTRL3,				//@CS2.2
	RLC_CTRL4,				//@CS2.3
	RLC_CTRL5,				//@CS2.4
	RLC_CTRL6,				//@CS2.5
	RLC_CTRL7,				//@CS2.6
	RLC_CTRL8,				//@CS2.7

	LV_HV_CTRL2,			//@CS3.0
	LV_HV_CTRL1,			//@CS3.1
	RLC_CTRL1,				//@CS3.2
	RESERVED_02,			//@CS3.3
	EN_48V_CTRL,			//@CS3.4
	HP_CTRL_350V,			//@CS3.5
	RESERVED_03,			//@CS3.6
	RESERVED_04,			//@CS3.7
	LAST_CTRLS_NUM			//last number
} SetCtrls;

typedef enum {
	LV_CTRL_RANGE_1 = 0,	//@SREG_CS.0
	LV_CTRL_RANGE_2,		//@SREG_CS.1
	LV_CTRL_RANGE_3,		//@SREG_CS.2
	LV_CTRL_RANGE_0,		//@SREG_CS.3
	HV_CTRL_RANGE_1,		//@SREG_CS.4
	HV_CTRL_RANGE_2,		//@SREG_CS.5
	HV_CTRL_RANGE_0,		//@SREG_CS.6
	RESERVED_001			//@SREG_CS.7
} SetRanges;

typedef enum {
	SELECT_DAC_NONE=0,
	SELECT_DAC_LV,
	SELECT_DAC_HV
} SelDacX;

// Defines
#define CTRL_SIZE ((LAST_CTRLS_NUM-1)/8+1)

// Variables
//
extern volatile Int64U CONTROL_TimeCounter;
extern Int64U CONTROL_LEDTimeout;


// Functions
//
void CONTROL_Init();
void CONTROL_Idle();
void CONTROL_DelayMs(uint32_t Delay);

#endif // __CONTROLLER_H
