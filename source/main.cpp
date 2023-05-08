#include "Game.hpp"
#include "Player.hpp"
#include "Zombie.hpp"

int main() {
    Game game;
    game.backstory();

    while(game.getPlaying()) {
        game.mainMenu();
    }
}
