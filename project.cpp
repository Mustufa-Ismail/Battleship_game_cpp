#include "iostream"
#include <cstdlib>
using namespace std ;

//cell class

class Cell {
    private:
        bool hasShip;
        bool isHit;
    
    public:
        Cell() : hasShip(false), isHit(false) {}
    
        void placeShip() {
            hasShip = true;
        }
    
        void markHit() {
            isHit = true;
        }
    
        bool wasHit() const {
            return isHit;
        }
    
        bool containsShip() const {
            return hasShip;
        }
    
        char display(bool revealShip = false) const {
            if (isHit) {
                return hasShip ? 'X' : 'O';
            } else {
                return (revealShip && hasShip) ? 'S' : '.';
            }
        }
    };
    

//ship class

class Ship {
    private:
        int size;
        int hitsTaken;
        int coordinates[5][2];  // max 5 cells per ship
        int coordCount;
    
    public:
        Ship() : size(0), hitsTaken(0), coordCount(0) {}
    
        Ship(int s) : size(s), hitsTaken(0), coordCount(0) {}
    
        void addCoordinate(int row, int col) {
            if (coordCount < 5) {
                coordinates[coordCount][0] = row;
                coordinates[coordCount][1] = col;
                coordCount++;
            }
        }


        bool occupiesCell(int row, int col) const {
            for (int i = 0; i < coordCount; i++) {
                if (coordinates[i][0] == row && coordinates[i][1] == col)
                    return true;
            }
            return false;
        }
    
        void registerHit() {
            if (hitsTaken < size)
                hitsTaken++;
        }
    
        bool isSunk() const {
            return hitsTaken >= size;
        }
    
        int getSize() const {
            return size;
        }
    };
    
//cell or ship ka direct relation nhi hai but ship's objects cell ke coordinate store kerenge 
    class Board {
        private:
            Cell grid[10][10];
            Ship ships[5];
            int shipCount;
        
        public:
            Board() {
                shipCount = 0;
            }
        
            bool checkShip(int row,int col){
                return grid[row][col].containsShip();
            }

            bool canPlaceShip(int startRow, int startCol, int size, bool horizontal) {
                if (horizontal) {
                    if (startCol + size > 10) return false;
                    for (int i = 0; i < size; i++) {
                        if (grid[startRow][startCol + i].containsShip()) return false;
                    }
                } else {
                    if (startRow + size > 10) return false;
                    for (int i = 0; i < size; i++) {
                        if (grid[startRow + i][startCol].containsShip()) return false;
                    }
                }
                return true;
            }
        
            void placeShip(int startRow, int startCol, int size, bool horizontal) {
                if (shipCount >= 5) return;
                if (!canPlaceShip(startRow, startCol, size, horizontal)) return;
        
                Ship newShip(size);
        
                if (horizontal) {
                    for (int i = 0; i < size; i++) {
                        grid[startRow][startCol + i].placeShip();
                        newShip.addCoordinate(startRow, startCol + i);
                    }
                } else {
                    for (int i = 0; i < size; i++) {
                        grid[startRow + i][startCol].placeShip();
                        newShip.addCoordinate(startRow + i, startCol);
                    }
                }
        
                ships[shipCount] = newShip;
                shipCount++;
            }
        
            void attackCell(int row, int col) {
                grid[row][col].markHit();
        
                for (int i = 0; i < shipCount; i++) {
                    if (ships[i].occupiesCell(row, col)) {
                        ships[i].registerHit();
                        break;
                    }
                }
            }
        
            bool hasLost() const {
                for (int i = 0; i < shipCount; i++) {
                    if (!ships[i].isSunk()) return false;
                }
                return true;
            }
        
            void displayBoard(bool reveal = false) const {
                for (int i = 0; i < 10; i++) {
                    cout << "|";
                    for (int j = 0; j < 10; j++) {
                        cout << grid[i][j].display(reveal) << "|";
                    }
                    cout << endl;
                }
            }

            bool allShipsSunk() {
                for (int i = 0; i < shipCount; ++i) {
                    if (!ships[i].isSunk()) {
                        return false;
                    }
                }
                return true;
            }
            
            void displayShipStatus(){
                for(int i=0;i<shipCount;i++){
                    if(ships[i].isSunk()){
                        cout<<"Ship "<<i+1<<" destroyed ! "<<endl;
                    }else{
                        cout<<"Ship "<<i+1<<" remaining ! "<<endl;
                    }
                }
            }
        };
        

