#include "Tennis.h"

Score_t score[NUMBER_OF_PLAYERS] = {0};
static Player_t advantage = None;
static bool deuce = false;

void GameReset(void)
{
    advantage = None;
    deuce = false;

    for(uint8_t i = 0; i < NUMBER_OF_PLAYERS; i++)
    {
        score[i].points = 0;
        score[i].gems = 0;
        score[i].sets = 0;
    }
    printf("\n\nRESET\n\n");
}

static void manageGems(Player_t winner)
{
    if(score[winner].gems == 6)
    {
        score[Player_1].gems = 0;
        score[Player_2].gems = 0;
        score[winner].sets++;
    }
}

static void managePoints(Player_t winner)
{
    if(deuce == false)
    {
        score[winner].points += 15;
        if(score[winner].points == 45)
        {
            score[winner].points = 40;
        }

        if(score[Player_1].points == 40 && score[Player_2].points == 40)
        {
            deuce = true;
        }
    }

    if(score[winner].points == 55)
    {
        score[Player_1].points = 0;
        score[Player_2].points = 0;
        score[winner].gems++;
    }
}

static void manageDeuce(Player_t winner)
{
    if(deuce == true)
    {
        if(advantage == None)
        {
            advantage = winner;
        }
        else if(advantage == winner)
        {
            score[winner].points = 55;
        }
        else
        {
            advantage = None;
        }
    }
}

static void printStatus(void)
{
    printf("Player 1: P-%d, G-%d, S-%d\n", score[Player_1].points, score[Player_1].gems, score[Player_1].sets);
    printf("Player 2: P-%d, G-%d, S-%d\n", score[Player_2].points, score[Player_2].gems, score[Player_2].sets);
    printf("deuce: %d, advantage: %d\n\n", deuce, advantage);
}

void WinBall(Player_t winner)
{
    manageDeuce(winner);
    managePoints(winner);
    // printStatus();
    manageGems(winner);
}

Score_t* Score(Player_t player)
{
    return &score[player];
}