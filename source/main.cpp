#include "Game.hpp"

#include <ctime>

int main() {
    srand(time(NULL));

    Game game;
    game.backstory();
    game.initialize();
    while (game.getPlaying()) {
        game.mainMenu();
    }
}
