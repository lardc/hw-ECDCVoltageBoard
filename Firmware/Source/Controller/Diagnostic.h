#ifndef __DIAGNOSTIC_H
#define __DIAGNOSTIC_H

// Include
#include "stdinc.h"

// Define
#define TIME_PULSE_LINE_SYNC	100

// Functions
bool DIAG_HandleDiagnosticAction(uint16_t ActionID, uint16_t *pUserError);

#endif // __DIAGNOSTIC_H
