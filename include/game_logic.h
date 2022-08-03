#ifndef GAME_LOGIC_H_INCLUDE
#define GAME_LOGIC_H_INCLUDE

class GameLogic
{
public:
    bool getGameOver();
    void setGameOver();
    int getPlayer();
    void changePlayer(int playerSet);
    void ballSunk(int ballNumber);

private:
    bool gameOver = false;
    bool ballsInPlay[15] = {true};
    int currentPlayer = 1, playerWinner = 0;
};
#endif
