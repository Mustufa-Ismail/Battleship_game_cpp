#ifndef BOARD_H
#define BOARD_H

#include "Cell.h"
#include "Ship.h"
#include <iostream>
using namespace std;

class Board {
private:
    Cell grid[10][10];
    Ship ships[5];
    int shipCount;

public:
    Board();
    bool checkShip(int row, int col);
    bool canPlaceShip(int startRow, int startCol, int size, bool horizontal);
    void placeShip(int startRow, int startCol, int size, bool horizontal);
    void attackCell(int row, int col);
    bool hasLost() const;
    void displayBoard(bool reveal = false) const;
    bool allShipsSunk();
    void displayShipStatus();
};

#endif
