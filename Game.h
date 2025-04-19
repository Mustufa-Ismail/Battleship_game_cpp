#ifndef GAME_H
#define GAME_H

#include "Player.h"

class Game {
private:
    Player* p1;
    Player* p2;
    Board board1;
    Board board2;

public:
    Game(Player* player1, Player* player2);
    void start();
};

#endif
