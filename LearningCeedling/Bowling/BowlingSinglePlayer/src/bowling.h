#ifndef BOWLING_H
#define BOWLING_H

#include "stdint.h"
#include "string.h"
#include "stdio.h"

#define MAX_ROLLS_IN_GAME 21
#define ROLLS_WITHOUT_BONUSES 20
#define LAST_REGULAR_ROLL 19
#define BONUS_ROLL 20

void GameReset(void);
void Roll(uint8_t pins);
uint16_t Score(void);

#endif // BOWLING_H
