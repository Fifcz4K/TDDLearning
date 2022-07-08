#include "unity.h"

#include "bowling.h"

void setUp(void)
{
    GameReset();
}

void tearDown(void)
{
}

static uint8_t Turn(uint8_t roll_1, uint8_t roll_2)
{
    Roll(roll_1);
    Roll(roll_2);

    return roll_1 + roll_2;
}

void test_score_after_1_roll(void)
{
    uint16_t expected = 0;
    
    expected = Turn(5, 0);

    TEST_ASSERT_EQUAL(expected, Score());
}

void test_score_after_2_rolls(void)
{
    uint16_t expected = 0;

    expected = Turn(5, 3);

    TEST_ASSERT_EQUAL(expected, Score());
}

void test_score_after_game_without_bonuses(void)
{
    uint16_t expected = 0;

    expected += Turn(1, 3);
    expected += Turn(5, 2);
    expected += Turn(1, 4);
    expected += Turn(8, 1);
    expected += Turn(0, 5);
    expected += Turn(9, 0);
    expected += Turn(0, 8);
    expected += Turn(3, 0);
    expected += Turn(0, 0);
    expected += Turn(9, 0);

    TEST_ASSERT_EQUAL(expected, Score());
}

void test_spare(void)
{
    uint16_t expected = 0;

    expected += Turn(5, 5);
    expected += Turn(3, 4);

    //Bonus for spare
    expected += 3;

    TEST_ASSERT_EQUAL(expected, Score());
}

void test_2_spares_in_a_row(void)
{
    uint16_t expected = 0;

    expected += Turn(5, 5);
    expected += Turn(5, 5);
    expected += Turn(1, 0);

    //Bonus for spare
    expected += 5;
    expected += 1;

    TEST_ASSERT_EQUAL(expected, Score());
}



