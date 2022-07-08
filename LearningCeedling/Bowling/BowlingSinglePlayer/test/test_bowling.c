#include "unity.h"

#include "bowling.h"

void setUp(void)
{
    GameReset();
}

void tearDown(void)
{
}

void test_score_after_1_roll(void)
{
    Roll(5);

    TEST_ASSERT_EQUAL(5, Score());
}

void test_score_after_2_rolls(void)
{
    Roll(5);
    Roll(3);

    TEST_ASSERT_EQUAL(8, Score());
}







