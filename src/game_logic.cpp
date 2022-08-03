#include "game_logic.h"
#include <iostream>

bool GameLogic::getGameOver()
{
        return gameOver;
}

void GameLogic::setGameOver()
{
    if(gameOver)
    {
        gameOver = false;

    }
    else
    {
        gameOver = true;
    }
}


int GameLogic::getPlayer()
{
    return currentPlayer;
}

void GameLogic::changePlayer(int playerSet)
{
    currentPlayer = playerSet;
}

void GameLogic::ballSunk(int ballNumber)
{
    switch (ballNumber)
    {
        case 15:
            ballsInPlay[14] = false;
            break;
        case 14:
            ballsInPlay[13] = false;
            break;
        case 13:
            ballsInPlay[12] = false;
            break;
        case 12:
            ballsInPlay[11] = false;
            break;
        case 11:
            ballsInPlay[10] = false;
            break;
        case 10:
            ballsInPlay[9] = false;
            break;
        case 9:
            ballsInPlay[8] = false;
            break;
        case 8:
            break;
        case 7:
            ballsInPlay[6] = false;
            break;
        case 6:
            ballsInPlay[5] = false;
            break;
        case 5:
            ballsInPlay[4] = false;
            break;
        case 4:
            ballsInPlay[3] = false;
            break;
        case 3:
            ballsInPlay[2] = false;
            break;
        case 2:
            ballsInPlay[1] = false;
            break;
        case 1:
            ballsInPlay[0] = false;
            break;
        default:
            std::cout << "Ball Sunk Error" << std::endl;
    }
}
