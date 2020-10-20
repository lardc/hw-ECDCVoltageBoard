// Header
#include <string.h>

#include "LowLevel.h"
// Include
#include "Board.h"
#include "Delay.h"
#include "Controller.h"

// Variables
//
uint8_t CONTROL_UnitCtrls[CTRL_SIZE];
uint8_t CONTROL_UnitRanges;

// Functions
//
void LL_ToggleBoardLED()
{
	GPIO_Toggle(GPIO_LED);
}
//-----------------------------

void LL_SetStateExtLed(bool State)
{
	GPIO_SetState(GPIO_EXT_LED, State);
}
//-----------------------------

void LL_SetStateLineSync1(bool State)
{
	GPIO_SetState(GPIO_SYNC1_OUT, State);
}
//-----------------------------

void LL_SetStateLineSync2(bool State)
{
	GPIO_SetState(GPIO_SYNC2_OUT, State);
}
//-----------------------------

bool LL_GetStateLineSync1()
{
	return GPIO_GetState(GPIO_SYNC1_IN);
}
//-----------------------------

bool LL_GetStateLineSync2()
{
	return GPIO_GetState(GPIO_SYNC2_IN);
}
//-----------------------------

// Управление выходами CTRL
void LL_UpdateStateCtrls()
{
	uint32_t i = CTRL_SIZE;
	while(i--)
		SPI_WriteByte8b(SPI1, CONTROL_UnitCtrls[i]);
	GPIO_SetState(GPIO_RCK, true);
	GPIO_SetState(GPIO_RCK, false);
}
//-----------------------------

void LL_ResetStateCtrls()
{
	memset(CONTROL_UnitCtrls, 0, CTRL_SIZE);
	LL_UpdateStateCtrls();
}
//-----------------------------
void LL_SetStateCtrls(SetCtrls Pin, bool State)
{
	uint32_t Nbyte;
	uint32_t Nbit;
	
	Nbyte = Pin / 8;
	Nbit = Pin % 8;
	if(State)
	{
		CONTROL_UnitCtrls[Nbyte] |= 1 << Nbit;
	}
	else
	{
		CONTROL_UnitCtrls[Nbyte] &= ~(1 << Nbit);
	}
	LL_UpdateStateCtrls();
}
//-----------------------------

// Управление выходами RANGE
void LL_UpdateStateRanges()
{
	GPIO_SetState(GPIO_SREG_CS, false);
	SPI_WriteByte8b(SPI1, CONTROL_UnitRanges);
	GPIO_SetState(GPIO_SREG_CS, true);
}
//-----------------------------

void LL_ResetStateRanges()
{
	CONTROL_UnitRanges = 0;
	LL_UpdateStateRanges();
}
//-----------------------------
void LL_SetStateRanges(SetRanges Pin, bool State)
{
	uint32_t Nbit;
	
	Nbit = Pin % 8;
	if(State)
	{
		CONTROL_UnitRanges |= 1 << Nbit;
	}
	else
	{
		CONTROL_UnitRanges &= ~(1 << Nbit);
	}
	LL_UpdateStateRanges();
}
//-----------------------------

void LL_WriteDAC_LH(uint16_t Data)
{
	GPIO_SetState(GPIO_DAC_CS, false);
	SPI_WriteByte8b(SPI1, (Data >> 8) & 0xff);
	SPI_WriteByte8b(SPI1, Data & 0xff);
	GPIO_SetState(GPIO_DAC_CS, true);
}
//-----------------------------

void LL_SelectDACx(SelDacX dac)
{
	switch (dac)
	{
		case SELECT_DAC_LV:
			GPIO_SetState(GPIO_LDAC2, true);	//first: off(), then: on()
			GPIO_SetState(GPIO_LDAC1, false);
			break;
			
		case SELECT_DAC_HV:
			GPIO_SetState(GPIO_LDAC2, true);	//first: off(), then: on()
			GPIO_SetState(GPIO_LDAC1, false);
			break;
			
		case SELECT_DAC_NONE:
		default:
			GPIO_SetState(GPIO_LDAC1, true);	//off() & off()
			GPIO_SetState(GPIO_LDAC2, true);
			break;
	}
}
//-----------------------------

void LL_SelectVOutMaxV200()
{
	LL_SetStateCtrls(LV_RANGE0, true);
	LL_SetStateCtrls(LV_RANGE1, false);
	LL_SetStateCtrls(LV_RANGE2, false);
}
//-----------------------------

void LL_SelectVOutMax2V00()
{
	LL_SetStateCtrls(LV_RANGE0, false);
	LL_SetStateCtrls(LV_RANGE1, true);
	LL_SetStateCtrls(LV_RANGE2, false);
	;
}
//-----------------------------

void LL_SelectVOutMax20V0()
{
	LL_SetStateCtrls(LV_RANGE0, false);
	LL_SetStateCtrls(LV_RANGE1, false);
	LL_SetStateCtrls(LV_RANGE2, true);
}
//-----------------------------

void LL_SelectRs27K()
{
	LL_SetStateRanges(LV_CTRL_RANGE_0, true);
	LL_SetStateRanges(LV_CTRL_RANGE_1, false);
	LL_SetStateRanges(LV_CTRL_RANGE_2, false);
	LL_SetStateRanges(LV_CTRL_RANGE_3, false);
}
//-----------------------------

void LL_SelectRs2K7()
{
	LL_SetStateRanges(LV_CTRL_RANGE_0, false);
	LL_SetStateRanges(LV_CTRL_RANGE_1, false);
	LL_SetStateRanges(LV_CTRL_RANGE_2, false);
	LL_SetStateRanges(LV_CTRL_RANGE_3, true);
}
//-----------------------------

