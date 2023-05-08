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
    Option getOption() {return option;}

    void setPlaying(bool playing) {this->playing = playing;}
    void setOption(Option option) {this->option = option;}
    
    void backstory();
    void mainMenu();
};

void printMenu();