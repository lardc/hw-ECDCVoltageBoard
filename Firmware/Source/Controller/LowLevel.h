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

void LL_WriteDACLV_Voltage(uint16_t Data);
void LL_WriteDACLV_Current(uint16_t Data);

void LL_WriteDACHV_Voltage(uint16_t Data);
void LL_WriteDACHV_Current(uint16_t Data);

void LL_ResetDACOutputs();

void LL_ResetStateCtrls();
void LL_SetStateCtrls(SetCtrls Pin, bool State);
void LL_ResetStateRanges();
void LL_SetStateRanges(SetRanges Pin, bool State);

void LL_SelectVOutMaxV200();
void LL_SelectVOutMax2V00();
void LL_SelectVOutMax20V0();
void LL_SelectVrange270V();

void LL_SelectRs27K();
void LL_SelectRs2K7();
void LL_SelectRsK27();
void LL_SelectRsK020();
void LL_SelectRsNone();

void LL_SelectAdcSrcVLV();
void LL_SelectAdcSrcHV();
void LL_SelectAdcSrcPT();
void LL_SelectAdcSrcNO();

void LL_SelectRgK12();
void LL_SelectRg1K10();
void LL_SelectRg7K70();
void LL_SelectRg720K();

void LL_SelectHV_R1();
void LL_SelectHV_R2();
void LL_SelectHV_R3();
void LL_SelectHV_R4();

void LL_RelayCtrls(uint16_t Relay, bool State);
void LL_SelectAdcSrcILV();
void LL_SelectAdcSrcIHV();

#endif //__LOWLEVEL_H
