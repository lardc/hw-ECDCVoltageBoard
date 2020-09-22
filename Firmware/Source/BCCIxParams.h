// -----------------------------------------
// Parameters of BCCI interface
// ----------------------------------------

#ifndef __BCCI_PARAMS_H
#define __BCCI_PARAMS_H

#include "xCCIParams.h"

// Маска поля функции
//
#define CAN_FUNC_MASK				0x000003FF

// Конфигурация Slave
//
#define CAN_SLAVE_NID				101				// Node ID устройства		//TODO change CAN_SLAVE_NID
#define CAN_SLAVE_NID_MASK			0x0003FC00		// Маска Slave node ID		//TODO change CAN_SLAVE_NID_MASK
#define CAN_SLAVE_NID_MPY			10				// Смещение адреса Slave	//TODO change CAN_SLAVE_NID_MPY

// Конфигурация Master
//
#define CAN_MASTER_NID				20				// Node ID устройства		//TODO change CAN_MASTER_NID
#define CAN_MASTER_NID_MASK			0x03FC0000		// Маска Master node ID		//TODO change CAN_MASTER_NID_MASK
#define CAN_MASTER_NID_MPY			18				// Смещение адреса Master	//TODO change CAN_MASTER_NID_MPY

// CAN фильтр
//
#define CAN_SLAVE_FILTER_ID				(CAN_SLAVE_NID << CAN_SLAVE_NID_MPY)
#define CAN_MASTER_FILTER_ID			(CAN_MASTER_NID << CAN_MASTER_NID_MPY)

#endif // __BCCI_PARAMS_H
