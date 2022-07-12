#include "Tennis.h"

Score_t score[NUMBER_OF_PLAYERS] = {0};
static Player_t advantage = None;
static bool deuce = false;
static bool tieBreak = false;
static Player_t gameWinner = None;

void GameReset(void)
{
    advantage = None;
    deuce = false;
    tieBreak = false;
    gameWinner = None;

    for(uint8_t i = 0; i < NUMBER_OF_PLAYERS; i++)
    {
        score[i].points = 0;
        score[i].gems = 0;
        score[i].sets = 0;
    }
}

static void manageSets(Player_t winner)
{
    if(score[winner].sets == SETS_TO_WIN)
    {
        gameWinner = winner;
    }
}

static void manageTieBreak(Player_t winner)
{
    if(tieBreak == true)
    {
        score[winner].points++;

        if(score[winner].points >= POINTS_TO_WIN_TIE_BREAK)
        {
            if(score[winner].points - score[1 - winner].points >= ADVANTAGE_IN_TIE_BREAK)
            {
                score[Player_1].points = 0;
                score[Player_2].points = 0;
                score[Player_1].gems = 0;
                score[Player_2].gems = 0;
                score[winner].sets++;
                tieBreak = false;            
            }
        }
    }
}

static void manageGems(Player_t winner)
{
    if(tieBreak == false)
    {
        if(score[winner].gems >= GEMS_TO_WIN)
        {
            if(score[1 - winner].gems >= GEMS_TO_WIN)
            {
                tieBreak = true;
            }
            else if(score[winner].gems - score[1 - winner].gems >= GEMS_ADVANTAGE)
            {
                score[Player_1].gems = 0;
                score[Player_2].gems = 0;
                score[winner].sets++;
            }
        }
    }
}

static void managePoints(Player_t winner)
{
    if(tieBreak == false)
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
            deuce = false;
            score[winner].gems++;
        }
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

void WinBall(Player_t winner)
{
    manageDeuce(winner);
    managePoints(winner);
    manageTieBreak(winner);
    manageGems(winner);
    manageSets(winner);
}

Score_t* Score(Player_t player)
{
    return &score[player];
}

Player_t Winner(void)
{
    return gameWinner;
}