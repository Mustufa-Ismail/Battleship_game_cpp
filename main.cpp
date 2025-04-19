#include "Game.h"
#include <cstdlib>
#include <ctime>

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
 