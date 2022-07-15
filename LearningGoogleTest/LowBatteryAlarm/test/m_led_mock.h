#include "gmock/gmock.h"

class LedMock
{
    public:
        virtual ~LedMock() = default;
        MOCK_METHOD0(LedOff, void());
        MOCK_METHOD0(LedOn, void());
};

void ledMockInit(LedMock *mock);
