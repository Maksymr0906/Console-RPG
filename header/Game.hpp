#pragma once

#include <iomanip>
#include <conio.h>

#include "Option.hpp"
#include "Player.hpp"

class Game {
private:
protected:
    Option option;
    bool playing;
    Player player;
public:
    Game();


    bool getPlaying() const { return playing; }
    //Option getOption() const {return option;}

    void setPlaying(bool playing) { this->playing = playing; }
    void setOption(Option option) { this->option = option; }

    void backstory() const;
    void mainMenu();
    void initialize();
};

void printMenu();