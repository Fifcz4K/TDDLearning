#include "TicTacToe.h"

static Winner_t TicTacToeMap[N][N];
static uint32_t MoveCounter;

void ResetGame(void)
{
    MoveCounter = 0;
    
    for(uint8_t i = 0; i < N; i++)
    {
        for(uint8_t j = 0; j < N; j++)
        {
            TicTacToeMap[i][j] = None;
        }
    }
}

static Winner_t CheckWinner(void)
{
    uint32_t playerOne[Win_Cases] = {0}, playerTwo[Win_Cases] = {0};

    for(uint8_t i = 0; i < N; i++)
    {
        if(TicTacToeMap[i][i] == PlayerOne)
            playerOne[Win_Case_1]++;
        if(TicTacToeMap[i][i] == PlayerTwo)
            playerTwo[Win_Case_1]++;
        if(TicTacToeMap[i][N - 1 - i] == PlayerOne)
            playerOne[Win_Case_2]++;
        if(TicTacToeMap[i][N - 1 - i] == PlayerTwo)
            playerTwo[Win_Case_2]++;

        if(playerOne[Win_Case_1] == N || playerOne[Win_Case_2] == N)
            return PlayerOne;

        if(playerTwo[Win_Case_1] == N || playerTwo[Win_Case_2] == N)
            return PlayerTwo;

        for(uint8_t j = 0; j < N; j++)
        {
            if(TicTacToeMap[j][i] == PlayerOne)
                playerOne[Win_Case_3]++;
            if(TicTacToeMap[j][i] == PlayerTwo)
                playerTwo[Win_Case_3]++;

            if(TicTacToeMap[i][j] == PlayerOne)
                playerOne[Win_Case_4]++;
            if(TicTacToeMap[i][j] == PlayerTwo)
                playerTwo[Win_Case_4]++;

            if(playerOne[Win_Case_3] == N || playerOne[Win_Case_4] == N)
                return PlayerOne;

            if(playerTwo[Win_Case_3] == N || playerTwo[Win_Case_4] == N)
                return PlayerTwo;
        }

        playerOne[Win_Case_3] = 0;
        playerTwo[Win_Case_3] = 0;
        playerOne[Win_Case_4] = 0;
        playerTwo[Win_Case_4] = 0;
    }

    return None;
}

Winner_t Game(uint8_t posX, uint8_t posY)
{
    Winner_t signToAdd;
    Winner_t result = None;

    if(MoveCounter % 2 == 0)
        signToAdd = PlayerOne;
    else
        signToAdd = PlayerTwo;

    if(posX >= N || posY >= N)
        return None;

    if(TicTacToeMap[posX][posY] != None)
        return None;

    TicTacToeMap[posX][posY] = signToAdd;

    MoveCounter++;
    
    result = CheckWinner();

    if(result == None && MoveCounter >= MAP_SIZE)
        result = Tie;

    return result;
}