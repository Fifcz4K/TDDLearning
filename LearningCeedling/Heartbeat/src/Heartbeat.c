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

bool HeartbeatCheck(GPIO_State_t hbPinState)
{
    if(hbPinState != lastPinState)
    {
        lastPinState = hbPinState;
        if(heartbeatCnt < CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE)
        {
            wrongHeartbeatCnt++;
        }
        else
        {
            wrongHeartbeatCnt = 0;
        }

        heartbeatCnt = 1;
    }
    else
    {
        heartbeatCnt++;
        if(heartbeatCnt > CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE)
        {
            wrongHeartbeatCnt++;
            heartbeatCnt = 0;
            lastPinState = 1 - lastPinState;
        }
    }

    if(wrongHeartbeatCnt >= 3)
    {
        safeState = true;
    }

    return safeState;
}