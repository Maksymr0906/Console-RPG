#include "Game.hpp"

int main() {
    srand(time(NULL));
    Game game;
    game.initialize();
    game.mainMenu();

    while (game.getPlaying()) {
        game.gameMenu();
    }
}
