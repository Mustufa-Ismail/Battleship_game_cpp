#include "Player.h"
#include <cstdlib>
#include <iostream>
using namespace std;

void HumanPlayer::placeShips(Board& board) {
    int sizes[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        int row, col, direction;
        board.displayBoard(true);
        cout << "\nPlacing ship of size " << sizes[i] << endl;
        cout << "Enter row and column (0-9): ";
        cin >> row >> col;
        cout << "Horizontal (1) or Vertical (0): ";
        cin >> direction;
        bool horizontal = direction;

        while (!board.canPlaceShip(row, col, sizes[i], horizontal)) {
            cout << "Invalid position. Try again.\n";
            cout << "Enter row and column: ";
            cin >> row >> col;
            cout << "Horizontal (1) or Vertical (0): ";
            cin >> direction;
            horizontal = direction;
        }

        board.placeShip(row, col, sizes[i], horizontal);
    }
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
