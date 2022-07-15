#include "heartbeat.h"

static bool safeState = false;
static uint8_t wrongHeartbeatCnt = 0;
static uint8_t heartbeatCnt = 0;
static GPIO_State_t lastPinState = GPIO_LOW;

void HeartbeatInit(void)
{
    safeState = false;
    wrongHeartbeatCnt = 0;
    heartbeatCnt = 0;
    lastPinState = GPIO_LOW;
}

bool HeartbeatCheck(void)
{
    GPIO_State_t pinState = heartbeat_pin_get();

    if(pinState == GPIO_HIGH)
    {
        safeState = true;
    }

    return safeState;
}