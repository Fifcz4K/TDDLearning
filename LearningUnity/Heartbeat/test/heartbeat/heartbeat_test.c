#include "unity/fixture/unity_fixture.h"
#include "../../../fff-master/fff.h"
#include "heartbeat.h"

DEFINE_FFF_GLOBALS;
FAKE_VALUE_FUNC(GPIO_State_t, heartbeat_pin_get);

TEST_GROUP(heartbeat);

TEST_SETUP(heartbeat)
{
    heartbeat_pin_get_fake.return_val = GPIO_LOW;
    HeartbeatInit();
}

TEST_TEAR_DOWN(heartbeat)
{
}

TEST(heartbeat, PinLowAfterInit)
{
    TEST_ASSERT_EQUAL(GPIO_LOW, heartbeat_pin_get());
}


