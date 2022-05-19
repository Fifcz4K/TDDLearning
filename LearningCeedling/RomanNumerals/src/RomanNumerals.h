#ifndef ROMANNUMERALS_H
#define ROMANNUMERALS_H

#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define OUTPUT_ARRAY_SIZE 20

typedef struct
{
    int number;
    char *letter;
}RomanNumeralConverter_t;

char* Convert(int number);

#endif // ROMANNUMERALS_H
