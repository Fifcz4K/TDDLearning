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

    if(pinState != lastPinState)
    {
        lastPinState = pinState;
        if(heartbeatCnt < CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE)
        {
            wrongHeartbeatCnt++;
            heartbeatCnt = 0;
        }
        else
        {
            wrongHeartbeatCnt = 0;
            heartbeatCnt = 1;
        }
    }
    else
    {
        heartbeatCnt++;
        
        if(heartbeatCnt > CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE)
        {
            heartbeatCnt = 0;
            wrongHeartbeatCnt++;
            lastPinState = 1 - lastPinState;
        }
    }

    if(wrongHeartbeatCnt >= 3)
    {
        safeState = true;
    }

    return safeState;
}