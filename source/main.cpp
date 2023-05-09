#include "Game.hpp"
#include "Player.hpp"
#include "Zombie.hpp"
#include <ctime>

int main() {
    srand(time(NULL));
    
    Game game;
    game.backstory();;
    while(game.getPlaying()) {
        game.mainMenu();
    }
}
