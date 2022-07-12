#ifndef TENNIS_H
#define TENNIS_H

#include "stdint.h"
#include "stdbool.h"
#include "stdio.h"

#define NUMBER_OF_PLAYERS 2

typedef enum
{
    Player_1,
    Player_2,
    None
}Player_t;

typedef struct
{
    uint8_t points;
    uint8_t gems;
    uint8_t sets;
}Score_t;


void GameReset(void);
void WinBall(Player_t winner);
Score_t* Score(Player_t player);


#endif // TENNIS_H
