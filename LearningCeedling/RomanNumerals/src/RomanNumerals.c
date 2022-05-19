#include "RomanNumerals.h"

char RomanNumber[OUTPUT_ARRAY_SIZE] = "";

static RomanNumeralConverter_t convertArray[] =
{
    {1000, "M"},
    {900, "CM"},
    {500, "D"},
    {400, "CD"},
    {100, "C"},
    {90, "XC"},
    {50, "L"},
    {40, "XL"},
    {10, "X"},
    {9, "IX"},
    {5, "V"},
    {4, "IV"},
    {1, "I"}
};

static uint8_t convertArrayLen = sizeof(convertArray)/sizeof(convertArray[0]);

static void addAfterString(char *string, char *characterToAdd)
{
    sprintf(string, "%s%s", string, characterToAdd);
}

char* Convert(int number)
{
    sprintf(RomanNumber, "\0");

    for(uint8_t i = 0; i < convertArrayLen; i++)
    {
        while(number >= convertArray[i].number)
        {
            printf("number: %d --- number to add: %d\n", number, convertArray[i].number);
            addAfterString(RomanNumber, convertArray[i].letter);
            number -= convertArray[i].number;
        }
    }

    return RomanNumber;
}


