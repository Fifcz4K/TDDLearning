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

void test_strike(void)
{
    uint16_t expected = 0;

    expected += Turn(10, 0);
    expected += Turn(2, 4);

    //Bonus for strike
    expected += 2 + 4;

    TEST_ASSERT_EQUAL(expected, Score());
}

void test_2_strikes_in_a_row(void)
{
    uint16_t expected = 0;

    expected += Turn(10, 0);
    expected += Turn(10, 0);
    expected += Turn(1, 2);

    //Bonus for strike
    expected += 10 + 1;
    expected += 1 + 2;

    TEST_ASSERT_EQUAL(expected, Score());
}

void test_spare_in_last_round(void)
{
    uint16_t expected = 0;

    for(uint8_t i = 0; i < 9; i++)
    {
        Turn(0, 0);
    }

    Roll(2);
    Roll(8);
    Roll(4);

    expected = 2 + 8 + 4;

    TEST_ASSERT_EQUAL(expected, Score());
}

void test_strike_in_last_round(void)
{
    uint16_t expected = 0;

    for(uint8_t i = 0; i < 9; i++)
    {
        Turn(0, 0);
    }

    Roll(10);
    Roll(10);
    Roll(4);

    expected = 10 + 10 + 4;

    TEST_ASSERT_EQUAL(expected, Score());
}

void test_random_game_1(void)
{
    Turn(5, 5);
    Turn(4, 0);
    Turn(8, 1);
    Turn(10, 0);
    Turn(0, 10);
    Turn(10, 0);
    Turn(10, 0);
    Turn(10, 0);
    Turn(4, 6);

    Roll(10);
    Roll(10);
    Roll(5);

    TEST_ASSERT_EQUAL(186, Score());
}

void test_only_9_0_game(void)
{
    Turn(9, 0);
    Turn(9, 0);
    Turn(9, 0);
    Turn(9, 0);
    Turn(9, 0);
    Turn(9, 0);
    Turn(9, 0);
    Turn(9, 0);
    Turn(9, 0);

    Roll(9);
    Roll(0);

    TEST_ASSERT_EQUAL(90, Score());
}

void test_only_9_spare_game(void)
{
    Turn(9, 1);
    Turn(9, 1);
    Turn(9, 1);
    Turn(9, 1);
    Turn(9, 1);
    Turn(9, 1);
    Turn(9, 1);
    Turn(9, 1);
    Turn(9, 1);

    Roll(9);
    Roll(1);
    Roll(9);

    TEST_ASSERT_EQUAL(190, Score());
}

void test_perfect_game(void)
{
    Turn(10, 0);
    Turn(10, 0);
    Turn(10, 0);
    Turn(10, 0);
    Turn(10, 0);
    Turn(10, 0);
    Turn(10, 0);
    Turn(10, 0);
    Turn(10, 0);
    Turn(10, 0);

    Roll(10);
    Roll(10);
    Roll(10);

    TEST_ASSERT_EQUAL(300, Score());
}

