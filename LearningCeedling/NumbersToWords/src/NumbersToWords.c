#include "NumbersToWords.h"

char OutputWord[OUTPUT_ARRAY_LENGTH] = "";

static NumberToWordConverter_t numberToWordArray[] =
{
    {90, "Ninety"},
    {80, "Eighty"},
    {70, "Seventy"},
    {60, "Sixty"},
    {50, "Fifty"},
    {40, "Forty"},
    {30, "Thirty"},
    {20, "Twenty"},
    {19, "Nineteen"},
    {18, "Eighteen"},
    {17, "Seventeen"},
    {16, "Sixteen"},
    {15, "Fiveteen"},
    {14, "Fourteen"},
    {13, "Thirteen"},
    {12, "Twelve"},
    {11, "Eleven"},
    {10, "Ten"},
    {9, "Nine"},
    {8, "Eight"},
    {7, "Seven"},
    {6, "Six"},
    {5, "Five"},
    {4, "Four"},
    {3, "Three"},
    {2, "Two"},
    {1, "One"},
};

static uint8_t numberToWordArrayLen = sizeof(numberToWordArray)/sizeof(numberToWordArray[0]);

static void addAfterString(char *outputWord, char *wordToAdd)
{
    if(strcmp(outputWord, "") == 0)
    {
        sprintf(outputWord, "%s%s", outputWord, wordToAdd);
    }
    else
    {
        sprintf(outputWord, "%s %s", outputWord, wordToAdd);
    }
}

char* ConvertNumberToWord(uint32_t number)
{
    uint8_t ThousandCounter = 0, HundredCounter = 0;
    memset(OutputWord, '\0', OUTPUT_ARRAY_LENGTH);

    if(number > 9999)
        return "Put in number from 0 to 9999!";

    if(number == 0)
        return "Zero";

    while(number > 0)
    {
        if(number >= 1000)
        {
            ThousandCounter = number / 1000;
            for(uint8_t i = 0; i < numberToWordArrayLen; i++)
            {
                if(ThousandCounter == numberToWordArray[i].number)
                {
                    addAfterString(OutputWord, numberToWordArray[i].word);
                    addAfterString(OutputWord, "Thousand");
                    number -= (numberToWordArray[i].number * 1000);
                    break;
                }
            }
        }
        else if(number >= 100)
        {
            HundredCounter = number / 100;
            for(uint8_t i = 0; i < numberToWordArrayLen; i++)
            {
                if(HundredCounter == numberToWordArray[i].number)
                {
                    addAfterString(OutputWord, numberToWordArray[i].word);
                    addAfterString(OutputWord, "Hundred");
                    number -= (numberToWordArray[i].number * 100);
                    break;
                }
            }
        }
        else
        {
            for(uint8_t i = 0; i < numberToWordArrayLen; i++)
            {
                if(number >= numberToWordArray[i].number)
                {
                    if(strcmp(OutputWord, "") != 0 && numberToWordArray[i].number % 10 == 0 && number % 10 == 0)
                    {
                        addAfterString(OutputWord, "And");
                    }
                    addAfterString(OutputWord, numberToWordArray[i].word);
                    number -= numberToWordArray[i].number;
                }
            }
        }
    }

    return OutputWord;
}