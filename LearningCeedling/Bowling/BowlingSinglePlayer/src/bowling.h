#ifndef BOWLING_H
#define BOWLING_H

#include "stdint.h"
#include "string.h"

#define MAX_ROLLS_IN_GAME 22
#define ROLLS_WITHOUT_BONUSES 20

void GameReset(void);
void Roll(uint8_t pins);
uint16_t Score(void);

#endif // BOWLING_H
