#include "unity.h"

#include "Bowling.h"

/*
    TEST ARE WRITTEN FOR 2 PLAYERS GAME
*/

void setUp(void)
{
    GameReset();
}

void tearDown(void)
{
}

static uint8_t pinsCharToNum(char c)
{
    static uint8_t pins = 0;
    
    if(c >= '0' && c <= '9')
    {
        pins = c - 48;
    }
    else if(c == '/')
    {
        pins = 10 - pins;
    }
    else if(c == 'X')
    {
        pins = 10;
    }
    else
    {
        pins = 0;
    }

    return pins;
}

static uint8_t PlayerTurn(char roll_1, char roll_2)
{
    uint8_t pins = 0;

    Roll(roll_1);
    Roll(roll_2);

    pins = pinsCharToNum(roll_1) + pinsCharToNum(roll_2);

    return pins;
}

static uint8_t Strike(void)
{
    Roll('X');

    return 10;
}

static void WholeTurn(char player_1_roll_1, 
                      char player_1_roll_2,
                      char player_2_roll_1,
                      char player_2_roll_2,
                      uint16_t *expected_1,
                      uint16_t *expected_2)
{
    if(player_1_roll_1 == 'X')
    {
        *expected_1 += Strike();
    }
    else
    {
        *expected_1 += PlayerTurn(player_1_roll_1, player_1_roll_2);
    }

    if(player_2_roll_1 == 'X')
    {
        *expected_2 += Strike();
    }
    else
    {
        *expected_2 += PlayerTurn(player_2_roll_1, player_2_roll_2);
    }
}

void test_score_after_2_rolls_each_player(void)
{
    uint16_t expected_player_1 = 0, expected_player_2 = 0;

    WholeTurn('2', '3', '1', '/', &expected_player_1, &expected_player_2);

    //Player 1
    TEST_ASSERT_EQUAL(expected_player_1, Score(0));
    //Player 2
    TEST_ASSERT_EQUAL(expected_player_2, Score(1));
}

void test_score_after_game_without_bonuses(void)
{
    uint16_t expected_player_1 = 0, expected_player_2 = 0;

    WholeTurn('2', '4', '1', '1', &expected_player_1, &expected_player_2);

    WholeTurn('3', '6', '1', '2', &expected_player_1, &expected_player_2);

    WholeTurn('7', '0', '0', '9', &expected_player_1, &expected_player_2);

    WholeTurn('1', '1', '1', '1', &expected_player_1, &expected_player_2);

    WholeTurn('0', '9', '0', '0', &expected_player_1, &expected_player_2);

    WholeTurn('4', '5', '5', '4', &expected_player_1, &expected_player_2);

    WholeTurn('0', '1', '2', '3', &expected_player_1, &expected_player_2);

    WholeTurn('5', '3', '2', '7', &expected_player_1, &expected_player_2);

    WholeTurn('0', '0', '0', '0', &expected_player_1, &expected_player_2);

    WholeTurn('9', '0', '9', '0', &expected_player_1, &expected_player_2);

    //Player 1
    TEST_ASSERT_EQUAL(expected_player_1, Score(0));
    //Player 2
    TEST_ASSERT_EQUAL(expected_player_2, Score(1));
}

void test_spare(void)
{
    uint16_t expected_player_1 = 0, expected_player_2 = 0;

    WholeTurn('1', '/', '8', '/', &expected_player_1, &expected_player_2);

    WholeTurn('5', '2', '9', '0', &expected_player_1, &expected_player_2);

    //SPARE BONUS
    expected_player_1 += 5;
    expected_player_2 += 9;

    //Player 1
    TEST_ASSERT_EQUAL(expected_player_1, Score(0));
    //Player 2
    TEST_ASSERT_EQUAL(expected_player_2, Score(1));
}

void test_2_spares_in_a_row(void)
{
    uint16_t expected_player_1 = 0, expected_player_2 = 0;

    WholeTurn('1', '/', '8', '/', &expected_player_1, &expected_player_2);

    WholeTurn('5', '/', '9', '/', &expected_player_1, &expected_player_2);

    WholeTurn('1', '2', '3', '4', &expected_player_1, &expected_player_2);

    //SPARE BONUS
    expected_player_1 += 5 + 1;
    expected_player_2 += 9 + 3;

    //Player 1
    TEST_ASSERT_EQUAL(expected_player_1, Score(0));
    //Player 2
    TEST_ASSERT_EQUAL(expected_player_2, Score(1));
}

void test_strike(void)
{
    uint16_t expected_player_1 = 0, expected_player_2 = 0;

    WholeTurn('X', '0', '2', '4', &expected_player_1, &expected_player_2);

    WholeTurn('5', '2', '9', '0', &expected_player_1, &expected_player_2);

    //SPARE BONUS
    expected_player_1 += 5 + 2;

    //Player 1
    TEST_ASSERT_EQUAL(expected_player_1, Score(0));
    //Player 2
    TEST_ASSERT_EQUAL(expected_player_2, Score(1));
}

