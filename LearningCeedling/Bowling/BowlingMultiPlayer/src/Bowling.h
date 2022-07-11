#ifndef BOWLING_H
#define BOWLING_H

#include "stdint.h"
#include "string.h"
#include "stdio.h"

#define NUMBER_OF_PLAYERS 2

#define MAX_ROLLS_IN_GAME 21
#define ROLLS_WITHOUT_BONUSES 20
#define LAST_REGULAR_ROLL 19
#define BONUS_ROLL 20

typedef enum
{
    NoBonus,
    DoubleOneRound,
    DoubleTwoRound,
    TripleOneRound
}BonusState_t;

typedef struct
{
    uint16_t score;
    uint8_t rollNumber;
    uint8_t lastRollPins;
    BonusState_t bonus;
}Player_t;

void GameReset(void);
void Roll(char rollOutput);
uint16_t Score(uint8_t player);


#endif // BOWLING_H
