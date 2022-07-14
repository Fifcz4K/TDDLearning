#ifndef HEARTBEAT_H
#define HEARTBEAT_H

#include "stdio.h"
#include "stdbool.h"
#include "stdint.h"

#define CORRECT_SIGNAL_PERIOD 100
#define CHECK_PERIOD 10
#define CORRECT_SIGNAL_COUNTER (CORRECT_SIGNAL_PERIOD / CHECK_PERIOD)
#define HEARTBEAT_TOLERANCE 1

typedef enum 
{
    GPIO_LOW,
    GPIO_HIGH
}GPIO_State_t;

void HeartbeatInit(void);
bool HeartbeatCheck(GPIO_State_t hbPinState);

#endif // HEARTBEAT_H