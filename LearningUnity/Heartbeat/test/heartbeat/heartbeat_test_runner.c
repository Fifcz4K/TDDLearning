#include "unity/fixture/unity_fixture.h"

TEST_GROUP_RUNNER(heartbeat)
{
   /* Test cases to run */
   RUN_TEST_CASE(heartbeat, PinLowAfterInit);
}
