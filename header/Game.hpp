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
    bool getPlaying() const {return playing;}
    //Option getOption() const {return option;}

    void setPlaying(bool playing) {this->playing = playing;}
    void setOption(Option option) {this->option = option;}

    void backstory() const;
    void mainMenu();
};

void printMenu();