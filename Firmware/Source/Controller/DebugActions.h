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

#endif //__DEBUGACTIONS_H
