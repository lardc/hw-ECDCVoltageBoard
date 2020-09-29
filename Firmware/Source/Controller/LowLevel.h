#ifndef __LOWLEVEL_H
#define __LOWLEVEL_H

// Include
#include "stdinc.h"
#include "Controller.h"
// Functions
//
void LL_ToggleBoardLED();
void LL_SetStateExtLed(bool State);
void LL_SetStateLineSync1(bool State);
void LL_SetStateLineSync2(bool State);
bool LL_GetStateLineSync1();
bool LL_GetStateLineSync2();
void LL_ResetStateCtrls();
void LL_SetStateCtrls(SetCtrls Pin, bool State);
void LL_ResetStateRanges();
void LL_SetStateRanges(SetRanges Pin, bool State);
void LL_WriteDAC_LH(uint16_t Data);
void LL_SelectDACx(SelDacX dac);

#endif //__LOWLEVEL_H
