#include "bowling.h"

static uint8_t rollsArray[MAX_ROLLS_IN_GAME] = {0};
static uint8_t rollNumber = 0;

void GameReset(void)
{
    memset(rollsArray, 0, MAX_ROLLS_IN_GAME);
    rollNumber = 0;
}

void Roll(uint8_t pins)
{
    rollsArray[rollNumber] = pins;
    
    if(rollNumber % 2 == 0 && pins == 10)
    {
        rollNumber += 2;
    }
    else
    {
        rollNumber++;
    }
}

uint16_t Score(void)
{
    uint16_t score = 0;
    for(uint8_t i = 0; i < ROLLS_WITHOUT_BONUSES; i++)
    {
        score += rollsArray[i];
        if(i % 2 == 0)
        {
            if(rollsArray[i] + rollsArray[i + 1] == 10)
            {
                score += rollsArray[i + 2];
            }
        }
    }


    return score;
}