#pragma once

#include <iomanip>
#include <conio.h>

#include "Option.hpp"

class Game {
private:
protected:
    Option option;
    bool playing;
public:
    bool getPlaying() {return playing;}

    void backstory();
    void mainMenu();
};


void Game::backstory() {
    std::cout << "Zombie Project - a simple console game in which you have to survive in an unfair world full of zombies." << std::endl
              << "You come to your senses in an empty New York, which is full of zombies."                                 << std::endl
              << "All you have in your pockets is a knife, Coca-Kolya, and a loaf of bread."                               << std::endl
              << "For now, all you need is to survive, and how to achieve this depends on you."                            << std::endl
              << "So get up and don't waste a single moment on empty thoughts, otherwise you simply won't survive."        << std::endl;
    
    std::cout << std::endl << "/*/*Press any key to continue/*/*" << std::endl;
    _getch();
}

void Game::mainMenu() {
    std::cout << std::setw(20) << std::right << "Main Menu" << std::endl
              << "(1) - Quit"                               << std::endl
              << "(2) - Explore world"                      << std::endl
              << "(3) - Visit Merchant"                     << std::endl
              << "(4) - View my stats"                      << std::endl
              << "(5) - View my inventory"                  << std::endl
              << "(6) - Level up"                           << std::endl;

    
    option = getOption();
    
    switch (option) {
    case Option::Quit:
        playing = false;
        break;
    case Option::EXPLORE_WORLD:
        break;
    case Option::SHOP:
        break;
    case Option::VIEW_STATS:
        break;
    case Option::VIEW_INVENTORY:
        break;
    case Option::LEVEL_UP:
        break;
    default:
        std::cout << "Incorrect choice" << std::endl;
        break;
    }
}
