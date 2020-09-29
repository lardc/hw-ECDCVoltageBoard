#ifndef __DEBUGACTIONS_H
#define __DEBUGACTIONS_H

// Include
//
#include "ZwBase.h"
#include "Controller.h"

// Define
//
#define RELAY_BUS		1
#define RELAY_PS1		2
#define RELAY_PS2		3
#define RELAY_CTRL1		4
#define RELAY_POT		5
#define RELAY_POT_CTRL	6
#define RELAY_POTP		7
#define RELAY_POTN		8

#define RANGE_V_HV_R0	0
#define RANGE_V_HV_R1	1
#define RANGE_V_HV_R2	2
#define RANGE_V_HV_R3	3

#define SENSOR_LV	0
#define SENSOR_HV	1

#define SENSOR_I_LV	0
#define SENSOR_I_HV	1

#define SELECT_LV_R0	0
#define SELECT_LV_R1	1
#define SELECT_LV_R2	2
#define SELECT_LV_R3	3

#define SELECT_HV_R0	0
#define SELECT_HV_R1	1
#define SELECT_HV_R2	2

// Functions
//
void DBGACT_BlinkExtLed();
void DBGACT_GenerateImpulseToLineSync1();
void DBGACT_GenerateImpulseToLineSync2();
bool DBGACT_ReadStateLineSync1();
bool DBGACT_ReadStateLineSync2();
void DBGACT_RelayCtrls(uint16_t Relay, bool State);
void DBGACT_LHVSelectSrc(SelVSrc src);
void DBGACT_Ctrls48V(bool State);
void DBGACT_Ctrls350V(bool State);

void DBGACT_Ctrls350VEnable();
void DBGACT_Ctrls350VDisable();
void DBGACT_SelectRg();
void DBGACT_SelectVSensSrc();
void DBGACT_SelectISensSrc();
void DBGACT_SelectDACx();
void DBGACT_WriteDACx();
void DBGACT_SelectLVCtrls();
void DBGACT_SelectHVCtrls();
void DBGACT_TestWaveform();

#endif //__DEBUGACTIONS_H
