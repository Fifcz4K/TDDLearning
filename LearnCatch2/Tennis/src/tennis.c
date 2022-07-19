#include "tennis.h"

static Score_t Score[NUMBER_OF_PLAYERS] = {0};
static Player_t playerGemAdvantage = None;
static bool gemAdvantage = false;
static bool tieBreak = false;
static Player_t Winner = None;

void TennisInit(void)
{
    playerGemAdvantage = None;
    gemAdvantage = false;
    tieBreak = false;
    Winner = None;

    for(uint8_t i = 0; i < NUMBER_OF_PLAYERS; i++)
    {
        Score[i].points = 0;
        Score[i].gems = 0;
        Score[i].sets = 0;
    }
}

static void managePoints(Player_t winner)
{
    Score[winner].points += 15;

    if(Score[winner].points == 45)
        Score[winner].points = 40;

    if(Score[winner].points == 40 && Score[1 - winner].points == 40)
    {
        gemAdvantage = true;
    }

    if(Score[winner].points == 55)
    {
        Score[Player_1].points = 0;
        Score[Player_2].points = 0;
        Score[winner].gems++;
    }            
}

static void manageGemAdvantage(Player_t winner)
{
    if(playerGemAdvantage == winner)
    {
        Score[winner].gems++;
        Score[Player_1].points = 0;
        Score[Player_2].points = 0;
        gemAdvantage = false;
        playerGemAdvantage = None;
    }
    else if(playerGemAdvantage == (1 - winner))
    {
        playerGemAdvantage = None;
    }
    else
    {
        playerGemAdvantage = winner;
    }
}

static void manageGems(Player_t winner)
{
    if(Score[Player_1].gems == 6 && Score[Player_2].gems == 6)
    {
        tieBreak = true;
    }
    else if(Score[winner].gems >= 6 && Score[winner].gems - Score[1 - winner].gems >= 2)
    {
        Score[Player_1].gems = 0;
        Score[Player_2].gems = 0;
        Score[winner].sets++;
    }
}

static void manageTieBreak(Player_t winner)
{
    Score[winner].points++;
    if(Score[winner].points >= 7 && Score[winner].points - Score[1 - winner].points >= 2)
    {
        Score[winner].sets++;
        Score[Player_1].points = 0;
        Score[Player_2].points = 0;
        Score[Player_1].gems = 0;
        Score[Player_2].gems = 0;
        tieBreak = false;
    }
}

static void manageSets(Player_t winner)
{
    if(Score[winner].sets == 2)
    {
        Winner = winner;
    }
}

void TennisWinBall(Player_t winner)
{
    if(tieBreak == false)
    {
        if(gemAdvantage == false)
        {
            managePoints(winner);
        }
        else
        {
            manageGemAdvantage(winner);
        }

        manageGems(winner);
    }
    else
    {
        manageTieBreak(winner);
    }

    manageSets(winner);
}

Score_t* TennisScore(Player_t player)
{
    return &Score[player];
}

Player_t TennisGetWinner(void)
{
    return Winner;
}