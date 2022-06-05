#ifndef ROMANNUMERALS_H
#define ROMANNUMERALS_H

#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

#define OUTPUT_ARRAY_SIZE 20

typedef struct
{
    uint16_t number;
    char *letter;
}ArabicToRomanConverter_t;

typedef struct
{
    uint16_t number;
    char letter;
}RomanToArabicConverter_t;


char* ConvertArabicToRoman(uint16_t number);
int16_t ConvertRomanToArabic(char* input);

#endif // ROMANNUMERALS_H
