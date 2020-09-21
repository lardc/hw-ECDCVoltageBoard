#ifndef __DEBUGACTIONS_H
#define __DEBUGACTIONS_H

// Include
//
#include "ZwBase.h"

// Functions
//
void DBGACT_BlinkExtLed();
void DBGACT_GenerateImpulseToLineSync1();
void DBGACT_GenerateImpulseToLineSync2();
bool DBGACT_ReadStateLineSync1();
bool DBGACT_ReadStateLineSync2();

//TODO check & update return type
bool DBGACT_RelayCtrlsOn();
bool DBGACT_RelayCtrlsOff();
bool DBGACT_LHVSelectLow();
bool DBGACT_LHVSelectHigh();
bool DBGACT_Ctrls48VEnable();
bool DBGACT_Ctrls48VDisable();
bool DBGACT_Ctrls350VEnable();
bool DBGACT_Ctrls350VDisable();
bool DBGACT_SelectRg();
bool DBGACT_SelectVSensSrc();
bool DBGACT_SelectISensSrc();
bool DBGACT_SelectDACx();
bool DBGACT_WriteDACx();
bool DBGACT_SelectLVCtrls();
bool DBGACT_SelectHVCtrls();

#endif //__DEBUGACTIONS_H
