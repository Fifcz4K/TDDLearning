#include "../../catch2.hpp"

extern "C"
{
    #include "../src/tennis.h"
}

static void WinGem(Player_t player)
{
    for(uint8_t i = 0; i < 4; i++)
    {
        TennisWinBall(player);
    }
}

static void WinSet(Player_t player)
{
    for(uint8_t i = 0; i < 6; i++)
    {
        WinGem(player);
    }
}

TEST_CASE("Score is 0 after init")
{
    TennisInit();
    REQUIRE(TennisScore(Player_1)->points == 0);
    REQUIRE(TennisScore(Player_1)->gems == 0);
    REQUIRE(TennisScore(Player_1)->sets == 0);
    REQUIRE(TennisScore(Player_2)->points == 0);
    REQUIRE(TennisScore(Player_2)->gems == 0);
    REQUIRE(TennisScore(Player_2)->sets == 0);
}

SCENARIO("Players scoring points")
{
    GIVEN("Beggining of the game - Both players without points")
    {
        TennisInit();

        WHEN("Player 1 wins a ball")
        {
            TennisWinBall(Player_1);

            THEN("Player 1 has 15 points, Player 2 - 0 points")
            {
                REQUIRE(TennisScore(Player_1)->points == 15);
                REQUIRE(TennisScore(Player_2)->points == 0);
            }
        }

        WHEN("Player 2 wins a ball 2 times, Player 1 wins a ball once")
        {
            TennisWinBall(Player_2);
            TennisWinBall(Player_2);
            TennisWinBall(Player_1);

            THEN("Player 2 has 30 points, Player 1 - 15 points")
            {
                REQUIRE(TennisScore(Player_1)->points == 15);
                REQUIRE(TennisScore(Player_2)->points == 30);
            }
        }

        WHEN("Player 1 wins a ball 3 times")
        {
            TennisWinBall(Player_1);
            TennisWinBall(Player_1);
            TennisWinBall(Player_1);

            THEN("Player 1 has 40 points, Player 2 - 0 points")
            {
                REQUIRE(TennisScore(Player_1)->points == 40);
                REQUIRE(TennisScore(Player_2)->points == 0);
            }
        }

        WHEN("Player 2 wins gem after winning 4 balls")
        {
            WinGem(Player_2);

            THEN("Player 2 has 1 gem and 0 points")
            {
                REQUIRE(TennisScore(Player_2)->points == 0);
                REQUIRE(TennisScore(Player_2)->gems == 1);
            }
        }
    }
}

SCENARIO("Gem advantage")
{
    GIVEN("Both players has 40 points")
    {
        TennisInit();
        for(uint8_t i = 0; i < 3; i++)
        {
            TennisWinBall(Player_1);
            TennisWinBall(Player_2);
        }

        WHEN("Player 1 wins a ball")
        {
            TennisWinBall(Player_1);

            THEN("Player 1 has advantage but gem is not yet achieved")
            {
                REQUIRE(TennisScore(Player_1)->points == 40);
                REQUIRE(TennisScore(Player_2)->points == 40);
                REQUIRE(TennisScore(Player_1)->gems == 0);
                REQUIRE(TennisScore(Player_2)->gems == 0);
            }
        }

        WHEN("Player 1 wins a ball twice")
        {
            TennisWinBall(Player_1);
            TennisWinBall(Player_1);

            THEN("Player 1 wins gem")
            {
                REQUIRE(TennisScore(Player_1)->points == 0);
                REQUIRE(TennisScore(Player_2)->points == 0);
                REQUIRE(TennisScore(Player_1)->gems == 1);
                REQUIRE(TennisScore(Player_2)->gems == 0);
            }
        }

        WHEN("Player 1 wins, Player 2 wins and noone wins advantage")
        {
            for(uint8_t i = 0; i < 100; i++)
            {
                TennisWinBall(Player_1);
                TennisWinBall(Player_2);
            }

            THEN("Noone achieved gem yet")
            {
                REQUIRE(TennisScore(Player_1)->points == 40);
                REQUIRE(TennisScore(Player_2)->points == 40);
                REQUIRE(TennisScore(Player_1)->gems == 0);
                REQUIRE(TennisScore(Player_2)->gems == 0);
            }

            WHEN("Player 2 finnaly wins advantage")
            {
                TennisWinBall(Player_2);
                TennisWinBall(Player_2);

                THEN("Player 2 wins gem")
                {
                    REQUIRE(TennisScore(Player_1)->points == 0);
                    REQUIRE(TennisScore(Player_2)->points == 0);
                    REQUIRE(TennisScore(Player_1)->gems == 0);
                    REQUIRE(TennisScore(Player_2)->gems == 1);
                }
            }
        }
    }
}

