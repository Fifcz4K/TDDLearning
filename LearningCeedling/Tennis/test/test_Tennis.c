#include "unity.h"

#include "Tennis.h"

void setUp(void)
{
    GameReset();
}

void tearDown(void)
{
}

static void winGem(Player_t player)
{
    for(uint8_t i = 0; i < 4; i++)
    {
        WinBall(player);
    }
}

static void winSet(Player_t player)
{
    for(uint8_t i = 0; i < GEMS_TO_WIN; i++)
    {
        winGem(player);
    }
}

void test_player_has_points_after_winning_a_ball(void)
{
    WinBall(Player_1);
    WinBall(Player_2);
    WinBall(Player_2);
    WinBall(Player_1);
    WinBall(Player_1);

    TEST_ASSERT_EQUAL(40, Score(Player_1)->points);
    TEST_ASSERT_EQUAL(30, Score(Player_2)->points);
}

void test_player_1_has_1_gem_and_0_points_after_4_won_balls(void)
{
    WinBall(Player_1);
    WinBall(Player_2);
    WinBall(Player_1);
    WinBall(Player_1);
    WinBall(Player_1);

    TEST_ASSERT_EQUAL(0, Score(Player_1)->points);
    TEST_ASSERT_EQUAL(0, Score(Player_2)->points);
    TEST_ASSERT_EQUAL(1, Score(Player_1)->gems);
}

void test_not_adding_gem_when_deuce(void)
{
    WinBall(Player_1);
    WinBall(Player_1);
    WinBall(Player_1);
    WinBall(Player_2);
    WinBall(Player_2);
    WinBall(Player_2);

    WinBall(Player_2);

    TEST_ASSERT_EQUAL(40, Score(Player_1)->points);
    TEST_ASSERT_EQUAL(40, Score(Player_2)->points);
    TEST_ASSERT_EQUAL(0, Score(Player_1)->gems);
    TEST_ASSERT_EQUAL(0, Score(Player_2)->gems);
}

void test_player_1_wins_gem_after_deuce(void)
{
    WinBall(Player_1);
    WinBall(Player_1);
    WinBall(Player_1);
    WinBall(Player_2);
    WinBall(Player_2);
    WinBall(Player_2);

    WinBall(Player_2);
    WinBall(Player_1);
    WinBall(Player_1);
    WinBall(Player_2);
    WinBall(Player_1);
    WinBall(Player_1);

    TEST_ASSERT_EQUAL(0, Score(Player_1)->points);
    TEST_ASSERT_EQUAL(0, Score(Player_2)->points);
    TEST_ASSERT_EQUAL(1, Score(Player_1)->gems);
    TEST_ASSERT_EQUAL(0, Score(Player_2)->gems);
}

void test_player_1_has_1_set_after_enough_won_gems(void)
{
    winSet(Player_1);

    TEST_ASSERT_EQUAL(0, Score(Player_1)->points);
    TEST_ASSERT_EQUAL(0, Score(Player_2)->points);
    TEST_ASSERT_EQUAL(0, Score(Player_1)->gems);
    TEST_ASSERT_EQUAL(0, Score(Player_2)->gems);
    TEST_ASSERT_EQUAL(1, Score(Player_1)->sets);
    TEST_ASSERT_EQUAL(0, Score(Player_2)->sets);
}

void test_not_adding_set_when_less_than_2_gems_advantage(void)
{
    for(uint8_t i = 0; i < GEMS_TO_WIN - 1; i++)
    {
        winGem(Player_1);   // after loop, score is 5 to 5 in gems
        winGem(Player_2);
    }

    winGem(Player_1);

    TEST_ASSERT_EQUAL(0, Score(Player_1)->points);
    TEST_ASSERT_EQUAL(0, Score(Player_2)->points);
    TEST_ASSERT_EQUAL(GEMS_TO_WIN, Score(Player_1)->gems);
    TEST_ASSERT_EQUAL(GEMS_TO_WIN - 1, Score(Player_2)->gems);
    TEST_ASSERT_EQUAL(0, Score(Player_1)->sets);
    TEST_ASSERT_EQUAL(0, Score(Player_2)->sets);
}

