#include "m_adc_mock.h"

static AdcMock *AdcMockObj = nullptr;
void adcMockInit(AdcMock *mock)
{
    AdcMockObj = mock;
}

extern "C"
{
    #include "../m_adc.h"
    adc_value_t getAdcValue()
    {
        return (AdcMockObj != nullptr) ? AdcMockObj->getAdcValue() : 0;
    }
}