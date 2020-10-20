#ifndef CONTROLLER_VOLTAGEBOARD_H_
#define CONTROLLER_VOLTAGEBOARD_H_

void VB_SaveParam(ControllerConfig *Config);
bool VB_CheckParam(ControllerConfig *Config);
void VB_EnableVoltageChannel(ControllerConfig *Config);
void VB_DisableVoltageChannel();
void VB_EnableCurrentChannel(ControllerConfig *Config);
void VB_RelayCommutation(ControllerConfig *Config);
void VB_SetCurrentLimit();
#endif /* CONTROLLER_VOLTAGEBOARD_H_ */
