#ifndef HEARTBEAT_H
#define HEARTBEAT_H

#include "stdio.h"
#include "stdbool.h"
#include "stdint.h"
#include "m_gpio.h"

#define CORRECT_SIGNAL_PERIOD 100
#define CHECK_PERIOD 10
#define CORRECT_SIGNAL_COUNTER (CORRECT_SIGNAL_PERIOD / CHECK_PERIOD)
#define HEARTBEAT_TOLERANCE 1

void HeartbeatInit(void);
bool HeartbeatCheck(void);

#endif // HEARTBEAT_H