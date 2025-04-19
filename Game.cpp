#include "Game.h"
#include <iostream>
using namespace std;

Game::Game(Player* player1, Player* player2) : p1(player1), p2(player2) {}

void Game::start() {
    cout << "\n-- Player 1 placing ships --\n";
    p1->placeShips(board1);

    cout << "\n-- Player 2 placing ships --\n";
    p2->placeShips(board2);

    while (true) {
        cout << "\n-- Player 1's Turn --\n";
        p1->makeMove(board2);
        if (board2.allShipsSunk()) {
            cout << "Player 1 wins!\n";
            break;
        }

        cout << "\n-- Player 2's Turn --\n";
        p2->makeMove(board1);
        if (board1.allShipsSunk()) {
            cout << "Player 2 wins!\n";
            break;
        }
    }
}