void LL_SelectRsK27()
{
	LL_SetStateRanges(LV_CTRL_RANGE_0, false);
	LL_SetStateRanges(LV_CTRL_RANGE_1, false);
	LL_SetStateRanges(LV_CTRL_RANGE_2, true);
	LL_SetStateRanges(LV_CTRL_RANGE_3, false);
}
//-----------------------------

void LL_SelectRsK020()
{
	LL_SetStateRanges(LV_CTRL_RANGE_0, false);
	LL_SetStateRanges(LV_CTRL_RANGE_1, true);
	LL_SetStateRanges(LV_CTRL_RANGE_2, false);
	LL_SetStateRanges(LV_CTRL_RANGE_3, false);
}
//-----------------------------

void LL_SelectAdcSrcVLV()
{
	LL_SetStateCtrls(LV_SENS_EN, false);
	LL_SetStateCtrls(HV_SENS_EN, false);
	LL_SetStateCtrls(PT_SENS_EN, false);
	//
	LL_SetStateCtrls(LV_SENS_EN, true);
}
//-----------------------------

void LL_SelectAdcSrcHV()
{
	LL_SetStateCtrls(LV_SENS_EN, false);
	LL_SetStateCtrls(HV_SENS_EN, false);
	LL_SetStateCtrls(PT_SENS_EN, false);
	//
	LL_SetStateCtrls(HV_SENS_EN, true);
}
//-----------------------------

void LL_SelectAdcSrcPT()
{
	LL_SetStateCtrls(LV_SENS_EN, false);
	LL_SetStateCtrls(HV_SENS_EN, false);
	LL_SetStateCtrls(PT_SENS_EN, false);
	//
	LL_SetStateCtrls(PT_SENS_EN, true);
}
//-----------------------------

void LL_SelectAdcSrcNO()
{
	LL_SetStateCtrls(LV_SENS_EN, true);
	LL_SetStateCtrls(HV_SENS_EN, true);
	LL_SetStateCtrls(PT_SENS_EN, true);
}
//-----------------------------

void LL_SelectRgK12()
{
	LL_SetStateCtrls(V_HV_CTRL_RANGE_0, true);
	//
	LL_SetStateCtrls(V_HV_CTRL_RANGE_1, false);
	LL_SetStateCtrls(V_HV_CTRL_RANGE_2, false);
	LL_SetStateCtrls(V_HV_CTRL_RANGE_3, false);
}
//-----------------------------

void LL_SelectRg1K10()
{
	LL_SetStateCtrls(V_HV_CTRL_RANGE_1, true);
	//
	LL_SetStateCtrls(V_HV_CTRL_RANGE_0, false);
	LL_SetStateCtrls(V_HV_CTRL_RANGE_2, false);
	LL_SetStateCtrls(V_HV_CTRL_RANGE_3, false);
}
//-----------------------------
void LL_SelectRg7K70()
{
	LL_SetStateCtrls(V_HV_CTRL_RANGE_2, true);
	//
	LL_SetStateCtrls(V_HV_CTRL_RANGE_0, false);
	LL_SetStateCtrls(V_HV_CTRL_RANGE_1, false);
	LL_SetStateCtrls(V_HV_CTRL_RANGE_3, false);
}
//-----------------------------
void LL_SelectRg720K()
{
	LL_SetStateCtrls(V_HV_CTRL_RANGE_3, true);
	//
	LL_SetStateCtrls(V_HV_CTRL_RANGE_0, false);
	LL_SetStateCtrls(V_HV_CTRL_RANGE_1, false);
	LL_SetStateCtrls(V_HV_CTRL_RANGE_2, false);
}
//-----------------------------

void LL_RelayCtrls(uint16_t Relay, bool State)
{
	switch (Relay)
	{
		case RELAY_BUS:
			{
				LL_SetStateCtrls(RLC_CTRL1, State);
			}
			break;

		case RELAY_PS1:
			{
				LL_SetStateCtrls(RLC_CTRL2, State);
			}
			break;

		case RELAY_PS2:
			{
				LL_SetStateCtrls(RLC_CTRL3, State);
			}
			break;

		case RELAY_CTRL:
			{
				LL_SetStateCtrls(RLC_CTRL4, State);
			}
			break;

		case RELAY_POT:
			{
				LL_SetStateCtrls(RLC_CTRL5, State);
			}
			break;

		case RELAY_POT_CTRLN:
			{
				LL_SetStateCtrls(RLC_CTRL6, State);
			}
			break;

		case RELAY_POT_CTRLP:
			{
				LL_SetStateCtrls(RLC_CTRL7, State);
			}
			break;
		case RELAY_LV_HV_CTRL1:
			{
				LL_SetStateCtrls(LV_HV_CTRL1, State);
			}
			break;
		case RELAY_LV_HV_CTRL2:
			{
				LL_SetStateCtrls(LV_HV_CTRL2, State);
			}
			break;
	}
}

void LL_SelectAdcSrcILV()
{
	LL_SetStateCtrls(LV_CUR_SENS_EN, false);
	LL_SetStateCtrls(HV_CUR_SENS_EN, false);
	//
	LL_SetStateCtrls(LV_CUR_SENS_EN, true);
}
//-----------------------------

void LL_SelectAdcSrcIHV()
{
	LL_SetStateCtrls(LV_CUR_SENS_EN, false);
	LL_SetStateCtrls(HV_CUR_SENS_EN, false);
	//
	LL_SetStateCtrls(HV_CUR_SENS_EN, true);
}
//-----------------------------
