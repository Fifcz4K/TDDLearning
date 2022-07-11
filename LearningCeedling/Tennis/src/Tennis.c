#include "Tennis.h"

Score_t score[NUMBER_OF_PLAYERS] = {0};

void GameReset(void)
{
    for(uint8_t i = 0; i < NUMBER_OF_PLAYERS; i++)
    {
        score[i].points = 0;
        score[i].gems = 0;
        score[i].sets = 0;
    }
}

void WinBall(Player_t winner)
{
    score[winner].points += 15;

    if(score[winner].points == 45)
        score[winner].points = 40;
}

Score_t* Score(Player_t player)
{
    return &score[player];
}