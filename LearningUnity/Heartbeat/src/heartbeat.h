#ifndef HEARTBEAT_H
#define HEARTBEAT_H

#include "stdio.h"
#include "stdbool.h"
#include "stdint.h"
#include "m_gpio.h"

#define STATE_PERIOD 100
#define CHECK_PERIOD 10
#define PERFECT_SIGNAL_COUNTER (STATE_PERIOD / CHECK_PERIOD)
#define HEARTBEAT_TOLERANCE 1

void HeartbeatInit(void);
bool HeartbeatCheck(void);

#endif // HEARTBEAT_H