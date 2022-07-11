#include "unity.h"

#include "Tennis.h"

void setUp(void)
{
    GameReset();
}

void tearDown(void)
{
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














