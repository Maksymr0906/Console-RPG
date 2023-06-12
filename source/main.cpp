#include "Game.hpp"

int main() {
    srand(time(NULL));
    
    Game game;
    game.startGame();
    while (game.getPlaying()) {
        game.mainMenu();
    }
}
