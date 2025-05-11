#ifndef GAME_H
#define GAME_H

#include "Player.h"
using namespace std;

enum GameState
{
    MENU,
    GAME,
    FINAL
};

class Game
{
private:
    GameState currentState = MENU;
    sf::Texture logoTexture;
    sf::Sprite logoSprite;

    sf::Text creditsHead;
    sf::Text creditsBody;

    sf::RectangleShape startButton;
    sf::RectangleShape exitButton;
    sf::Text startText;
    sf::Text exitText;
    sf::RectangleShape menuButton;
    sf::RectangleShape finalExitButton;
    sf::Text menuText;
    sf::Text finalExitText;

    sf::RectangleShape transitionBox;
    sf::Text transitionText;
    sf::FloatRect textBounds;
    sf::RectangleShape continueButton;
    sf::Text continueText;
    sf::FloatRect continueBounds;

    sf::RectangleShape playerCards[2];
    sf::Text playerNames[2];
    sf::Text hitsTexts[2], missesTexts[2], scoreTexts[2];
    sf::Texture crownTexture;
    sf::Sprite crownSprites[2];

    sf::RenderWindow window;
    sf::Texture shipTextures[5];
    sf::Texture hitTexture, missTexture, gridBgTexture;
    sf::Image icon;
    sf::Font fontA, fontB, fontC;
    sf::RectangleShape grid[gridSize][gridSize];
    sf::Sprite gridBgSprite;

    Player player1;
    Player player2;
    Player *currentPlayer;
    Player *opponent;

    bool isDragging = false;
    int selectedShipIndex = -1;
    sf::Vector2f dragOffset;
    bool shipPlaced[numShips] = {false};
    bool showInvalidMessage = false;
    bool isPlacementPhase = true;
    sf::Clock invalidMessageClock;
    bool targetPhaseComplete = false;

    // UI Elements
    sf::RectangleShape container1, container2;
    sf::RectangleShape scoreContainer, instructionsContainer;
    sf::Text insHead, insText;
    sf::Text scoreText, attackInstructions;
    sf::Text hitText, missText, scoreValueText;
    sf::Text invalidText;
    sf::Text currentPlayerText;

    sf::Clock transitionClock;
    bool isTransitioning = false;
    sf::Vector2f smoothShipPosition;
    sf::Vector2f targetGridPosition;
    const float lerpFactor = 0.2f;

    void setupGame();
    bool loadTextures();
    void setupUI();
    void setText();
    void resetGame();
    void handleEvents();
    void rotateShip();
    void switchToPlayer2Attack();
    void startTransition(const std::string &message);
    void checkAllShipsPlaced();
    void handleMouseClick();
    void handleShipDragging();
    void handleShipDrop();
    void update();
    void render();
    void drawPlacementUI();
    void drawTargetingUI();
    void setupScoreCards(int player1Misses, int player2Misses);
    

public:
    Game();
    void run();
};

#endif