SCENARIO("Winning Set")
{
    GIVEN("Both players has 4 gems")
    {
        TennisInit();
        for(uint8_t i = 0; i < 4; i++)
        {
            WinGem(Player_1);
            WinGem(Player_2);
        }

        WHEN("Player 1 wins 2 more gems")
        {
            WinGem(Player_1);
            WinGem(Player_1);

            THEN("Player 1 wins set")
            {
                REQUIRE(TennisScore(Player_1)->points == 0);
                REQUIRE(TennisScore(Player_2)->points == 0);
                REQUIRE(TennisScore(Player_1)->gems == 0);
                REQUIRE(TennisScore(Player_2)->gems == 0);
                REQUIRE(TennisScore(Player_1)->sets == 1);
                REQUIRE(TennisScore(Player_2)->sets == 0);
            }
        }

        WHEN("Player 1 wins 1 gem, Player 2 wins 2 gems")
        {
            WinGem(Player_1);
            WinGem(Player_2);
            WinGem(Player_2);

            THEN("Noone wins set - 2 gems advantage is needed")
            {
                REQUIRE(TennisScore(Player_1)->points == 0);
                REQUIRE(TennisScore(Player_2)->points == 0);
                REQUIRE(TennisScore(Player_1)->gems == 5);
                REQUIRE(TennisScore(Player_2)->gems == 6);
                REQUIRE(TennisScore(Player_1)->sets == 0);
                REQUIRE(TennisScore(Player_2)->sets == 0);
            }

            WHEN("Player 2 wins one more gem")
            {
                WinGem(Player_2);

                THEN("Player 2 wins set")
                {
                    REQUIRE(TennisScore(Player_1)->points == 0);
                    REQUIRE(TennisScore(Player_2)->points == 0);
                    REQUIRE(TennisScore(Player_1)->gems == 0);
                    REQUIRE(TennisScore(Player_2)->gems == 0);
                    REQUIRE(TennisScore(Player_1)->sets == 0);
                    REQUIRE(TennisScore(Player_2)->sets == 1);
                }
            }
        }
    }
}

SCENARIO("Tie-Break")
{
    GIVEN("Both players has 6 gems - Tie-Break starts")
    {
        TennisInit();
        for(uint8_t i = 0; i < 6; i++)
        {
            WinGem(Player_1);
            WinGem(Player_2);
        }

        WHEN("Player 1 wins 7 balls")
        {
            for(uint8_t i = 0; i < 7; i++)
            {
                TennisWinBall(Player_1);
            }

            THEN("Player 1 wins a set")
            {
                REQUIRE(TennisScore(Player_1)->points == 0);
                REQUIRE(TennisScore(Player_2)->points == 0);
                REQUIRE(TennisScore(Player_1)->gems == 0);
                REQUIRE(TennisScore(Player_2)->gems == 0);
                REQUIRE(TennisScore(Player_1)->sets == 1);
                REQUIRE(TennisScore(Player_2)->sets == 0);
            }
        }

        WHEN("Both players scoring - Player 1 wins, Player 2 wins etc...")
        {
            for(uint8_t i = 0; i < 100; i++)
            {
                TennisWinBall(Player_1);
                TennisWinBall(Player_2);
            }

            THEN("Tie-Break keeps going, noone achieved set yet")
            {
                REQUIRE(TennisScore(Player_1)->points == 100);
                REQUIRE(TennisScore(Player_2)->points == 100);
                REQUIRE(TennisScore(Player_1)->gems == 6);
                REQUIRE(TennisScore(Player_2)->gems == 6);
                REQUIRE(TennisScore(Player_1)->sets == 0);
                REQUIRE(TennisScore(Player_2)->sets == 0);
            }

            WHEN("Player 2 wins 2 points in a row")
            {
                TennisWinBall(Player_2);
                TennisWinBall(Player_2);

                THEN("Player 2 wins a set")
                {
                    REQUIRE(TennisScore(Player_1)->points == 0);
                    REQUIRE(TennisScore(Player_2)->points == 0);
                    REQUIRE(TennisScore(Player_1)->gems == 0);
                    REQUIRE(TennisScore(Player_2)->gems == 0);
                    REQUIRE(TennisScore(Player_1)->sets == 0);
                    REQUIRE(TennisScore(Player_2)->sets == 1);
                }
            }
        }
    }
}

SCENARIO("Winning game")
{
    GIVEN("Game starts")
    {
        TennisInit();

        WHEN("Player 1 gets 2 sets")
        {
            WinSet(Player_1);
            WinSet(Player_1);

            THEN("Player 1 wins the game")
            {
                REQUIRE(TennisGetWinner() == Player_1);
            }
        }
    }
}




