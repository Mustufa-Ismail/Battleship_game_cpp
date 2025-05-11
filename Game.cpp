#include "Game.h"

Game::Game() : window(sf::VideoMode(800, 600), "Battleship OOP"),
               player1("Player 1"),
               player2("Player 2")
{
    currentPlayer = &player1;
    opponent = &player2;
    setupGame();
}

void Game::run()
{
    while (window.isOpen())
    {
        setText();
        handleEvents();
        update();
        render();
    }
}

void Game::setupGame()
{
    if (!loadTextures())
    {
        window.close();
        return;
    }

    gridBgSprite.setTexture(gridBgTexture);
    gridBgSprite.setPosition(20, 20);
    gridBgSprite.setScale(0.6f, 0.6f);

    // Initialize ships for both players
    player1.initializeShips(shipTextures);
    player2.initializeShips(shipTextures);

    // Initialize grid
    for (int i = 0; i < gridSize; ++i)
    {
        for (int j = 0; j < gridSize; ++j)
        {
            grid[i][j].setSize(sf::Vector2f(cellSize, cellSize));
            grid[i][j].setOutlineThickness(1);
            grid[i][j].setOutlineColor(sf::Color(210, 225, 246));
            grid[i][j].setFillColor(sf::Color(255, 255, 255, 0));
            grid[i][j].setPosition(j * cellSize + 20, i * cellSize + 20);
        }
    }

    setupUI();
}

bool Game::loadTextures()
{
    if (!gridBgTexture.loadFromFile("assets/bg.jpg"))
        return false;
    if (!hitTexture.loadFromFile("assets/hit.gif") || !missTexture.loadFromFile("assets/miss.gif"))
        return false;
    if (!logoTexture.loadFromFile("assets/logo.png"))
        return false;
    if (icon.loadFromFile("assets/icon.jpg"))
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    if (!fontA.loadFromFile("assets/torso.ttf") || !fontB.loadFromFile("assets/torso-reg.otf") || !fontC.loadFromFile("assets/torso-semi.otf"))
        return false;

    for (int i = 0; i < 5; ++i)
    {
        string filename = "assets/ship" + to_string(i) + ".png";
        if (!shipTextures[i].loadFromFile(filename))
            return false;
    }
    return true;
}

