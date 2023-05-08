#include <iostream>
#include <windows.h>

#include "Option.hpp"
#include "Item.hpp"
#include "Player.hpp"
#include "Zombie.hpp"

using namespace std;

void fight(Player player);

int main() {
    srand(time(0));
    Player player;
    fight(player);
    /* backstory();

    Option my_option;
    switch (my_option) {
    case Option::EXPLORE_WORLD:

        break;
    case Option::VIEW_INVENTORY:

        break;
    case Option::QUIT:

        break;
    default:
        break;
    } */
}

void fight(Player player) {
    std::cout << "You hear something approaching." << std::endl;
    Sleep(1000);
    std::cout << "Can it carry? - you thought." << std::endl;
    Sleep(1000);
    std::cout << "Unfortunately, you were not lucky to meet Zombie" << std::endl;
    Zombie zombie{};
    bool chanceToEscape = true;
    bool isPlayerEscape{false};
    while(player.isAlive() && zombie.isAlive()) {
        if(chanceToEscape) {
            std::cout << "You still have a chance to escape. Will you try? y/n" << std::endl;
            char playerWantToEscape;
            std::cin >> playerWantToEscape; 
            if(playerWantToEscape == 'y') {
                isPlayerEscape = (rand() % 100 < 30? 1 : 0);
            }

            chanceToEscape = false;
        } 
        if(isPlayerEscape) {
                std::cout << "Congratulation! You escaped from Zombie" << std::endl;
                break;
            }
        else {
            std::cout << "Failed! You couldn't escape. Zombie attacked you" << std::endl;
        }

        int zombieDamage = zombie.inflictDamage();
        player.takeDamage(zombieDamage);

        std::cout << "Zombie attacked you and dealt " << zombieDamage << " damage" << std::endl;
        std::cout << "Your health: " << player.get_health() << std::endl;
        Sleep(5000);
        if(!player.isAlive()) {
            std::cout << "Zombie defeat you" << std::endl;
            break;
        }

        int playerDamage = player.inflictDamage();
        zombie.takeDamage(playerDamage);

        std::cout << "You attacked Zombie and dealt " << playerDamage << " damage" << std::endl;
        std::cout << "Zombie health: " << zombie.get_health() << std::endl;
        Sleep(5000);
        if(!zombie.isAlive()) {
            std::cout << "You defeat zombie" << std::endl;
            break;
        }

    }
}