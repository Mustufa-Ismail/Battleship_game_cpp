#ifndef SHIP_H
#define SHIP_H

class Ship {
private:
    int size;
    int hitsTaken;
    int coordinates[5][2];
    int coordCount;

public:
    Ship();
    Ship(int s);
    void addCoordinate(int row, int col);
    bool occupiesCell(int row, int col) const;
    void registerHit();
    bool isSunk() const;
    int getSize() const;
};

#endif