void Game::setupUI()
{
    logoSprite.setTexture(logoTexture);
    logoSprite.setPosition(205, 80);
    logoSprite.setScale(0.5f, 0.5f);

    creditsHead.setString("< CREDITS >");
    creditsHead.setFont(fontA);
    creditsHead.setCharacterSize(28);
    creditsHead.setFillColor(sf::Color::Black);
    creditsHead.setPosition(290.5, 380);

    creditsBody.setString("     Ali Asghar\n Mustufa Ismail\nHasheem Shuja");
    creditsBody.setFont(fontC);
    creditsBody.setCharacterSize(24);
    creditsBody.setFillColor(sf::Color::Black);
    creditsBody.setPosition(290, 425);

    // Start Button
    startButton.setSize({205, 45});
    startButton.setPosition(297.5, 255);
    startButton.setFillColor(sf::Color::Transparent);
    startButton.setOutlineThickness(1);
    startButton.setOutlineColor(sf::Color::Black);
    startText.setFont(fontA);
    startText.setString("< START >");
    startText.setCharacterSize(28);
    startText.setFillColor(sf::Color::Black);
    startText.setPosition(306, 259);

    // Exit Button (Menu screen)
    exitButton.setSize({205, 45});
    exitButton.setPosition(297.5, 300);
    exitButton.setFillColor(sf::Color::Transparent);
    exitButton.setOutlineThickness(1);
    exitButton.setOutlineColor(sf::Color::Black);
    exitText.setFont(fontA);
    exitText.setString("< EXIT >");
    exitText.setCharacterSize(28);
    exitText.setFillColor(sf::Color::Black);
    exitText.setPosition(328, 305);

    // Menu Button (Final screen)
    menuButton.setSize({205, 45});
    menuButton.setPosition(297.5, 355);
    menuButton.setFillColor(sf::Color::Transparent);
    menuText.setFont(fontA);
    menuText.setString("< MENU >");
    menuButton.setOutlineThickness(1);
    menuButton.setOutlineColor(sf::Color::Black);
    menuText.setCharacterSize(28);
    menuText.setFillColor(sf::Color::Black);
    menuText.setPosition(316, 359);

    // Final Exit Button
    finalExitButton.setSize({205, 45});
    finalExitButton.setPosition(297.5, 400);
    finalExitButton.setFillColor(sf::Color::Transparent);
    finalExitButton.setOutlineThickness(1);
    finalExitButton.setOutlineColor(sf::Color::Black);
    finalExitText.setFont(fontA);
    finalExitText.setString("< EXIT >");
    finalExitText.setCharacterSize(28);
    finalExitText.setFillColor(sf::Color::Black);
    finalExitText.setPosition(328, 405);

    transitionText.setString("Player 2's Turn");
    transitionText.setFillColor(sf::Color::White);
    transitionText.setFont(fontC);
    transitionText.setCharacterSize(30);

    continueButton.setSize(sf::Vector2f(150, 40));
    continueButton.setFillColor(sf::Color(100, 100, 255));
    continueButton.setPosition(800 / 2.0f - 75, 600 / 2.0f + 40);

    continueText.setString("Continue");
    continueText.setFont(fontC);
    continueText.setCharacterSize(20);
    continueText.setFillColor(sf::Color::White);

    container1.setPosition(347, 20);
    container1.setOutlineThickness(2);
    container1.setFillColor(sf::Color::Black);
    container1.setSize(sf::Vector2f(404.5, 150));

    insHead.setStyle(sf::Text::Bold);
    insHead.setFont(fontB);
    insHead.setString("Place Your Ships:\n");
    insHead.setCharacterSize(15);
    insHead.setFillColor(sf::Color::White);
    insHead.setPosition(container1.getPosition().x + 10, container1.getPosition().y + 10);

    insText.setFont(fontB);
    insText.setString("\n\n- Click on a ship from the sidebar to pick it up.\n- Click on your grid to place the ship.\n- Press R to rotate the ship (horizontal/vertical).\nRule: Ships cannot overlap or go outside the grid.\n When all the ships are places PRESS ENTER");
    insText.setCharacterSize(17);
    insText.setFillColor(sf::Color::White);
    insText.setPosition(insHead.getPosition().x, insHead.getPosition().y - 15);

    container2.setOutlineThickness(2);
    container2.setOutlineColor(sf::Color::Black);
    container2.setPosition(350, 170);
    container2.setFillColor(sf::Color::Black);
    container2.setSize(sf::Vector2f(400, 270));

    scoreContainer.setFillColor(sf::Color::Black);
    scoreContainer.setOutlineThickness(2);
    scoreContainer.setPosition(350, 20);
    scoreContainer.setSize(sf::Vector2f(200, 130));

    instructionsContainer.setFillColor(sf::Color::Black);
    instructionsContainer.setOutlineThickness(2);
    instructionsContainer.setPosition(350, 170);
    instructionsContainer.setSize(sf::Vector2f(400, 160));

    attackInstructions.setFont(fontB);
    attackInstructions.setString("Targeting Phase:\n- Click on the opponent's grid to attack.\n- Hit = +20 points \n- Miss = -5 points\n- Turn automatically switches after all ships are\nrevealed (i.e at 21 hits).");
    attackInstructions.setCharacterSize(17);
    attackInstructions.setFillColor(sf::Color::White);
    attackInstructions.setPosition(instructionsContainer.getPosition().x + 10, instructionsContainer.getPosition().y + 10);

    invalidText.setFont(fontB);
    invalidText.setString("Invalid position!");
    invalidText.setCharacterSize(18);
    invalidText.setFillColor(sf::Color::Red);
    invalidText.setPosition(20, 320);
}

