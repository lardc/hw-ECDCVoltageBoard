// Header
#include "LowLevel.h"
// Include
#include "Board.h"
#include "Delay.h"
#include "Global.h"
#include <string.h>

// Defines
#define DAC_CHANNEL_B		BIT15
#define CTRL_SIZE			(8 * 3)		// Три восьмибитных регистра

// Variables
//
uint8_t CONTROL_UnitCtrls[CTRL_SIZE];
uint8_t CONTROL_UnitRanges;

// Forward functions
void LL_WriteDACx(uint16_t Data, GPIO_PortPinSetting GPIO_LDACx);

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
	SPI_InvertClockPolarity(SPI1, false);

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
	SPI_InvertClockPolarity(SPI1, false);

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

void LL_WriteDACx(uint16_t Data, GPIO_PortPinSetting GPIO_LDACx)
{
	//SPI_InvertClockPolarity(SPI1, true);

	if((Data&0xfff) > DAC_MAX_RESOLUTION)
		Data = (Data&0x8000) | DAC_MAX_RESOLUTION;

	GPIO_SetState(GPIO_DAC_CS, false);
	SPI_WriteByte8b(SPI1, (Data >> 8) & 0xff);
	SPI_WriteByte8b(SPI1, Data & 0xff);
	GPIO_SetState(GPIO_DAC_CS, true);
	DELAY_US(1);

	GPIO_SetState(GPIO_LDACx, false);
	DELAY_US(10);
	GPIO_SetState(GPIO_LDACx, true);
	DELAY_US(10);
}
//-----------------------------

void LL_WriteDACLV_Voltage(uint16_t Data)
{
	LL_WriteDACx(Data & ~DAC_CHANNEL_B, GPIO_LDAC1);
}
//-----------------------------

void LL_WriteDACLV_Current(uint16_t Data)
{
	LL_WriteDACx(Data | DAC_CHANNEL_B, GPIO_LDAC1);
}
//-----------------------------

void LL_WriteDACHV_Voltage(uint16_t Data)
{
	LL_WriteDACx(Data | DAC_CHANNEL_B, GPIO_LDAC2);
}
//-----------------------------

void LL_WriteDACHV_Current(uint16_t Data)
{
	LL_WriteDACx(Data & ~DAC_CHANNEL_B, GPIO_LDAC2);
}
//-----------------------------

void LL_ResetDACOutputs()
{
	LL_WriteDACLV_Voltage(0);
	LL_WriteDACLV_Current(0);
	LL_WriteDACHV_Voltage(0);
	LL_WriteDACHV_Current(0);
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

void LL_SelectRsNone()
{
	LL_SetStateRanges(LV_CTRL_RANGE_0, false);
	LL_SetStateRanges(LV_CTRL_RANGE_1, false);
	LL_SetStateRanges(LV_CTRL_RANGE_2, false);
	LL_SetStateRanges(LV_CTRL_RANGE_3, false);
}
//-----------------------------

void LL_SelectAdcSrcVLV()
{
	LL_SetStateCtrls(LV_SENS_EN, false);
	LL_SetStateCtrls(HV_SENS_EN, false);
	LL_SetStateCtrls(PT_SENS_EN, false);
	LL_SetStateCtrls(PT_CTRL_SENS_EN, false);
	//
	LL_SetStateCtrls(LV_SENS_EN, true);
}
//-----------------------------

void LL_SelectAdcSrcHV()
{
	LL_SetStateCtrls(LV_SENS_EN, false);
	LL_SetStateCtrls(HV_SENS_EN, false);
	LL_SetStateCtrls(PT_SENS_EN, false);
	LL_SetStateCtrls(PT_CTRL_SENS_EN, false);
	//
	LL_SetStateCtrls(HV_SENS_EN, true);
}
//-----------------------------

void LL_SelectAdcSrcPT()
{
	LL_SetStateCtrls(LV_SENS_EN, false);
	LL_SetStateCtrls(HV_SENS_EN, false);
	LL_SetStateCtrls(PT_SENS_EN, false);
	LL_SetStateCtrls(PT_CTRL_SENS_EN, false);
	//
	LL_SetStateCtrls(PT_SENS_EN, true);
}
//-----------------------------

void LL_SelectAdcSrcPTCtrl()
{
	LL_SetStateCtrls(LV_SENS_EN, false);
	LL_SetStateCtrls(HV_SENS_EN, false);
	LL_SetStateCtrls(PT_SENS_EN, false);
	LL_SetStateCtrls(PT_CTRL_SENS_EN, false);
	//
	LL_SetStateCtrls(PT_CTRL_SENS_EN, true);
}
//-----------------------------

void LL_SelectAdcSrcNO()
{
	LL_SetStateCtrls(LV_SENS_EN, false);
	LL_SetStateCtrls(HV_SENS_EN, false);
	LL_SetStateCtrls(PT_SENS_EN, false);
	LL_SetStateCtrls(PT_CTRL_SENS_EN, false);
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

void LL_SelectHV_R1()
{
	LL_SetStateRanges(HV_CTRL_RANGE_0, true);
	LL_SetStateRanges(HV_CTRL_RANGE_1, true);
	LL_SetStateRanges(HV_CTRL_RANGE_2, true);
}
//-----------------------------

void LL_SelectHV_R2()
{
	LL_SetStateRanges(HV_CTRL_RANGE_0, true);
	LL_SetStateRanges(HV_CTRL_RANGE_1, true);
	LL_SetStateRanges(HV_CTRL_RANGE_2, false);
}
//-----------------------------

void LL_SelectHV_R3()
{
	LL_SetStateRanges(HV_CTRL_RANGE_0, true);
	LL_SetStateRanges(HV_CTRL_RANGE_1, false);
	LL_SetStateRanges(HV_CTRL_RANGE_2, false);
}
//-----------------------------

void LL_SelectHV_R4()
{
	LL_SetStateRanges(HV_CTRL_RANGE_0, false);
	LL_SetStateRanges(HV_CTRL_RANGE_1, false);
	LL_SetStateRanges(HV_CTRL_RANGE_2, false);
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

		case RELAY_POT_CTRL:
			{
				LL_SetStateCtrls(RLC_CTRL6, State);
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
//-----------------------------

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
