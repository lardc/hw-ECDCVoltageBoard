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

// ”правление выходами CTRL
void LL_UpdateStateCtrls()
{
	//no need CS control
	uint32_t i = CTRL_SIZE;
	while(i--) 	SPI_WriteByte8b(SPI1, CONTROL_UnitCtrls[i]);
	//latch DATA / update state pin
	GPIO_SetState(GPIO_RCK, true);
	GPIO_SetState(GPIO_RCK, false);
}
//-----------------------------

void LL_ResetStateCtrls()
{
	memset(CONTROL_UnitCtrls,0,CTRL_SIZE);
	LL_UpdateStateCtrls();
}
//-----------------------------
void LL_SetStateCtrls(SetCtrls Pin, bool State)
{
	uint32_t Nbyte;
	uint32_t Nbit;

	Nbyte = Pin/8;
	Nbit = Pin%8;
	if (State)
	{
		CONTROL_UnitCtrls[Nbyte] |= 1<<Nbit;
	}
	else
	{
		CONTROL_UnitCtrls[Nbyte] &= ~(1<<Nbit);
	}
	LL_UpdateStateCtrls();
}
//-----------------------------

// ”правление выходами RANGE
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

	Nbit = Pin%8;
	if (State)
	{
		CONTROL_UnitRanges |= 1<<Nbit;
	}
	else
	{
		CONTROL_UnitRanges &= ~(1<<Nbit);
	}
	LL_UpdateStateRanges();
}
//-----------------------------

void LL_WriteDAC_LH(uint16_t Data)
{
	GPIO_SetState(GPIO_DAC_CS, false);


	SPI_WriteByte8b(SPI1, (Data>>8)&0xff);
	SPI_WriteByte8b(SPI1, Data&0xff);

	GPIO_SetState(GPIO_DAC_CS, true);
}
//-----------------------------

void LL_SelectDACx(SelDacX dac)
{
	switch (dac){
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