void Game::setText()
{
    // Set fonts and basic properties
    hitText.setFont(fontB);
    missText.setFont(fontB);
    scoreValueText.setFont(fontB);

    hitText.setCharacterSize(17);
    missText.setCharacterSize(17);
    scoreValueText.setCharacterSize(17);

    hitText.setFillColor(sf::Color::White);
    missText.setFillColor(sf::Color::White);
    scoreValueText.setFillColor(sf::Color::White);

    hitText.setString("Hits: " + to_string(currentPlayer->getHits()));
    missText.setString("Misses: " + to_string(currentPlayer->getMisses()));
    scoreValueText.setString("Score: " + to_string(currentPlayer->getScore()));

    // Calculate positions relative to container
    const float padding = 10.f;
    const sf::Vector2f containerPos = scoreContainer.getPosition();

    hitText.setPosition(containerPos.x + padding, containerPos.y + padding);
    missText.setPosition(containerPos.x + padding, containerPos.y + padding + 30.f);
    scoreValueText.setPosition(containerPos.x + padding, containerPos.y + padding + 60.f);
}

void Game::resetGame()
{
    currentState = MENU;
    isPlacementPhase = true;
    isDragging = false;
    selectedShipIndex = -1;
    showInvalidMessage = false;
    targetPhaseComplete = false;

    player1 = Player("Player 1");
    player2 = Player("Player 2");
    currentPlayer = &player1;
    opponent = &player2;

    player1.initializeShips(shipTextures);
    player2.initializeShips(shipTextures);

    for (int i = 0; i < gridSize; ++i)
    {
        for (int j = 0; j < gridSize; ++j)
        {
            grid[i][j].setFillColor(sf::Color(255, 255, 255, 0));
        }
    }
}

void Game::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        if (currentState == GAME)
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::R && selectedShipIndex != -1)
                {
                    rotateShip();
                }

                if (event.key.code == sf::Keyboard::Enter && isPlacementPhase)
                {
                    checkAllShipsPlaced();
                }
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                handleMouseClick();
            }

            if (event.type == sf::Event::MouseMoved && isDragging && selectedShipIndex != -1)
            {
                handleShipDragging();
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                handleShipDrop();
            }
        }
        else if (currentState == MENU || currentState == FINAL)
        {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                if (currentState == MENU)
                {
                    if (startButton.getGlobalBounds().contains(mousePos))
                    {
                        currentState = GAME;
                    }
                    else if (exitButton.getGlobalBounds().contains(mousePos))
                    {
                        window.close();
                    }
                }
                else if (currentState == FINAL)
                {
                    if (menuButton.getGlobalBounds().contains(mousePos))
                    {
                        resetGame();
                        // Reset the game state to MENU
                        currentState = MENU;
                    }
                    else if (finalExitButton.getGlobalBounds().contains(mousePos))
                    {
                        window.close();
                    }
                }
            }
        }
    }
}

void Game::rotateShip()
{
    Ship *playerShips = currentPlayer->getShips();
    Ship &ship = playerShips[selectedShipIndex];

    // Clear current position if placed
    if (ship.getIsPlaced())
    {
        ship.clearPosition(ship.getGridPosition().x, ship.getGridPosition().y, currentPlayer->getOccupiedCells());
    }

    // Perform rotation
    ship.rotate(shipTextures);

    // Try to place at current position
    if (ship.getIsPlaced())
    {
        sf::Vector2i pos = ship.getGridPosition();
        if (ship.canPlace(pos.x, pos.y, currentPlayer->getOccupiedCells()) &&
            currentPlayer->validateShipPlacement(selectedShipIndex))
        {
            ship.markPosition(pos.x, pos.y, currentPlayer->getOccupiedCells());
        }
        else
        {
            // Revert rotation if invalid
            ship.rotate(shipTextures);
            ship.markPosition(pos.x, pos.y, currentPlayer->getOccupiedCells());
            showInvalidMessage = true;
            invalidMessageClock.restart();
        }
    }
}

void Game::switchToPlayer2Attack()
{
    currentPlayer = &player2;
    opponent = &player1;
    currentPlayer->setTurnToAttack(true);
    opponent->setTurnToAttack(false);
}