void test_2_strikes_in_a_row(void)
{
    uint16_t expected_player_1 = 0, expected_player_2 = 0;

    WholeTurn('X', '0', 'X', '0', &expected_player_1, &expected_player_2);

    WholeTurn('5', '2', 'X', '0', &expected_player_1, &expected_player_2);

    WholeTurn('7', '1', '2', '6', &expected_player_1, &expected_player_2);

    //SPARE BONUS
    expected_player_1 += 5 + 2;
    expected_player_2 += 10 + 2 + 2 + 6;

    //Player 1
    TEST_ASSERT_EQUAL(expected_player_1, Score(0));
    //Player 2
    TEST_ASSERT_EQUAL(expected_player_2, Score(1));
}

void test_spare_last_round(void)
{
    uint16_t expected_player_1 = 0, expected_player_2 = 0;

    for(uint8_t i = 0; i < 9; i++)
    {
        WholeTurn('0', '0', '0', '0', &expected_player_1, &expected_player_2);
    }

    expected_player_1 += PlayerTurn('5', '/');
    //Player 1 bonus roll for spare
    Roll('4');

    expected_player_2 += PlayerTurn('9', '/');
    //Player 2 bonus roll for spare
    Roll('8');

    //SPARE BONUS
    expected_player_1 += 4;
    expected_player_2 += 8;

    //Player 1
    TEST_ASSERT_EQUAL(expected_player_1, Score(0));
    //Player 2
    TEST_ASSERT_EQUAL(expected_player_2, Score(1));
}

void test_strike_last_round(void)
{
    uint16_t expected_player_1 = 0, expected_player_2 = 0;

    for(uint8_t i = 0; i < 9; i++)
    {
        WholeTurn('0', '0', '0', '0', &expected_player_1, &expected_player_2);
    }

    Roll('X');
    expected_player_1 += 10;
    //Player 1 bonus roll for strike
    expected_player_1 += PlayerTurn('7', '2');

    expected_player_2 += PlayerTurn('5', '2');

    //Player 1
    TEST_ASSERT_EQUAL(expected_player_1, Score(0));
    //Player 2
    TEST_ASSERT_EQUAL(expected_player_2, Score(1));
}

void test_only_9_spare_game(void)
{
    uint16_t expected_player_1 = 0, expected_player_2 = 0;

    for(uint8_t i = 0; i < 9; i++)
    {
        WholeTurn('9', '/', '9', '/', &expected_player_1, &expected_player_2);
    }

    expected_player_1 += PlayerTurn('9', '/');
    //Player 1 bonus rolls for strike
    Roll('9');

    expected_player_2 += PlayerTurn('9', '/');
    //Player 2 bonus rolls for strike
    Roll('9');

    //Player 1
    TEST_ASSERT_EQUAL(190, Score(0));
    //Player 2
    TEST_ASSERT_EQUAL(190, Score(1));
}

void test_perfect_game(void)
{
    uint16_t expected_player_1 = 0, expected_player_2 = 0;

    for(uint8_t i = 0; i < 10; i++)
    {
        WholeTurn('X', '0', 'X', '0', &expected_player_1, &expected_player_2);
    }

    //Player 1 bonus rolls for strike
    Roll('X');
    Roll('X');
    //Player 2 bonus rolls for strike
    Roll('X');
    Roll('X');

    //Player 1
    TEST_ASSERT_EQUAL(300, Score(0));
    //Player 2
    TEST_ASSERT_EQUAL(300, Score(1));
}

void test_random_game(void)
{
    uint16_t expected_player_1 = 0, expected_player_2 = 0;

    WholeTurn('5', '/', '7', '/', &expected_player_1, &expected_player_2); 
    WholeTurn('4', '0', 'X', '0', &expected_player_1, &expected_player_2);
    WholeTurn('8', '1', 'X', '0', &expected_player_1, &expected_player_2);
    WholeTurn('X', '0', '8', '1', &expected_player_1, &expected_player_2);
    WholeTurn('0', '/', '9', '/', &expected_player_1, &expected_player_2);
    WholeTurn('X', '0', '8', '1', &expected_player_1, &expected_player_2);
    WholeTurn('X', '0', 'X', '0', &expected_player_1, &expected_player_2);
    WholeTurn('X', '0', '9', '/', &expected_player_1, &expected_player_2);
    WholeTurn('4', '/', '8', '/', &expected_player_1, &expected_player_2);


    Roll('X');
    //Player 1 bonus rolls for strike
    Roll('X');
    Roll('5');


    PlayerTurn('6', '1');

    //Player 1
    TEST_ASSERT_EQUAL(186, Score(0));
    //Player 2
    TEST_ASSERT_EQUAL(164, Score(1));
}