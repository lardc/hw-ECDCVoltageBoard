#ifndef __CONTROLLER_H
#define __CONTROLLER_H

// Include
//
#include "stdinc.h"
#include "arm_math.h"

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

typedef enum __DeviceSubState
{
	SS_None = 0,
	SS_PulsePrepare,
	SS_PulseStart,
	SS_PulseProcess,
	SS_PulseStop,
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
	RLC_CTRL5,				//@CS2.4	//POT
	RLC_CTRL6,				//@CS2.5	//POT_CTRL
	RLC_CTRL7,				//@CS2.6	//POT+ LV|LH
	PT_SENS_EN,				//@CS2.7	//POT- LV|LH
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

typedef enum __WorkMode
{
	WORK_MODE_OFF = 0,
	WORK_MODE_VOLT,
	WORK_MODE_CURR,
} WorkMode;

typedef enum __SrcType
{
	SRC_TYPE_NONE = 0,
	SRC_TYPE_SINGLE,
	SRC_TYPE_PERMANENT,
} SrcType;

typedef enum __OutLine
{
	OUT_LINE_NONE = 0,
	OUT_LINE_PS1,
	OUT_LINE_PS2,
	OUT_LINE_CTRL1,
	OUT_LINE_POT_CTRL,
	OUT_LINE_BUS,
	OUT_LINE_LAST = OUT_LINE_BUS
} OutLine;

typedef enum __Relay
{
	RELAY_BUS = 1,
	RELAY_PS1,
	RELAY_PS2,
	RELAY_CTRL,
	RELAY_POT,
	RELAY_POT_CTRLN,
	RELAY_POT_CTRLP,
	RELAY_LV_HV_CTRL1,
	RELAY_LV_HV_CTRL2
} Relay;

typedef enum __VoltageChannel
{
	CHANEL_NONE,
	CHANEL_V200,
	CHANEL_2V00,
	CHANEL_20V0,
	CHANEL_270V
} VoltageChannel;

typedef enum __CurrentChannel
{
	CHANEL_LV_R1,
	CHANEL_LV_R2,
	CHANEL_LV_R3,
	CHANEL_LV_R4
} CurrentChannel;

typedef struct __ControllerConfig
{
	uint8_t WorkMode;
	uint8_t OutLine;
	uint8_t PulseType;
	uint16_t PulseTime;
	uint32_t CurrSet;
	uint32_t VSet;
	uint32_t VMeas;
	uint32_t CurrMeas;;
	uint32_t CurrCut;
	uint32_t VCut;
	uint64_t StartTime;
	VoltageChannel VChanel;
	CurrentChannel CurrChanel;
	uint16_t VWant;
	uint16_t VDac;
	uint16_t VReal;
	uint16_t CurrWant;
	uint16_t CurrDac;
	uint16_t CurrReal;
	uint16_t VDacRegionSize;
	uint16_t VAdcRegionSize;
	uint16_t CurrDacRegionSize;
	uint16_t CurrAdcRegionSize;
	int16_t VError;
	int16_t IError;
} ControllerConfig;

// Defines
//
#define CTRL_SIZE ((LAST_CTRLS_NUM-1)/8+1)
#define DAC_MAX_VALUE	4095
#define ADC_MAX_VALUE	4095
#define DAC_SELECT_CHV	(0<<15)
#define DAC_SELECT_CHI	(1<<15)
#define ADC_CHANEL_V	1
#define ADC_CHANEL_I	1

//�������� ������� ����������:����������:*��, ���:*���
#define VB_VOUT_MIN		40
#define VB_VOUT_MAX		270000
#define VB_VOUT_ICUT	100000
#define VB_IOUT_MIN		8
#define VB_IOUT_MAX		110000
#define VB_IOUT_VCUT	50000

// Variables
//
extern volatile Int64U CONTROL_TimeCounter;
extern Int64U CONTROL_LEDTimeout;

// Functions
//
void CONTROL_Init();
void CONTROL_Idle();
void CONTROL_UpdateWatchDog();
void CONTROL_EpLog(uint16_t CurrMeasure, uint16_t CurError, uint16_t Vmeasure, uint16_t VError);

#endif // __CONTROLLER_H
