#include "unity.h"

#include "TicTacToe.h"

void setUp(void)
{
    ResetGame();
}

void tearDown(void)
{
}

void test_Tie(void)
{
    TEST_ASSERT_EQUAL(None, Game(0, 2));
    TEST_ASSERT_EQUAL(None, Game(0, 0));
    TEST_ASSERT_EQUAL(None, Game(1, 0));
    TEST_ASSERT_EQUAL(None, Game(0, 1));
    TEST_ASSERT_EQUAL(None, Game(1, 1));
    TEST_ASSERT_EQUAL(None, Game(1, 2));
    TEST_ASSERT_EQUAL(None, Game(2, 1));
    TEST_ASSERT_EQUAL(None, Game(2, 0));
    TEST_ASSERT_EQUAL(Tie, Game(2, 2));
}

void test_PlayerOne_win_1(void)
{
    TEST_ASSERT_EQUAL(None, Game(0, 1));
    TEST_ASSERT_EQUAL(None, Game(2, 0));
    TEST_ASSERT_EQUAL(None, Game(1, 1));
    TEST_ASSERT_EQUAL(None, Game(2, 2));
    TEST_ASSERT_EQUAL(PlayerOne, Game(2, 1));
}

void test_PlayerOne_win_2(void)
{
    TEST_ASSERT_EQUAL(None, Game(1, 0));
    TEST_ASSERT_EQUAL(None, Game(2, 0));
    TEST_ASSERT_EQUAL(None, Game(1, 1));
    TEST_ASSERT_EQUAL(None, Game(2, 2));
    TEST_ASSERT_EQUAL(PlayerOne, Game(1, 2));
}

void test_PlayerOne_win_3(void)
{
    TEST_ASSERT_EQUAL(None, Game(0, 0));
    TEST_ASSERT_EQUAL(None, Game(2, 0));
    TEST_ASSERT_EQUAL(None, Game(1, 1));
    TEST_ASSERT_EQUAL(None, Game(2, 1));
    TEST_ASSERT_EQUAL(PlayerOne, Game(2, 2));
}

void test_PlayerOne_win_4(void)
{
    TEST_ASSERT_EQUAL(None, Game(0, 2));
    TEST_ASSERT_EQUAL(None, Game(1, 0));
    TEST_ASSERT_EQUAL(None, Game(1, 1));
    TEST_ASSERT_EQUAL(None, Game(2, 1));
    TEST_ASSERT_EQUAL(PlayerOne, Game(2, 0));
}

void test_PlayerTwo_win_1(void)
{
    TEST_ASSERT_EQUAL(None, Game(0, 1));
    TEST_ASSERT_EQUAL(None, Game(0, 0));
    TEST_ASSERT_EQUAL(None, Game(1, 2));
    TEST_ASSERT_EQUAL(None, Game(1, 0));
    TEST_ASSERT_EQUAL(None, Game(1, 1));
    TEST_ASSERT_EQUAL(PlayerTwo, Game(2, 0));
}

void test_PlayerTwo_win_2(void)
{
    TEST_ASSERT_EQUAL(None, Game(1, 1));
    TEST_ASSERT_EQUAL(None, Game(2, 0));
    TEST_ASSERT_EQUAL(None, Game(1, 0));
    TEST_ASSERT_EQUAL(None, Game(2, 1));
    TEST_ASSERT_EQUAL(None, Game(0, 0));
    TEST_ASSERT_EQUAL(PlayerTwo, Game(2, 2));
}

void test_PlayerTwo_win_3(void)
{
    TEST_ASSERT_EQUAL(None, Game(1, 0));
    TEST_ASSERT_EQUAL(None, Game(0, 0));
    TEST_ASSERT_EQUAL(None, Game(2, 1));
    TEST_ASSERT_EQUAL(None, Game(1, 1));
    TEST_ASSERT_EQUAL(None, Game(0, 2));
    TEST_ASSERT_EQUAL(PlayerTwo, Game(2, 2));
}

void test_PlayerTwo_win_4(void)
{
    TEST_ASSERT_EQUAL(None, Game(2, 2));
    TEST_ASSERT_EQUAL(None, Game(0, 2));
    TEST_ASSERT_EQUAL(None, Game(1, 0));
    TEST_ASSERT_EQUAL(None, Game(1, 1));
    TEST_ASSERT_EQUAL(None, Game(2, 1));
    TEST_ASSERT_EQUAL(PlayerTwo, Game(2, 0));
}
