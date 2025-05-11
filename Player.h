#ifndef PLAYER_H
#define PLAYER_H

#include "Ship.h"

class Player
{
private:
    std::string name;
    Ship ships[numShips];
    bool occupiedCells[gridSize][gridSize] = {false};
    bool isCellTargeted[gridSize][gridSize] = {false};
    bool showEffect[gridSize][gridSize] = {false};
    sf::Sprite cellEffects[gridSize][gridSize];
    int hits = 0;
    int misses = 0;
    int score = 0;
    bool myTurnToAttack = false;

public:
    Player(const std::string &playerName);
    std::string getName() const;
    Ship *getShips();
    bool getOccupiedCell(int x, int y) const;
    bool getIsCellTargeted(int x, int y) const;
    int getHits() const;
    int getMisses() const;
    int getScore() const;
    bool getTurnToAttack() const;
    bool (*getOccupiedCells())[gridSize];
    bool getShowEffect(int x, int y) const;
    const sf::Sprite &getCellEffect(int x, int y) const;
    void setIsCellTargeted(int x, int y, bool value);
    void setShowEffect(int x, int y, bool value);
    void setTurnToAttack(bool turn);
    void setCellEffect(int x, int y, const sf::Texture &texture);
    void initializeShips(sf::Texture shipTextures[5]);
    bool allShipsPlaced() const;
    void recordHit();
    void recordMiss();
    void clearAllShipPositions();
    bool validateShipPlacement(int excludeIndex = -1);

};

#endif