void test_add_set_when_7_to_5_in_gems(void)
{
    for(uint8_t i = 0; i < GEMS_TO_WIN - 1; i++)
    {
        winGem(Player_1);   // after loop, both players has 1 less gem than needed to win
        winGem(Player_2);
    }

    winGem(Player_1);
    winGem(Player_1);

    TEST_ASSERT_EQUAL(0, Score(Player_1)->points);
    TEST_ASSERT_EQUAL(0, Score(Player_2)->points);
    TEST_ASSERT_EQUAL(0, Score(Player_1)->gems);
    TEST_ASSERT_EQUAL(0, Score(Player_2)->gems);
    TEST_ASSERT_EQUAL(1, Score(Player_1)->sets);
    TEST_ASSERT_EQUAL(0, Score(Player_2)->sets);
}

void test_tie_break(void)
{
    for(uint8_t i = 0; i < GEMS_TO_WIN; i++)
    {
        winGem(Player_1);   // TIE-BREAK AFTER LOOP
        winGem(Player_2);
    }

    for(uint8_t i = 0; i < POINTS_TO_WIN_TIE_BREAK; i++)
    {
        WinBall(Player_1); // 7 points to win the set in tie-break
    }

    TEST_ASSERT_EQUAL(0, Score(Player_1)->points);
    TEST_ASSERT_EQUAL(0, Score(Player_2)->points);
    TEST_ASSERT_EQUAL(0, Score(Player_1)->gems);
    TEST_ASSERT_EQUAL(0, Score(Player_2)->gems);
    TEST_ASSERT_EQUAL(1, Score(Player_1)->sets);
    TEST_ASSERT_EQUAL(0, Score(Player_2)->sets);
}

void test_tie_break_with_advantage(void)
{
    for(uint8_t i = 0; i < GEMS_TO_WIN; i++)
    {
        winGem(Player_1);   // TIE-BREAK AFTER LOOP
        winGem(Player_2);
    }

    for(uint8_t i = 0; i < POINTS_TO_WIN_TIE_BREAK - 1; i++)
    {
        WinBall(Player_1);
        WinBall(Player_2); // 6 TO 6 IN POINTS IN TIE-BREAK
    }

    WinBall(Player_1);
    WinBall(Player_2);
    WinBall(Player_2);
    WinBall(Player_1);
    WinBall(Player_2);

    TEST_ASSERT_EQUAL(8, Score(Player_1)->points);
    TEST_ASSERT_EQUAL(9, Score(Player_2)->points);
    TEST_ASSERT_EQUAL(GEMS_TO_WIN, Score(Player_1)->gems);
    TEST_ASSERT_EQUAL(GEMS_TO_WIN, Score(Player_2)->gems);
    TEST_ASSERT_EQUAL(0, Score(Player_1)->sets);
    TEST_ASSERT_EQUAL(0, Score(Player_2)->sets);

    WinBall(Player_2);

    TEST_ASSERT_EQUAL(0, Score(Player_1)->points);
    TEST_ASSERT_EQUAL(0, Score(Player_2)->points);
    TEST_ASSERT_EQUAL(0, Score(Player_1)->gems);
    TEST_ASSERT_EQUAL(0, Score(Player_2)->gems);
    TEST_ASSERT_EQUAL(0, Score(Player_1)->sets);
    TEST_ASSERT_EQUAL(1, Score(Player_2)->sets);
}

void test_player_2_wins_the_game_when_enough_sets_won(void)
{
    for(uint8_t i = 0; i < SETS_TO_WIN; i++)
    {
        winSet(Player_2);
    }

    TEST_ASSERT_EQUAL(0, Score(Player_1)->points);
    TEST_ASSERT_EQUAL(0, Score(Player_2)->points);
    TEST_ASSERT_EQUAL(0, Score(Player_1)->gems);
    TEST_ASSERT_EQUAL(0, Score(Player_2)->gems);
    TEST_ASSERT_EQUAL(0, Score(Player_1)->sets);
    TEST_ASSERT_EQUAL(SETS_TO_WIN, Score(Player_2)->sets);

    TEST_ASSERT_EQUAL(Player_2, Winner());
}





