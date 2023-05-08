#include <iostream>
#include <windows.h>

#include "Game.hpp"
#include "Player.hpp"
#include "Zombie.hpp"

using namespace std;

int main() {
    Game game;
    game.backstory();

    while(game.getPlaying()) {
        game.mainMenu();
    }
}
