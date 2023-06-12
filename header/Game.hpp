#pragma once

#include <iomanip>
#include <conio.h>

#include "Option.hpp"
#include "Event.hpp"

class Game {
private:
protected:
    Option option;
    bool playing;
    int indexOfActivePlayer;
    std::vector<Player> players;
public:
    Game();

    bool getPlaying() const { return playing; }
    //Option getOption() const {return option;}

    void setPlaying(bool playing) { this->playing = playing; }
    void setOption(Option option) { this->option = option; }

    //Methods
    void backstory() const;
    void mainMenu();
    void initialize();
    void explore();
    void createNewPlayer();
    void savePlayers();
    void loadPlayers();
    void startGame();
};

void printMenu();