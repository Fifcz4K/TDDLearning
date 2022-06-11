#ifndef NUMBERSTOWORDS_H
#define NUMBERSTOWORDS_H

#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

#define OUTPUT_ARRAY_LENGTH 100

typedef struct
{
    uint32_t number;
    char* word;
}NumberToWordConverter_t;


char* ConvertNumberToWord(uint32_t number);

#endif // NUMBERSTOWORDS_H
