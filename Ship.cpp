#include "Ship.h"

Ship::Ship() : size(0), hitsTaken(0), coordCount(0) {}

Ship::Ship(int s) : size(s), hitsTaken(0), coordCount(0) {}

void Ship::addCoordinate(int row, int col) {
    if (coordCount < 5) {
        coordinates[coordCount][0] = row;
        coordinates[coordCount][1] = col;
        coordCount++;
    }
}

bool Ship::occupiesCell(int row, int col) const {
    for (int i = 0; i < coordCount; i++) {
        if (coordinates[i][0] == row && coordinates[i][1] == col)
            return true;
    }
    return false;
}

void Ship::registerHit() {
    if (hitsTaken < size)
        hitsTaken++;
}

bool Ship::isSunk() const {
    return hitsTaken >= size;
}

int Ship::getSize() const {
    return size;
}
