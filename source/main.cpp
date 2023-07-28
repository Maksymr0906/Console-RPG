#include "Game.hpp"

int main() {
    Game game;
    game.initialize();
    game.mainMenu();

    while (game.getPlaying()) {
        game.gameMenu();
    }
}
