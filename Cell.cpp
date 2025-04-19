#include "Cell.h"

Cell::Cell() : hasShip(false), isHit(false) {}

void Cell::placeShip() {
    hasShip = true;
}

void Cell::markHit() {
    isHit = true;
}

bool Cell::wasHit() const {
    return isHit;
}

bool Cell::containsShip() const {
    return hasShip;
}

char Cell::display(bool revealShip) const {
    if (isHit) {
        return hasShip ? 'X' : 'O';
    } else {
        return (revealShip && hasShip) ? 'S' : '.';
    }
}
