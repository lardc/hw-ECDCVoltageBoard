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

void DBGACT_RelayCtrlsOn();
void DBGACT_RelayCtrlsOff();
void DBGACT_LHVSelectLow();
void DBGACT_LHVSelectHigh();
void DBGACT_Ctrls48VEnable();
void DBGACT_Ctrls48VDisable();
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
