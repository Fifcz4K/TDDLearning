#include "Doors100.h"

static char DoorsStates[MAX_NUMBER_OF_DOORS] = "";

char* GetDoorsState(uint16_t NumberOfDoors)
{
    uint16_t indexToChange = 0;

    if(NumberOfDoors > MAX_NUMBER_OF_DOORS || NumberOfDoors < 1)
        return "Incorrect number of doors!";

    memset(DoorsStates, '\0', MAX_NUMBER_OF_DOORS);
    memset(DoorsStates, '#', NumberOfDoors);

    for(uint16_t i = 1; i <= NumberOfDoors; i++)
    {
        indexToChange = 0;
        while(indexToChange < NumberOfDoors)
        {
            if((i == 1) || ((indexToChange + 1) % i == 0))
            {
                if(DoorsStates[indexToChange] == '#')
                {
                    DoorsStates[indexToChange] = '@';
                }
                else
                {
                    DoorsStates[indexToChange] = '#';
                }
            }

            indexToChange++;
        }
    }

    return DoorsStates;
}