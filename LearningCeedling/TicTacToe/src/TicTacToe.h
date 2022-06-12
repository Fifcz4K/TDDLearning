#ifndef TICTACTOE_H
#define TICTACTOE_H

#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

#define N 3
#define MAP_SIZE (N * N)

typedef enum
{
    PlayerOne,
    PlayerTwo,
    Tie,
    None
}Winner_t;

typedef enum
{
    Win_Case_1,
    Win_Case_2,
    Win_Case_3,
    Win_Case_4,
    Win_Cases
}WinCase_t;

void ResetGame(void);
Winner_t Game(uint8_t posX, uint8_t posY);

#endif // TICTACTOE_H
