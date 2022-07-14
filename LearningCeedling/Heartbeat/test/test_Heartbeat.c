#include "unity.h"

#include "Heartbeat.h"

void setUp(void)
{
    HeartbeatInit();
}

void tearDown(void)
{
}

static bool heartbeat_n_times(GPIO_State_t pinState, uint8_t times)
{
    bool safeState = false;

    for(uint8_t i = 0; i < times; i++)
    {
        safeState = HeartbeatCheck(pinState);
    }

    return safeState;
}

void test_NoSafeStateAfter3correctHeartbeats(void)
{
    bool safeState = false;

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER);

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER);

    TEST_ASSERT_EQUAL(false, safeState);
}

void test_SafeStateWhen3timesInRowHeartbeatTooShort(void)
{
    bool safeState = false;

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE - 1);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE - 1);

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE - 1);

    safeState = HeartbeatCheck(GPIO_HIGH);

    TEST_ASSERT_EQUAL(true, safeState);
}

void test_SafeStateWhen3timesInRowHeartbeatTooLong(void)
{
    bool safeState = false;

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE + 1);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE + 1);

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE + 1);

    TEST_ASSERT_EQUAL(true, safeState);
}

void test_NoSafeStateWhenHeartbeatInTolerance_1(void)
{
    bool safeState = false;

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE);

    TEST_ASSERT_EQUAL(false, safeState);
}

void test_NoSafeStateWhenHeartbeatInTolerance_2(void)
{
    bool safeState = false;

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE);

    TEST_ASSERT_EQUAL(false, safeState);
}

void test_NoSafeStateWhenHeartbeatInTolerance_3(void)
{
    bool safeState = false;

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE);

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE);

    TEST_ASSERT_EQUAL(false, safeState);
}

void test_NoSafeStateWhenWrongHeartbeat3TimesNotInRow(void)
{
    bool safeState = false;

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE - 1);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE - 1);

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE + 1);

    TEST_ASSERT_EQUAL(false, safeState);
}

void test_SafeStateWhenWrong2InRowThenCorrectThenWrong3InRow(void)
{
    bool safeState = false;

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE - 1);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER + HEARTBEAT_TOLERANCE - 1);

    safeState = heartbeat_n_times(GPIO_LOW, CORRECT_SIGNAL_COUNTER);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE - 1);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE - 1);

    safeState = heartbeat_n_times(GPIO_HIGH, CORRECT_SIGNAL_COUNTER - HEARTBEAT_TOLERANCE - 1);

    TEST_ASSERT_EQUAL(true, safeState);
}


