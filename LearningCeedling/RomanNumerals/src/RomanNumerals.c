#include "RomanNumerals.h"

static char RomanNumber[OUTPUT_ARRAY_SIZE] = "";
static int16_t ArabicNumber = 0;

static ArabicToRomanConverter_t convertArabicToRomanArray[] =
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

static RomanToArabicConverter_t convertRomanToArabicArray[] =
{
    {1000, 'M'},
    {500, 'D'},
    {100, 'C'},
    {50, 'L'},
    {10, 'X'},
    {5, 'V'},
    {1, 'I'}
};

static ArabicToRomanConverter_t RomanToArabicSpecialCaseArray[] =
{
    {200, "CM"},
    {200, "CD"},
    {20, "XC"},
    {20, "XL"},
    {2, "IX"},
    {2, "IV"},
};

static uint8_t convertArabicToRomanArrayLen = sizeof(convertArabicToRomanArray)/sizeof(convertArabicToRomanArray[0]);
static uint8_t convertRomanToArabicArrayLen = sizeof(convertRomanToArabicArray)/sizeof(convertRomanToArabicArray[0]);
static uint8_t romanToArabicSpecialCasesArrayLen = sizeof(RomanToArabicSpecialCaseArray)/sizeof(RomanToArabicSpecialCaseArray[0]);

static void addAfterString(char *string, char *characterToAdd)
{
    sprintf(string, "%s%s", string, characterToAdd);
}

char* ConvertArabicToRoman(uint16_t number)
{
    sprintf(RomanNumber, "\0");

    for(uint8_t i = 0; i < convertArabicToRomanArrayLen; i++)
    {
        while(number >= convertArabicToRomanArray[i].number)
        {
            addAfterString(RomanNumber, convertArabicToRomanArray[i].letter);
            number -= convertArabicToRomanArray[i].number;
        }
    }

    return RomanNumber;
}

static void subIfNeeded(char* input, uint16_t *returnValue, char* subStr, uint16_t valueToSub)
{
    if(strstr(input, subStr) != NULL)
    {
        *returnValue -= valueToSub;
    }
}

int16_t ConvertRomanToArabic(char* input)
{
    ArabicNumber = 0;
    char temp;

    for(uint8_t i = 0; i < romanToArabicSpecialCasesArrayLen; i++)
    {
        subIfNeeded(input, &ArabicNumber, RomanToArabicSpecialCaseArray[i].letter, RomanToArabicSpecialCaseArray[i].number);
    }

    while(*input != '\0')
    {
        memcpy(&temp, input, 1);
        for(uint8_t i = 0; i < convertRomanToArabicArrayLen; i++)
        {
            if(convertRomanToArabicArray[i].letter == temp)
            {
                ArabicNumber += convertRomanToArabicArray[i].number;
                input++;
            }
        }
    }

    return ArabicNumber;
}

