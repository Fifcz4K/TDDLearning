#include "gmock/gmock.h"

typedef uint16_t adc_value_t;

class AdcMock
{
    public:
        virtual ~AdcMock() = default;
        MOCK_METHOD0(getAdcValue, adc_value_t());
};

void adcMockInit(AdcMock *mock);
