#include "unity/fixture/unity_fixture.h"

TEST_GROUP_RUNNER(heartbeat)
{
   /* Test cases to run */
   RUN_TEST_CASE(heartbeat, PinLowAfterInit);
   RUN_TEST_CASE(heartbeat, SafeStateWhen3TooShortHeartbeatsInRow);
   RUN_TEST_CASE(heartbeat, SafeStateWhen3TooLongHeartbeatsInRow);
   RUN_TEST_CASE(heartbeat, NoSafeStateWhen3HeartbeatsInTolerance_1);
   RUN_TEST_CASE(heartbeat, NoSafeStateWhen3HeartbeatsInTolerance_2);
   RUN_TEST_CASE(heartbeat, NoSafeStateWhen3HeartbeatsInTolerance_3);
   RUN_TEST_CASE(heartbeat, NoSafeStateWhen3WrongHeartbeatsNotInRow);
   RUN_TEST_CASE(heartbeat, SafeStateWhen2WrongHeartbeatsThenOkThen3Wrong);
}
