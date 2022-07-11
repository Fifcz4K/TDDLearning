#include "Bowling.h"

static Player_t players[NUMBER_OF_PLAYERS] = {0};
static uint8_t player = 0;

void GameReset(void)
{
    player = 0;
    for(uint8_t i = 0; i < NUMBER_OF_PLAYERS; i++)
    {
        players[i].score = 0;
        players[i].lastRollPins = 0;
        players[i].rollNumber = 0;
        players[i].bonus = NoBonus;
        players[i].bonusRolls = 0;
    }
}

static uint8_t pinsCharToNum(char c)
{
    uint8_t pins = 0;
    
    if(c >= '0' && c <= '9')
    {
        pins = c - 48;
    }
    else if(c == '/')
    {
        pins = 10 - players[player].lastRollPins;
    }
    else if(c == 'X')
    {
        pins = 10;
    }

    return pins;
}

static void rememberFirstRollInTurn(uint8_t pins)
{
    if(players[player].rollNumber % 2 == 0)
    {
        players[player].lastRollPins = pins;
    }
    else
    {
        players[player].lastRollPins = 0;
    }
}

static void assignBonusRolls(char pins)
{
    if(players[player].rollNumber == LAST_REGULAR_ROLL)
    {
        if(pins == '/')
        {
            players[player].bonusRolls = 1;
        }
    }
    else if(players[player].rollNumber == LAST_REGULAR_ROLL - 1)
    {
        if(pins == 'X')
        {
            players[player].bonusRolls = 2;
        }
    }
}

static void assignPlayerAndRollNumber(char pins)
{
    if(pins == 'X')
    {
        players[player].rollNumber += 2;
    }
    else
    {
        players[player].rollNumber++;
    }

    if(players[player].bonusRolls > 0)
    {
        players[player].bonusRolls--;
    }
    else if(players[player].rollNumber > LAST_REGULAR_ROLL)
    {
        player++;
        if(player >= NUMBER_OF_PLAYERS)
        {
            player = 0;
        }
    }
    else
    {
        if(players[player].rollNumber % 2 == 0)
        {
            player++;
            if(player >= NUMBER_OF_PLAYERS)
            {
                player = 0;
            }
        }
    }
}

static void assignBonusState(char bonus)
{
    if(players[player].rollNumber < LAST_REGULAR_ROLL - 1)
    {
        if(bonus == '/')
        {
            if(players[player].bonus == NoBonus)
            {
                players[player].bonus = DoubleOneRound;
            }
            else
            {
                players[player].bonus = TripleOneRound;
            }
        }
        else if(bonus == 'X')
        {
            if(players[player].bonus == NoBonus)
            {
                players[player].bonus = DoubleTwoRound;
            }
            else
            {
                players[player].bonus = TripleOneRound;
            }
        }
    }
}

static void assignPointsForBonus(uint8_t pins)
{
    switch(players[player].bonus)
    {
        case TripleOneRound:
            players[player].score += (2 * pins);
            players[player].bonus = DoubleOneRound;
            break;

        case DoubleTwoRound:
            players[player].score += pins;
            players[player].bonus = DoubleOneRound;
            break;

        case DoubleOneRound:
            players[player].score += pins;
            players[player].bonus = NoBonus;
            break;

        default:
            break;
    }
}

void Roll(char rollOutput)
{
    uint8_t pins = pinsCharToNum(rollOutput);
    rememberFirstRollInTurn(pins);

    players[player].score += pins;

    assignPointsForBonus(pins);

    assignBonusState(rollOutput);

    assignBonusRolls(rollOutput);

    printf("player: %d, roll: %d, score: %d\n", player, players[player].rollNumber, players[player].score);

    assignPlayerAndRollNumber(rollOutput);
}

uint16_t Score(uint8_t player)
{
    return players[player].score;
}



