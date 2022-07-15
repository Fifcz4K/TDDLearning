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

static bool heartbeat_n_times(GPIO_State_t pinState, uint8_t times)
{
    bool safeState = false;

    heartbeat_pin_get_fake.return_val = pinState;

    for(uint8_t i = 0; i < times; i++)
    {
        safeState = HeartbeatCheck();
    }

    return safeState;
}

TEST(heartbeat, PinLowAfterInit)
{
    TEST_ASSERT_EQUAL(GPIO_LOW, heartbeat_pin_get());
}

TEST(heartbeat, SafeStateWhen3TooShortHeartbeatsInRow)
{
    bool safeState = false;

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE - 1);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE - 1);

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE - 1);
    
    heartbeat_pin_get_fake.return_val = GPIO_HIGH;
    safeState = HeartbeatCheck();

    TEST_ASSERT_EQUAL(true, safeState);
}

TEST(heartbeat, SafeStateWhen3TooLongHeartbeatsInRow)
{
    bool safeState = false;

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE + 1);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE + 1);

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE + 1);
    
    TEST_ASSERT_EQUAL(true, safeState);
}

TEST(heartbeat, NoSafeStateWhen3HeartbeatsInTolerance_1)
{
    bool safeState = false;

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE);

    heartbeat_pin_get_fake.return_val = GPIO_HIGH;

    safeState = HeartbeatCheck();
    
    TEST_ASSERT_EQUAL(false, safeState);
}

TEST(heartbeat, NoSafeStateWhen3HeartbeatsInTolerance_2)
{
    bool safeState = false;

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE);

    TEST_ASSERT_EQUAL(false, safeState);
}

TEST(heartbeat, NoSafeStateWhen3HeartbeatsInTolerance_3)
{
    bool safeState = false;

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE);

    TEST_ASSERT_EQUAL(false, safeState);
}

TEST(heartbeat, NoSafeStateWhen3WrongHeartbeatsNotInRow)
{
    bool safeState = false;

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE + 1);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE - 1);

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE + 1);

    TEST_ASSERT_EQUAL(false, safeState);
}

TEST(heartbeat, SafeStateWhen2WrongHeartbeatsThenOkThen3Wrong)
{
    bool safeState = false;

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE + 1);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE - 1);

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE + 1);

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE + 1);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE + 1);

    TEST_ASSERT_EQUAL(true, safeState);
}