void Game::checkAllShipsPlaced()
{
    if (currentPlayer->allShipsPlaced())
    {
        if (currentPlayer == &player1)
        {
            // Switch to player 2's placement
            currentPlayer = &player2;
            opponent = &player1;
        }
        else
        {
            // Both players have placed ships - start targeting phase
            isPlacementPhase = false;
            currentPlayer = &player1;
            opponent = &player2;
            currentPlayer->setTurnToAttack(true); // Player 1 goes first
            opponent->setTurnToAttack(false);
        }
    }
}

void Game::handleMouseClick()
{
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (isPlacementPhase && !isDragging)
    {
        Ship *playerShips = currentPlayer->getShips();
        for (int i = 0; i < numShips; ++i)
        {
            // Check all parts of the ship
            for (int j = 0; j < playerShips[i].getLength(); ++j)
            {
                if (playerShips[i].getPartBounds(j).contains(mousePos))
                {
                    selectedShipIndex = i;
                    isDragging = true;

                    // Calculate drag offset
                    sf::FloatRect bounds = playerShips[i].getBounds();
                    dragOffset = mousePos - sf::Vector2f(bounds.left, bounds.top);

                    if (playerShips[i].getIsPlaced())
                    {
                        playerShips[i].clearPosition(
                            playerShips[i].getGridPosition().x,
                            playerShips[i].getGridPosition().y,
                            currentPlayer->getOccupiedCells());
                        playerShips[i].setIsPlaced(false);
                    }
                    break;
                }
            }
            if (isDragging)
                break;
        }
    }
    else if (!isPlacementPhase)
    {

        if (player1.getHits() == 21 && player2.getHits() == 21)
        {
            setupScoreCards(player1.getMisses(), player2.getMisses());
            currentState = GameState::FINAL;
            return;
        }

        if (player1.getHits() == 21 && currentPlayer == &player1)
        {

            switchToPlayer2Attack();
            return;
        }

        if (currentPlayer->getTurnToAttack())
        {
            // Targeting logic
            int gridX = (int)((mousePos.x - 20) / cellSize);
            int gridY = (int)((mousePos.y - 20) / cellSize);

            if (gridX >= 0 && gridX < gridSize && gridY >= 0 && gridY < gridSize &&
                !currentPlayer->getIsCellTargeted(gridX, gridY))
            {
                currentPlayer->setIsCellTargeted(gridX, gridY, true);
                currentPlayer->setShowEffect(gridX, gridY, true);

                if (opponent->getOccupiedCell(gridX, gridY))
                {
                    currentPlayer->recordHit();
                    currentPlayer->setCellEffect(gridX, gridY, hitTexture);

                    if (currentPlayer == &player1 && player1.getHits() == 21)
                    {
                        window.clear(sf::Color(210, 225, 246));

                        switchToPlayer2Attack();
                        return;
                    }

                    else if (currentPlayer == &player2 && player2.getHits() == 21)
                    {
                        setupScoreCards(player1.getMisses(), player2.getMisses());
                        currentState = FINAL;
                        return;
                    }
                }
                else
                {
                    currentPlayer->recordMiss();
                    currentPlayer->setCellEffect(gridX, gridY, missTexture);
                }
            }
        }
    }
}

void Game::handleShipDragging()
{
    if (isDragging && selectedShipIndex != -1)
    {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        Ship *playerShips = currentPlayer->getShips();

        sf::Vector2f rawTarget = mousePos - dragOffset;

        int gridX = (int)((rawTarget.x - 20) / cellSize + 0.5f);
        int gridY = (int)((rawTarget.y - 20) / cellSize + 0.5f);

        if (playerShips[selectedShipIndex].getIsVertical())
        {
            gridX = clamp(gridX, 0, gridSize - 1);
            gridY = clamp(gridY, 0, gridSize - playerShips[selectedShipIndex].getLength());
        }
        else
        {
            gridX = clamp(gridX, 0, gridSize - playerShips[selectedShipIndex].getLength());
            gridY = clamp(gridY, 0, gridSize - 1);
        }

        targetGridPosition = sf::Vector2f(
            20 + gridX * cellSize,
            20 + gridY * cellSize);

        // smooth movement
        smoothShipPosition += (targetGridPosition - smoothShipPosition) * lerpFactor;
        playerShips[selectedShipIndex].setPosition(smoothShipPosition.x, smoothShipPosition.y);
    }
}

