#include "m_led_mock.h"

static LedMock *LedMockObj = nullptr;
void ledMockInit(LedMock *mock)
{
    LedMockObj = mock;
}

extern "C"
{
    #include "../m_led.h"
    void LedOff()
    {
        return (LedMockObj != nullptr) ? LedMockObj->LedOff() : 0;
    }

    void LedOn()
    {
        return (LedMockObj != nullptr) ? LedMockObj->LedOn() : 0;
    }
}