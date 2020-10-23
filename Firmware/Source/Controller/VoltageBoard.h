#ifndef __VOLTAGE_BOARD_H
#define __VOLTAGE_BOARD_H

#include "Controller.h"

void VB_SaveParam(ControllerConfig *Config);
bool VB_CheckParam(ControllerConfig *Config);
void VB_EnableVoltageChannel(ControllerConfig *Config);
void VB_EnableCurrentChannel(ControllerConfig *Config);
void VB_RelayCommutation(ControllerConfig *Config);

#endif // __VOLTAGE_BOARD_H