void Game::handleShipDrop()
{
    if (isDragging && selectedShipIndex != -1)
    {
        Ship *playerShips = currentPlayer->getShips();

        // Use the TARGET grid position (not current visual position)
        int gridX = (int)((targetGridPosition.x - 20) / cellSize);
        int gridY = (int)((targetGridPosition.y - 20) / cellSize);

        // Check placement validity
        bool canPlace = playerShips[selectedShipIndex].canPlace(gridX, gridY,
                                                                currentPlayer->getOccupiedCells());
        bool validBoard = currentPlayer->validateShipPlacement(selectedShipIndex);

        if (canPlace && validBoard)
        {

            if (playerShips[selectedShipIndex].getIsPlaced())
            {
                sf::Vector2i oldPos = playerShips[selectedShipIndex].getGridPosition();
                playerShips[selectedShipIndex].clearPosition(oldPos.x, oldPos.y,
                                                             currentPlayer->getOccupiedCells());
            }

            playerShips[selectedShipIndex].setPosition(targetGridPosition.x, targetGridPosition.y);

            playerShips[selectedShipIndex].markPosition(gridX, gridY,
                                                        currentPlayer->getOccupiedCells());
            playerShips[selectedShipIndex].setGridPosition(gridX, gridY);
            playerShips[selectedShipIndex].setIsPlaced(true);
        }
        else
        {
            showInvalidMessage = true;
            invalidMessageClock.restart();

            // Revert to previous valid state
            if (playerShips[selectedShipIndex].getIsPlaced())
            {
                sf::Vector2i oldPos = playerShips[selectedShipIndex].getGridPosition();
                playerShips[selectedShipIndex].setPosition(20 + oldPos.x * cellSize,
                                                           20 + oldPos.y * cellSize);
            }
            else
            {
                // Return to sidebar
                float startX = 370.0f;
                float startY = 190.0f + selectedShipIndex * (partSize + 10);
                playerShips[selectedShipIndex].setPosition(startX, startY);

                // Reset rotation if needed
                if (playerShips[selectedShipIndex].getIsVertical())
                {
                    playerShips[selectedShipIndex].rotate(shipTextures);
                }
            }
        }

        // Reset drag state
        isDragging = false;
        selectedShipIndex = -1;
        currentPlayer->clearAllShipPositions(); // Refresh grid occupancy
    }
}

void Game::update()
{
    if (showInvalidMessage && invalidMessageClock.getElapsedTime().asSeconds() > 5.0f)
    {
        showInvalidMessage = false;
    }
}

void Game::render()
{
    window.clear(sf::Color(210, 225, 246));

    if (currentState == MENU)
    {
        // Draw menu screen
        window.draw(logoSprite);
        window.draw(startButton);
        window.draw(exitButton);
        window.draw(startText);
        window.draw(exitText);
        window.draw(creditsHead);
        window.draw(creditsBody);
    }
    else if (currentState == GAME)
    {
        window.draw(gridBgSprite);

        // Draw grid
        for (int i = 0; i < gridSize; ++i)
        {
            for (int j = 0; j < gridSize; ++j)
            {
                window.draw(grid[i][j]);
                if (currentPlayer->getShowEffect(j, i))
                {
                    window.draw(currentPlayer->getCellEffect(j, i));
                }
            }
        }

        // Draw UI
        if (isPlacementPhase)
        {
            drawPlacementUI();
            // Draw ships for current player
            Ship *playerShips = currentPlayer->getShips();
            for (int i = 0; i < numShips; ++i)
            {
                playerShips[i].draw(window);
            }
        }
        else
        {
            drawTargetingUI();
        }

        // Display current player
        currentPlayerText.setString("Current Player: " + currentPlayer->getName());
        currentPlayerText.setFont(fontC);
        currentPlayerText.setCharacterSize(18);
        currentPlayerText.setFillColor(sf::Color::Black);
        currentPlayerText.setPosition(20, 350);
        window.draw(currentPlayerText);
    }
    else if (currentState == FINAL)
    {
        // Draw final screen
        for (int i = 0; i < 2; ++i)
        {
            window.draw(playerCards[i]);
            window.draw(playerNames[i]);
            window.draw(hitsTexts[i]);
            window.draw(missesTexts[i]);
            window.draw(scoreTexts[i]);
            window.draw(crownSprites[i]);
        }
        window.draw(menuButton);
        window.draw(finalExitButton);
        window.draw(menuText);
        window.draw(finalExitText);
    }

    window.display();
}

