#include "Player.h"

Player::Player(const string &playerName) : name(playerName) {}

// Getters and Setters
string Player::getName() const { return name; }
Ship *Player::getShips() { return ships; }
bool Player::getOccupiedCell(int x, int y) const { return occupiedCells[y][x]; }
bool Player::getIsCellTargeted(int x, int y) const { return isCellTargeted[y][x]; }
int Player::getHits() const { return hits; }
int Player::getMisses() const { return misses; }
int Player::getScore() const { return score; }
bool Player::getTurnToAttack() const { return myTurnToAttack; }
bool (*Player::getOccupiedCells())[gridSize] { return occupiedCells; }
bool Player::getShowEffect(int x, int y) const { return showEffect[y][x]; }
const sf::Sprite &Player::getCellEffect(int x, int y) const { return cellEffects[y][x]; }

void Player::setIsCellTargeted(int x, int y, bool value) { isCellTargeted[y][x] = value; }
void Player::setShowEffect(int x, int y, bool value) { showEffect[y][x] = value; }
void Player::setTurnToAttack(bool turn) { myTurnToAttack = turn; }
void Player::setCellEffect(int x, int y, const sf::Texture &texture)
{
    cellEffects[y][x].setTexture(texture);
    cellEffects[y][x].setPosition(20 + x * cellSize, 20 + y * cellSize);
}

void Player::initializeShips(sf::Texture shipTextures[5])
{
    int shipLengths[numShips] = {5, 4, 4, 3, 3, 2};
    for (int i = 0; i < numShips; ++i)
    {
        float startX = 370.0f;
        float startY = 190.0f + i * (partSize + 10);
        ships[i].init(shipLengths[i], shipTextures, startX, startY);
    }
}

bool Player::allShipsPlaced() const
{
    for (int i = 0; i < numShips; ++i)
    {
        if (!ships[i].getIsPlaced())
            return false;
    }
    return true;
}

void Player::recordHit()
{
    hits++;
    score += 20;
}

void Player::recordMiss()
{
    misses++;
    score -= 5;
}

void Player::clearAllShipPositions()
{
    // Reset the entire occupied cells array using nested loops
    for (int y = 0; y < gridSize; y++)
    {
        for (int x = 0; x < gridSize; x++)
        {
            occupiedCells[y][x] = false;
        }
    }

    // Re-mark all properly placed ships
    for (int i = 0; i < numShips; i++)
    {
        if (ships[i].getIsPlaced() && ships[i].getGridPosition().x >= 0)
        {
            ships[i].markPosition(
                ships[i].getGridPosition().x,
                ships[i].getGridPosition().y,
                occupiedCells);
        }
    }
}

bool Player::validateShipPlacement(int excludeIndex)
{
    bool tempGrid[gridSize][gridSize] = {false};

    for (int i = 0; i < numShips; i++)
    {
        if (i == excludeIndex)
            continue;

        if (ships[i].getIsPlaced())
        {
            sf::Vector2i pos = ships[i].getGridPosition();
            if (!ships[i].canPlace(pos.x, pos.y, tempGrid))
            {
                return false;
            }
            ships[i].markPosition(pos.x, pos.y, tempGrid);
        }
    }
    return true;
}


void HumanPlayer::makeMove(Board& opponentBoard) {
    while (true) {
        int row, col;
        opponentBoard.displayShipStatus();
        opponentBoard.displayBoard();
        cout << "Your turn! Enter attack coordinates: ";
        cin >> row >> col;

        opponentBoard.attackCell(row, col);

        if (!opponentBoard.checkShip(row, col)) {
            break;
        }
    }
}

BotPlayer::BotPlayer() {
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            attackMemory[i][j] = false;
}

void BotPlayer::placeShips(Board& board) {
    int sizes[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        int row, col;
        bool horizontal;

        do {
            row = rand() % 10;
            col = rand() % 10;
            horizontal = rand() % 2;
        } while (!board.canPlaceShip(row, col, sizes[i], horizontal));

        board.placeShip(row, col, sizes[i], horizontal);
    }
}

void BotPlayer::makeMove(Board& opponentBoard) {
    while (true) {
        int row, col;
        opponentBoard.displayShipStatus();
        do {
            row = rand() % 10;
            col = rand() % 10;
        } while (attackMemory[row][col]);
        attackMemory[row][col] = true;

        cout << "Bot attacks (" << row << ", " << col << ")\n";
        opponentBoard.attackCell(row, col);
        opponentBoard.displayBoard();

        if (!opponentBoard.checkShip(row, col)) {
            break;
        }
    }
}
