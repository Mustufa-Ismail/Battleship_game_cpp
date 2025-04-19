#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"

class Player {
public:
    virtual void placeShips(Board& board) = 0;
    virtual void makeMove(Board& opponentBoard) = 0;
};

class HumanPlayer : public Player {
public:
    void placeShips(Board& board) override;
    void makeMove(Board& opponentBoard) override;
};

class BotPlayer : public Player {
private:
    bool attackMemory[10][10];

public:
    BotPlayer();
    void placeShips(Board& board) override;
    void makeMove(Board& opponentBoard) override;
};

#endif
