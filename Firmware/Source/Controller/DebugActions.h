#ifndef __DEBUGACTIONS_H
#define __DEBUGACTIONS_H

// Include
//
#include "ZwBase.h"
#include "Controller.h"
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
