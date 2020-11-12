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
	DS_Ready = 3,
	DS_InProcess = 4
} DeviceState;

typedef enum __DeviceSubState
{
	SS_None = 0,
	SS_PulsePrepare,
	SS_PulseWaitSwitch,
	SS_PulseWaitOutSet,
	SS_PulseProcess,
	SS_RequestStop,
	SS_WaitDisconnection
} DeviceSubState;

typedef enum __SetCtrls
{
//-0-
	CTRLS_NONE = 0,			//none
	V_HV_CTRL_RANGE_2 = 0,	//@CS1.0	//EN_VOL_SENS_2
	V_HV_CTRL_RANGE_3,		//@CS1.1	//EN_VOL_SENS_3
	LV_SENS_EN,				//@CS1.2
	HV_SENS_EN,				//@CS1.3
	LV_CUR_SENS_EN,			//@CS1.4
	HV_CUR_SENS_EN,			//@CS1.5
	V_HV_CTRL_RANGE_0,		//@CS1.6	//EN_VOL_SENS_0
	V_HV_CTRL_RANGE_1,		//@CS1.7	//EN_VOL_SENS_1
//-1-
	CTRLS_RESERVED1,		//@CS2.0	//none
	RLC_CTRL2,				//@CS2.1	//PS1
	RLC_CTRL3,				//@CS2.2	//PS2
	RLC_CTRL4,				//@CS2.3	//CTRL1
	RLC_POT,				//@CS2.4	//
	RLC_POT_CRL,			//@CS2.5	//
	POT_COMM_INPUT,			//@CS2.6	//
	PT_SENS_EN,				//@CS2.7	//
//-2-
	LV_HV_CTRL2,			//@CS3.0	//low: [LV-] connect, high: [HV-]
	LV_HV_CTRL1,			//@CS3.1	//low: [LV+] connect, high: [HV+]
	RLC_CTRL1,				//@CS3.2	//BUS
	LV_RANGE2,				//@CS3.3	//19
	EN_48V_CTRL,			//@CS3.4	//add +5VDC to 24VDC
	HP_CTRL_350V,			//@CS3.5	//enable Flyback
	LV_RANGE0,				//@CS3.6	//22
	LV_RANGE1,				//@CS3.7	//23
	LAST_CTRLS_NUM			//last num
} SetCtrls;

typedef enum __SetRanges
{
	RANGES_NONE = 0,		//none
	LV_CTRL_RANGE_1 = 0,	//@SREG_CS.0
	LV_CTRL_RANGE_2,		//@SREG_CS.1
	LV_CTRL_RANGE_3,		//@SREG_CS.2
	LV_CTRL_RANGE_0,		//@SREG_CS.3
	HV_CTRL_RANGE_1,		//@SREG_CS.4
	HV_CTRL_RANGE_2,		//@SREG_CS.5
	HV_CTRL_RANGE_0,		//@SREG_CS.6
	RANGES_RESERVED1		//@SREG_CS.7
} SetRanges;

typedef enum __SelVSrc
{
	SELECT_VSRC_LOW = 0,
	SELECT_VSRC_HIGH,
} SelVSrc;

typedef enum __DCV_OutputLine
{
	DC_BUS_LV = 1,
	DC_CTRL = 2,
	PS1 = 3,
	PS2 = 4
} DCV_OutputLine;

typedef enum __DCV_OutputType
{
	OT_Voltage = 1,
	OT_Current = 2
} DCV_OutputType;

typedef enum __DCV_OutputMode
{
	OM_Pulse = 1,
	OM_Continuous = 2
} DCV_OutputMode;

typedef enum __Relay
{
	RELAY_BUS = 1,
	RELAY_PS1,
	RELAY_PS2,
	RELAY_CTRL,
} Relay;

typedef struct __ControllerConfig
{
	DCV_OutputLine OutputLine;
	DCV_OutputType OutputType;
	DCV_OutputMode OutputMode;
	uint16_t PulseTime;
	float VoltageSetpoint;
	float CurrentSetpoint;
	float HWCurrentLimit;
	bool VoltageHighRange;
	bool CurrentHighRange;
	uint16_t Problem;
} ControllerConfig, *pControllerConfig;

// Variables
//
extern volatile Int64U CONTROL_TimeCounter;

// Functions
//
void CONTROL_Init();
void CONTROL_Idle();
void CONTROL_UpdateWatchDog();
void CONTROL_ForceRegulatorStop(uint16_t Problem);
void CONTROL_EpLog(float Current, float Voltage, float Setpoint, float Control, uint16_t RawControl);

#endif // __CONTROLLER_H
