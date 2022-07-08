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
    rollNumber++;
}

uint16_t Score(void)
{
    uint16_t score = 0;
    for(uint8_t i = 0; i < MAX_ROLLS_IN_GAME; i++)
    {
        score += rollsArray[i];
    }

    return score;
}