class Player {
    public:
        virtual void placeShips(Board& board) = 0;
        virtual void makeMove(Board& opponentBoard) = 0;
    };
            

    class HumanPlayer : public Player {
        public:
            void placeShips(Board& board) override {
                int sizes[5] = {1, 2, 3, 4, 5};
                for (int i = 0; i < 5; ++i) {
                    int row, col;
                    int direction;
        
                    board.displayBoard(true);
                    cout << "\nPlacing ship of size " << sizes[i] << endl;
                    cout << "Enter row and column (0-9): ";
                    cin >> row >> col;
                    cout << "Horizontal or Vertical? (1/0): ";
                    cin >> direction;
        
                    bool horizontal = direction;
        
                    while (!board.canPlaceShip(row, col, sizes[i], horizontal)) {
                        cout << "Invalid position. Try again.\n";
                        cout << "Enter row and column: ";
                        cin >> row >> col;
                        cout << "Horizontal or Vertical? (h/v): ";
                        cin >> direction;
                        horizontal = direction;
                    }
        
                    board.placeShip(row, col, sizes[i], horizontal);
                }
            }
        
            void makeMove(Board& opponentBoard) override {
                while(true){
                    int row, col;
                    opponentBoard.displayShipStatus();
                    opponentBoard.displayBoard();
                    cout << "Your turn! Enter attack coordinates: ";
                    cin >> row >> col;
            
                    opponentBoard.attackCell(row, col);
                    
                    if(!opponentBoard.checkShip(row,col)){
                        break;
                    }
                }
            }
        };
        

        class BotPlayer : public Player {
            private:
                bool attackMemory[10][10]; // to avoid repeating attacks
            
            public:
                BotPlayer() {
                    for (int i = 0; i < 10; ++i)
                        for (int j = 0; j < 10; ++j)
                            attackMemory[i][j] = false;
                }
            
                void placeShips(Board& board) override {
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
            
                void makeMove(Board& opponentBoard) override {
                    while(true){
                        int row, col;
                        opponentBoard.displayShipStatus();
                        
                        do {
                            row = rand() % 10;
                            col = rand() % 10;
                        } while (attackMemory[row][col]); // bot values repeat na kare
                
                        attackMemory[row][col] = true;
                        cout << "Bot attacks (" << row << ", " << col << ")\n";
                
                        opponentBoard.attackCell(row, col);
                        opponentBoard.displayBoard();
                        if(!opponentBoard.checkShip(row,col)){
                            break;
                        }
                    }
                }
            };
            

            class Game {
                private:
                    Player* p1;
                    Player* p2;
                    Board board1;
                    Board board2;
                
                public:
                    Game(Player* player1, Player* player2) : p1(player1), p2(player2) {}
                
                    void start() {
                        cout << "\n-- Player 1 placing ships --\n";
                        p1->placeShips(board1);
                
                        cout << "\n-- Player 2 placing ships --\n";
                        p2->placeShips(board2);
                
                        while (true) {
                            cout << "\n-- Player 1's Turn --\n";
                            p1->makeMove(board2);
                            if (board2.allShipsSunk()) {
                                cout << "Player 1 wins! \n";
                                break;
                            }
                
                            cout << "\n-- Player 2's Turn --\n";
                            p2->makeMove(board1);
                            if (board1.allShipsSunk()) {
                                cout << "Player 2 wins! \n";
                                break;
                            }
                        }
                    }
                };

                
                int main() {
                    srand(time(0));
                
                    Player* human = new HumanPlayer();
                    Player* bot = new BotPlayer();
                
                    Game game(human, bot);
                    game.start();
                
                    delete human;
                    delete bot;
                
                    return 0;
                }
                
