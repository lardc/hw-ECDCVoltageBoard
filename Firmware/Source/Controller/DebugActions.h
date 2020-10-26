#ifndef __DEBUGACTIONS_H
#define __DEBUGACTIONS_H

// Include
//
#include "ZwBase.h"
#include "Controller.h"

// Define
//
#define RANGE_V_HV_R0	0
#define RANGE_V_HV_R1	1
#define RANGE_V_HV_R2	2
#define RANGE_V_HV_R3	3

#define SENSOR_NO	0
#define SENSOR_LV	1
#define SENSOR_HV	2
#define SENSOR_PT	3

#define SENSOR_I_LV	0
#define SENSOR_I_HV	1

#define SELECT_LV_R0	0
#define SELECT_LV_R1	1
#define SELECT_LV_R2	2
#define SELECT_LV_R3	3

#define SELECT_HV_R1	0
#define SELECT_HV_R2	1
#define SELECT_HV_R3	2
#define SELECT_HV_R4	3

// Functions
//
void DBGACT_BlinkExtLed();
void DBGACT_GenerateImpulseToLineSync1();
void DBGACT_GenerateImpulseToLineSync2();
bool DBGACT_ReadStateLineSync1();
bool DBGACT_ReadStateLineSync2();
void DBGACT_LHVSelectSrc(SelVSrc src);
void DBGACT_Ctrls48V(bool State);
void DBGACT_Ctrls350V(bool State);

void DBGACT_Ctrls350VEnable();
void DBGACT_Ctrls350VDisable();
void DBGACT_SelectRg();
void DBGACT_SelectVSensSrc();
void DBGACT_SelectISensSrc();
void DBGACT_SelectLVCtrls();
void DBGACT_SelectHVCtrls();
void DBGACT_SelectVRange();

#endif // __DEBUGACTIONS_H
