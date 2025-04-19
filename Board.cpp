#include "Board.h"

Board::Board() {
    shipCount = 0;
}

bool Board::checkShip(int row, int col) {
    return grid[row][col].containsShip();
}

bool Board::canPlaceShip(int startRow, int startCol, int size, bool horizontal) {
    if (horizontal) {
        if (startCol + size > 10) return false;
        for (int i = 0; i < size; i++) {
            if (grid[startRow][startCol + i].containsShip()) return false;
        }
    } else {
        if (startRow + size > 10) return false;
        for (int i = 0; i < size; i++) {
            if (grid[startRow + i][startCol].containsShip()) return false;
        }
    }
    return true;
}

void Board::placeShip(int startRow, int startCol, int size, bool horizontal) {
    if (shipCount >= 5) return;
    if (!canPlaceShip(startRow, startCol, size, horizontal)) return;

    Ship newShip(size);

    if (horizontal) {
        for (int i = 0; i < size; i++) {
            grid[startRow][startCol + i].placeShip();
            newShip.addCoordinate(startRow, startCol + i);
        }
    } else {
        for (int i = 0; i < size; i++) {
            grid[startRow + i][startCol].placeShip();
            newShip.addCoordinate(startRow + i, startCol);
        }
    }

    ships[shipCount] = newShip;
    shipCount++;
}

void Board::attackCell(int row, int col) {
    grid[row][col].markHit();

    for (int i = 0; i < shipCount; i++) {
        if (ships[i].occupiesCell(row, col)) {
            ships[i].registerHit();
            break;
        }
    }
}

bool Board::hasLost() const {
    for (int i = 0; i < shipCount; i++) {
        if (!ships[i].isSunk()) return false;
    }
    return true;
}

void Board::displayBoard(bool reveal) const {
    for (int i = 0; i < 10; i++) {
        cout << "|";
        for (int j = 0; j < 10; j++) {
            cout << grid[i][j].display(reveal) << "|";
        }
        cout << endl;
    }
}

bool Board::allShipsSunk() {
    for (int i = 0; i < shipCount; ++i) {
        if (!ships[i].isSunk()) {
            return false;
        }
    }
    return true;
}

void Board::displayShipStatus() {
    for (int i = 0; i < shipCount; i++) {
        if (ships[i].isSunk()) {
            cout << "Ship " << i + 1 << " destroyed!\n";
        } else {
            cout << "Ship " << i + 1 << " remaining!\n";
        }
    }
}
