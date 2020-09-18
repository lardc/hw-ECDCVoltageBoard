#ifndef __BOARD_H
#define __BOARD_H

#include "stm32f30x.h"

#include "ZwRCC.h"
#include "ZwGPIO.h"
#include "ZwNCAN.h"
#include "ZwTIM.h"
#include "ZwDAC.h"
#include "ZwDMA.h"
#include "ZwADC.h"
#include "ZwEXTI.h"
#include "ZwSCI.h"
#include "ZwIWDG.h"
#include "ZwNFLASH.h"
#include "ZwSPI.h"

// Определения для выходных портов
GPIO_PortPinSettingMacro GPIO_CS1			= {GPIOB, Pin_0};	//U4
GPIO_PortPinSettingMacro GPIO_CS2			= {GPIOA, Pin_2};	//U2
GPIO_PortPinSettingMacro GPIO_CS3			= {GPIOA, Pin_1};	//U3
GPIO_PortPinSettingMacro GPIO_DAC_CS		= {GPIOA, Pin_3};	//U3
GPIO_PortPinSettingMacro GPIO_LDAC1			= {GPIOB, Pin_1};	//U35
GPIO_PortPinSettingMacro GPIO_LDAC2			= {GPIOB, Pin_2};	//U29
GPIO_PortPinSettingMacro GPIO_SREG_CS		= {GPIOB, Pin_11};	//U5
GPIO_PortPinSettingMacro GPIO_SREG_OE1		= {GPIOB, Pin_10};	//U5
GPIO_PortPinSettingMacro GPIO_RCK			= {GPIOA, Pin_6};	//U2, U3, U4
GPIO_PortPinSettingMacro GPIO_LED			= {GPIOB, Pin_7};
GPIO_PortPinSettingMacro GPIO_EXT_LED		= {GPIOC, Pin_14};

// Определения для линий синхронизации
GPIO_PortPinSettingMacro GPIO_SYNC1_IN		= {GPIOB, Pin_14};
GPIO_PortPinSettingMacro GPIO_SYNC2_IN		= {GPIOB, Pin_15};
GPIO_PortPinSettingMacro GPIO_SYNC1_OUT		= {GPIOB, Pin_13};
GPIO_PortPinSettingMacro GPIO_SYNC2_OUT		= {GPIOB, Pin_12};

// Определения для портов альтернативных функций
GPIO_PortPinSettingMacro GPIO_ALT_CAN_RX	= {GPIOA, Pin_11};
GPIO_PortPinSettingMacro GPIO_ALT_CAN_TX	= {GPIOA, Pin_12};
GPIO_PortPinSettingMacro GPIO_ALT_UART1_TX	= {GPIOA, Pin_9};
GPIO_PortPinSettingMacro GPIO_ALT_UART1_RX	= {GPIOA, Pin_10};
GPIO_PortPinSettingMacro GPIO_ALT_SPI1_CLK	= {GPIOA, Pin_5};	//U2, U3, U4, U5, U29, U35
GPIO_PortPinSettingMacro GPIO_ALT_SPI1_MOSI	= {GPIOA, Pin_7};	//U2, U3, U4, U5, U29, U35

//Определения для аналоговых портов
GPIO_PortPinSettingMacro GPIO_MEASURE_V		= {GPIOA, Pin_4};	//AD2_1
GPIO_PortPinSettingMacro GPIO_MEASURE_I		= {GPIOA, Pin_0};	//AD1_1

#endif // __BOARD_H
