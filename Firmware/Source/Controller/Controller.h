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

typedef enum __SetCtrls {
//-0-
	CTRLS_NONE = 0,			//none		//-+-
	V_HV_CTRL_RANGE_2 = 0,	//@CS1.0	//dbg+	//EN_VOL_SENS_2
	V_HV_CTRL_RANGE_3,		//@CS1.1	//dbg+	//EN_VOL_SENS_3
	LV_SENS_EN,				//@CS1.2	//dbg+
	HV_SENS_EN,				//@CS1.3	//dbg+
	LV_CUR_SENS_EN,			//@CS1.4	//dbg+
	HV_CUR_SENS_EN,			//@CS1.5	//dbg+
	V_HV_CTRL_RANGE_0,		//@CS1.6	//dbg+	//EN_VOL_SENS_0
	V_HV_CTRL_RANGE_1,		//@CS1.7	//dbg+	//EN_VOL_SENS_1
//-1-
	CTRLS_RESERVED1,		//@CS2.0	//-+-
	RLC_CTRL2,				//@CS2.1	//dbg+	//PS1
	RLC_CTRL3,				//@CS2.2	//dbg+	//PS2
	RLC_CTRL4,				//@CS2.3	//dbg+	//CTRL1
	RLC_CTRL5,				//@CS2.4	//dbg+	//POT
	RLC_CTRL6,				//@CS2.5	//dbg+	//POT_CTRL
	RLC_CTRL7,				//@CS2.6	//dbg+	//POT+ LV|LH
	RLC_CTRL8,				//@CS2.7	//dbg+	//POT- LV|LH
//-2-
	LV_HV_CTRL2,			//@CS3.0	//dbg+	//low: [LV-] connect, high: [HV-]
	LV_HV_CTRL1,			//@CS3.1	//dbg+	//low: [LV+] connect, high: [HV+]
	RLC_CTRL1,				//@CS3.2	//dbg+	//BUS
	CTRLS_RESERVED2,		//@CS3.3	//-+-
	EN_48V_CTRL,			//@CS3.4	//dbg+	//add +5VDC to 24VDC
	HP_CTRL_350V,			//@CS3.5	//dbg+	//enable Flyback
	CTRLS_RESERVED3,		//@CS3.6	//-+-
	CTRLS_RESERVED4,		//@CS3.7	//-+-
	LAST_CTRLS_NUM			//last num	//-+-
} SetCtrls;

typedef enum __SetRanges {
	RANGES_NONE = 0,		//none			//-+-
	LV_CTRL_RANGE_1 = 0,	//@SREG_CS.0	//dbg+
	LV_CTRL_RANGE_2,		//@SREG_CS.1	//dbg+
	LV_CTRL_RANGE_3,		//@SREG_CS.2	//dbg+
	LV_CTRL_RANGE_0,		//@SREG_CS.3	//dbg+
	HV_CTRL_RANGE_1,		//@SREG_CS.4	//dbg+
	HV_CTRL_RANGE_2,		//@SREG_CS.5	//dbg+
	HV_CTRL_RANGE_0,		//@SREG_CS.6	//dbg+
	RANGES_RESERVED1		//@SREG_CS.7	//-+-
} SetRanges;

typedef enum __SelDacX {
	SELECT_DAC_NONE=0,
	SELECT_DAC_LV,
	SELECT_DAC_HV
} SelDacX;

typedef enum __SelVSrc {
	SELECT_VSRC_LOW=0,
	SELECT_VSRC_HIGH,
} SelVSrc;


// Defines
#define CTRL_SIZE ((LAST_CTRLS_NUM-1)/8+1)
#define DAC_MAX_VALUE	4095
#define DAC_SELECT_CHU	(0<<15)	//channel A
#define DAC_SELECT_CHI	(1<<15)	//channel B

// Variables
//
extern volatile Int64U CONTROL_TimeCounter;
extern Int64U CONTROL_LEDTimeout;


// Functions
//
void CONTROL_Init();
void CONTROL_Idle();
void CONTROL_DelayMs(uint32_t Delay);
void CONTROL_UpdateWatchDog();

#endif // __CONTROLLER_H
