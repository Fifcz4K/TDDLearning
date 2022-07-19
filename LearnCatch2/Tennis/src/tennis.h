#ifndef TENNIS_H
#define TENNIS_H

#include "stdint.h"
#include "stdio.h"
#include "stdbool.h"

#define NUMBER_OF_PLAYERS 2

typedef enum
{
    Player_1,
    Player_2,
    None
}Player_t;

typedef struct
{
    uint16_t points;
    uint8_t gems;
    uint8_t sets;
}Score_t;

void TennisInit(void);
void TennisWinBall(Player_t winner);
Score_t* TennisScore(Player_t player);
Player_t TennisGetWinner(void);

#endif //TENNIS_H