void Game::drawPlacementUI()
{
    window.draw(container1);
    window.draw(container2);
    window.draw(insHead);
    window.draw(insText);

    if (showInvalidMessage)
    {
        window.draw(invalidText);
    }
}

void Game::drawTargetingUI()
{
    window.draw(scoreContainer);
    window.draw(instructionsContainer);
    window.draw(attackInstructions);

    // Update and draw score texts using current player's stats
    hitText.setString("Hits: " + to_string(currentPlayer->getHits()));
    missText.setString("Misses: " + to_string(currentPlayer->getMisses()));
    scoreValueText.setString("Score: " + to_string(currentPlayer->getScore()));

    window.draw(hitText);
    window.draw(missText);
    window.draw(scoreValueText);
}
void Game::setupScoreCards(int player1Misses, int player2Misses)
{
    int playerScores[2] = {420 - player1Misses * 5, 420 - player2Misses * 5};
    int winnerIndex = playerScores[0] > playerScores[1] ? 0 : 1;
    bool showCrown = false;
    if (playerScores[0] == playerScores[1])
    {
        winnerIndex = -1; // Draw
    }

    float cardWidth = 250, cardHeight = 200;
    float spacing = 50;
    float startX = (800 - (2 * cardWidth + spacing)) / 2;

    for (int i = 0; i < 2; ++i)
    {
        // Card
        playerCards[i].setSize(sf::Vector2f(cardWidth, cardHeight));
        playerCards[i].setFillColor(i == winnerIndex ? sf::Color(255, 215, 0) : sf::Color(200, 200, 200));
        playerCards[i].setOutlineColor(sf::Color::Black);
        playerCards[i].setOutlineThickness(1);
        playerCards[i].setPosition(startX + i * (cardWidth + spacing), 100);

        // Name
        playerNames[i].setFont(fontC);
        playerNames[i].setCharacterSize(20);
        playerNames[i].setString("Player " + to_string(i + 1));
        playerNames[i].setFillColor(sf::Color::Black);
        playerNames[i].setPosition(playerCards[i].getPosition().x + 20, playerCards[i].getPosition().y + 10);

        // Score info
        hitsTexts[i].setFont(fontC);
        hitsTexts[i].setCharacterSize(18);
        hitsTexts[i].setFillColor(sf::Color::Black);
        hitsTexts[i].setString("Hits: " + to_string(i == 0 ? 21 : 21));
        hitsTexts[i].setPosition(playerCards[i].getPosition().x + 20, playerCards[i].getPosition().y + 50);

        missesTexts[i].setFont(fontC);
        missesTexts[i].setCharacterSize(18);
        missesTexts[i].setFillColor(sf::Color::Black);
        missesTexts[i].setString("Misses: " + to_string(i == 0 ? player1Misses : player2Misses));
        missesTexts[i].setPosition(playerCards[i].getPosition().x + 20, playerCards[i].getPosition().y + 80);

        scoreTexts[i].setFont(fontC);
        scoreTexts[i].setCharacterSize(18);
        scoreTexts[i].setFillColor(sf::Color::Black);
        scoreTexts[i].setString("Score: " + to_string(playerScores[i]));
        scoreTexts[i].setPosition(playerCards[i].getPosition().x + 20, playerCards[i].getPosition().y + 110);

        if (i == winnerIndex && crownTexture.loadFromFile("assets/trophy.png"))
        {
            showCrown = true;
            crownSprites[i].setTexture(crownTexture);
            crownSprites[i].setScale(0.1f, 0.1f); // Resize
            crownSprites[i].rotate(25);
            crownSprites[i].setPosition(playerCards[i].getPosition().x + cardWidth - 10, playerCards[i].getPosition().y - 10);
        }
    }
}
