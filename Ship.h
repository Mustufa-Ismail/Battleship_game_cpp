#ifndef SHIP_H
#define SHIP_H

#include <SFML/Graphics.hpp>
using namespace std;
const int partSize = 30;
const int maxShipLength = 5;
const int gridSize = 10;
const int cellSize = 30;
const int numShips = 6;

class Ship {
    private:
    int length;
    sf::Sprite parts[maxShipLength];
    int gridX, gridY;
    bool isVertical;
    bool isPlaced;

    public:
    void init(int len, sf::Texture shipTextures[5], float startX, float startY);
    void draw(sf::RenderWindow &window);
    void rotate(sf::Texture shipTextures[5]);
    bool canPlace(int gridX, int gridY, bool occupiedCells[gridSize][gridSize]);
    void markPosition(int gridX, int gridY, bool occupiedCells[gridSize][gridSize]);
    void clearPosition(int gridX, int gridY, bool occupiedCells[gridSize][gridSize]);
    void setPosition(float x, float y);
    void setGridPosition(int x, int y);
    sf::Vector2i getGridPosition() const;
    bool getIsPlaced() const;
    void setIsPlaced(bool placed);
    bool getIsVertical() const;
    int getLength() const;
    sf::FloatRect getBounds() const;
    sf::FloatRect getPartBounds(int index) const;

};

#endif
