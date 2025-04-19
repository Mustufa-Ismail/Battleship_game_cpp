#ifndef CELL_H
#define CELL_H

class Cell {
private:
    bool hasShip;
    bool isHit;

public:
    Cell();
    void placeShip();
    void markHit();
    bool wasHit() const;
    bool containsShip() const;
    char display(bool revealShip = false) const;
};

#endif
