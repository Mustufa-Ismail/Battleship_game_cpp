#include <SFML/Graphics.hpp>
#include <iostream>

const int partSize = 30;
const int maxShipLength = 5;
const int gridSize = 10;
const int cellSize = 30;
const int numShips = 6;

class Ship {
public:
    int length;
    sf::Sprite parts[maxShipLength];

    void init(int len, sf::Texture shipTextures[5], float startX, float startY) {
        length = len;
        for (int i = 0; i < length; ++i) {
            if (i == 0)
                parts[i].setTexture(shipTextures[0]); // head
            else if (i == length - 1)
                parts[i].setTexture(shipTextures[4]); // tail
            else
                parts[i].setTexture(shipTextures[(i - 1) % 3 + 1]); // mid parts cycle 1-3

            parts[i].setPosition(startX + i * partSize, startY);
        }
    }

    void draw(sf::RenderWindow& window) {
        for (int i = 0; i < length; ++i)
            window.draw(parts[i]);
    }
};
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Battleship UI", sf::Style::Close | sf::Style::Titlebar);
    bool isPlacementScreen = true;

    // Set icon
    sf::Image icon;
    if (icon.loadFromFile("assets/icon.jpg"))
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Background
    sf::Texture gridBgTexture;
    if (!gridBgTexture.loadFromFile("assets/bg.jpg")) return -1;
    sf::Sprite gridBgSprite(gridBgTexture);
    gridBgSprite.setPosition(20, 20);
    gridBgSprite.setScale(0.6f, 0.6f);

    // Font
    sf::Font font;
    if (!font.loadFromFile("assets/arial.ttf")) return -1;

    // Ship textures
    sf::Texture shipTextures[5];
    for (int i = 0; i < 5; ++i) {
        std::string filename = "assets/ship" + std::to_string(i) + ".png";
        if (!shipTextures[i].loadFromFile(filename)) return -1;
    }

    // Ships
    int shipLengths[numShips] = {5, 4, 4, 3, 3, 2};
    Ship ships[numShips];
    for (int i = 0; i < numShips; ++i) {
        float startX = 370.0f;
        float startY = 190.0f + i * (partSize + 10);
        ships[i].init(shipLengths[i], shipTextures, startX, startY);
    }

    // Grid
    sf::RectangleShape grid[gridSize][gridSize];
    for (int i = 0; i < gridSize; ++i)
        for (int j = 0; j < gridSize; ++j) {
            grid[i][j].setSize(sf::Vector2f(cellSize, cellSize));
            grid[i][j].setOutlineThickness(1);
            grid[i][j].setOutlineColor(sf::Color::White);
            grid[i][j].setFillColor(sf::Color(255, 255, 255, 0));
            grid[i][j].setPosition(j * cellSize + 20, i * cellSize + 20);
        }

    // Instruction container
    sf::RectangleShape container1;
    container1.setSize(sf::Vector2f(400, 130));
    container1.setPosition(350, 20);
    container1.setOutlineThickness(2);
    container1.setFillColor(sf::Color::Black);

    sf::Text insHead;
    insHead.setStyle(sf::Text::Bold);
    insHead.setFont(font);
    insHead.setString("Place Your Ships:\n");
    insHead.setCharacterSize(17);
    insHead.setFillColor(sf::Color::White);
    insHead.setPosition(container1.getPosition().x + 10, container1.getPosition().y + 10);

    sf::Text insText;
    insText.setFont(font);
    insText.setString("\n\n- Click on a ship from the sidebar to pick it up.\n- Click on your grid to place the ship.\n- Press R to rotate the ship (horizontal/vertical).\nRule: Ships cannot overlap or go outside the grid.");
    insText.setCharacterSize(17);
    insText.setFillColor(sf::Color::White);
    insText.setPosition(insHead.getPosition().x, insHead.getPosition().y - 10);

    sf::RectangleShape container2;
    container2.setSize(sf::Vector2f(400, 270));
    container2.setOutlineThickness(2);
    container2.setOutlineColor(sf::Color::Black);
    container2.setPosition(350, 170);
    container2.setFillColor(sf::Color::Black);

    // NEXT BUTTON
    sf::RectangleShape nextButton;
    nextButton.setSize(sf::Vector2f(120, 40));
    nextButton.setFillColor(sf::Color(70, 130, 180));
    nextButton.setPosition(320, 530);

    sf::Text nextText;
    nextText.setFont(font);
    nextText.setCharacterSize(20);
    nextText.setFillColor(sf::Color::White);
    nextText.setString("Next");
    nextText.setPosition(nextButton.getPosition().x + 35, nextButton.getPosition().y + 5);

    // Targeting screen elements
    sf::RectangleShape scoreContainer;
    scoreContainer.setSize(sf::Vector2f(200, 130));
    scoreContainer.setFillColor(sf::Color::Black);
    scoreContainer.setOutlineThickness(2);
    scoreContainer.setPosition(350, 20);

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Scores:\nPlayer 1: 0\nPlayer 2: 0");
    scoreText.setCharacterSize(17);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(scoreContainer.getPosition().x + 10, scoreContainer.getPosition().y + 10);

    sf::RectangleShape instructionsContainer;
    instructionsContainer.setSize(sf::Vector2f(400, 130));
    instructionsContainer.setFillColor(sf::Color::Black);
    instructionsContainer.setOutlineThickness(2);
    instructionsContainer.setPosition(350, 170);

    sf::Text attackInstructions;
    attackInstructions.setFont(font);
    attackInstructions.setString("Targeting Phase:\n- Click on the opponent's grid to attack.\n- You get feedback on hit or miss.");
    attackInstructions.setCharacterSize(17);
    attackInstructions.setFillColor(sf::Color::White);
    attackInstructions.setPosition(instructionsContainer.getPosition().x + 10, instructionsContainer.getPosition().y + 10);

    int hits = 0;
    int misses = 0;
    int score = 0;

    // Text labels
    sf::Text hitText, missText, scoreValueText;

    // Set common properties
    hitText.setFont(font);
    missText.setFont(font);
    scoreValueText.setFont(font);

    hitText.setCharacterSize(17);
    missText.setCharacterSize(17);
    scoreValueText.setCharacterSize(17);

    hitText.setFillColor(sf::Color::White);
    missText.setFillColor(sf::Color::White);
    scoreValueText.setFillColor(sf::Color::White);

    // Set positions inside the scoreContainer
    hitText.setPosition(scoreContainer.getPosition().x + 10, scoreContainer.getPosition().y + 10);
    missText.setPosition(scoreContainer.getPosition().x + 10, scoreContainer.getPosition().y + 40);
    scoreValueText.setPosition(scoreContainer.getPosition().x + 10, scoreContainer.getPosition().y + 70);

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::H) hits++;
                if (event.key.code == sf::Keyboard::M) misses++;
                if (event.key.code == sf::Keyboard::S) score += 10;
            }
                    
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (nextButton.getGlobalBounds().contains(mousePos)) {
                    isPlacementScreen = !isPlacementScreen;
                }
            }
        }

        hitText.setString("Hits: " + std::to_string(hits));
        missText.setString("Misses: " + std::to_string(misses));
        scoreValueText.setString("Score: " + std::to_string(score));

    
        // Update button text depending on screen
        nextText.setString(isPlacementScreen ? "Next" : "Back");
    
        window.clear(sf::Color::White);
        window.draw(gridBgSprite);
    
        // Draw grid
        for (int i = 0; i < gridSize; ++i)
            for (int j = 0; j < gridSize; ++j)
                window.draw(grid[i][j]);
    
        if (isPlacementScreen) {
            window.draw(container1);
            window.draw(container2);
            window.draw(insHead);
            window.draw(insText);
            for (int i = 0; i < numShips; ++i)
                ships[i].draw(window);
        } else {
            window.draw(scoreContainer);
            window.draw(scoreText);
            window.draw(instructionsContainer);
            window.draw(attackInstructions);
            window.draw(scoreContainer);
            window.draw(hitText);
            window.draw(missText);
            window.draw(scoreValueText);
        }
    
        // Draw toggle button on both screens
        window.draw(nextButton);
        window.draw(nextText);
    
        window.display();
    }
    

    return 0;
}
