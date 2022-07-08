#include "bowling.h"

static uint8_t rollsArray[MAX_ROLLS_IN_GAME] = {0};
static uint8_t rollNumber = 0;
static uint16_t score = 0;

void GameReset(void)
{
    memset(rollsArray, 0, MAX_ROLLS_IN_GAME);
    rollNumber = 0;
    score = 0;
}

void Roll(uint8_t pins)
{
    rollsArray[rollNumber] = pins;
    rollNumber++;
}

static void AddSpareBonuses(uint8_t index)
{
    if(index % 2 == 0)
    {
        if(rollsArray[index] + rollsArray[index + 1] == 10 && rollsArray[index] != 10)
        {
            score += rollsArray[index + 2];
        }
    }
}

uint16_t Score(void)
{
    for(uint8_t i = 0; i < ROLLS_WITHOUT_BONUSES; i++)
    {
        score += rollsArray[i];

        AddSpareBonuses(i);

        if(i % 2 == 0)
        {
            if(rollsArray[i] == 10)
            {
                score += rollsArray[i + 2];
                if(rollsArray[i + 2] == 10)
                {
                    score += rollsArray[i + 4];
                }
                else
                {
                    score += rollsArray[i + 3];
                }
            }
        }
    }


    return score;
}