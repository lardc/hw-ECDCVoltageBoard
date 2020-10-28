#ifndef __VOLTAGE_BOARD_H
#define __VOLTAGE_BOARD_H

#include "Controller.h"

bool VB_CacheParameters(ControllerConfig *Config);
void VB_ConfigVIChannels(ControllerConfig *Config);
void VB_SetLimitVIOutputs(ControllerConfig *Config);

#endif // __VOLTAGE_BOARD_H
