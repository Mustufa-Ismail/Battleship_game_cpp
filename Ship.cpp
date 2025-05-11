#include "Ship.h"

    void Ship::init(int len, sf::Texture shipTextures[5], float startX, float startY)
    {
        length = len;
        gridX = -1;
        gridY = -1;
        isVertical = false;
        isPlaced = false;

        for (int i = 0; i < length; ++i)
        {
            if (i == 0)
                parts[i].setTexture(shipTextures[0]);
            else if (i == length - 1)
                parts[i].setTexture(shipTextures[4]);
            else
                parts[i].setTexture(shipTextures[(i - 1) % 3 + 1]);
            parts[i].setPosition(startX + i * partSize, startY);
        }
    }

    void Ship::draw(sf::RenderWindow &window)
    {
        for (int i = 0; i < length; ++i)
            window.draw(parts[i]);
    }

    void Ship::rotate(sf::Texture shipTextures[5])
    {
        // Store the heads position to keep it fixed during rotation
        sf::Vector2f headPos = parts[0].getPosition();

        for (int i = 0; i < length; ++i)
        {
            // Assign textures
            if (i == 0)
                parts[i].setTexture(shipTextures[0]);
            else if (i == length - 1)
                parts[i].setTexture(shipTextures[4]);
            else
                parts[i].setTexture(shipTextures[(i - 1) % 3 + 1]);

            if (!isVertical)
            {
                // For horizontal to vertical
                parts[i].setRotation(90);
                parts[i].setOrigin(0, parts[i].getLocalBounds().height);
                parts[i].setPosition(headPos.x, headPos.y + i * partSize);
            }
            else
            {
                // for vertical to horizontal
                parts[i].setRotation(0);
                parts[i].setOrigin(0, 0);
                parts[i].setPosition(headPos.x + i * partSize, headPos.y);
            }
        }

        isVertical = !isVertical; // Flip the state
    }

    bool Ship::canPlace(int gridX, int gridY, bool occupiedCells[gridSize][gridSize])
    {
        if (gridX < 0 || gridY < 0)
            return false;

        if (isVertical)
        {
            if (gridY + length > gridSize)
                return false;
            for (int i = 0; i < length; ++i)
            {
                if (occupiedCells[gridY + i][gridX])
                    return false;
            }
        }
        else
        {
            if (gridX + length > gridSize)
                return false;
            for (int i = 0; i < length; ++i)
            {
                if (occupiedCells[gridY][gridX + i])
                    return false;
            }
        }
        return true;
    }

    void Ship::markPosition(int gridX, int gridY, bool occupiedCells[gridSize][gridSize])
    {
        if (isVertical)
        {
            for (int i = 0; i < length; ++i)
            {
                occupiedCells[gridY + i][gridX] = true;
            }
        }
        else
        {
            for (int i = 0; i < length; ++i)
            {
                occupiedCells[gridY][gridX + i] = true;
            }
        }
    }

    void Ship::clearPosition(int gridX, int gridY, bool occupiedCells[gridSize][gridSize])
    {
        if (gridX < 0 || gridY < 0)
            return;

        if (isVertical)
        {
            for (int i = 0; i < length && (gridY + i) < gridSize; ++i)
            {
                occupiedCells[gridY + i][gridX] = false;
            }
        }
        else
        {
            for (int i = 0; i < length && (gridX + i) < gridSize; ++i)
            {
                occupiedCells[gridY][gridX + i] = false;
            }
        }
    }

    void Ship::setPosition(float x, float y)
    {
        for (int i = 0; i < length; ++i)
        {
            if (isVertical)
            {
                parts[i].setPosition(x, y + i * partSize);
            }
            else
            {
                parts[i].setPosition(x + i * partSize, y);
            }
        }
    }

    void Ship::setGridPosition(int x, int y)
    {
        gridX = x;
        gridY = y;
    }
    sf::Vector2i Ship::getGridPosition() const
    {
        return sf::Vector2i(gridX, gridY);
    }

    // getter and setters
    bool Ship::getIsPlaced() const { return isPlaced; }
    void Ship::setIsPlaced(bool placed) { isPlaced = placed; }
    bool Ship::getIsVertical() const { return isVertical; }
    int Ship::getLength() const { return length; }
    sf::FloatRect Ship::getBounds() const { return parts[0].getGlobalBounds(); }

    sf::FloatRect Ship::getPartBounds(int index) const
    {
        if (index >= 0 && index < length)
        {
            return parts[index].getGlobalBounds();
        }
        return sf::FloatRect(); // Return an empty rectangle if index is invalid
    }


}

int Ship::getSize() const {
    return size;
}
