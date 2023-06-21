#pragma once

#include <iomanip>
#include <conio.h>

#include "GameOption.hpp"
#include "Event.hpp"

class Game {
private:
    //Methods
    void backstory() const;
    void explore();
    void createNewPlayer();
    void savePlayers();
    void loadPlayers();
    std::vector<Player> getPlayersFromFile(const std::string &filePath);
    void displayAllPlayers() const;
    void printGameMenu() const;
    int findPlayerIndexByName(const std::string &name) const;
protected:
    GameOption gameOption;
    bool playing;
    int indexOfActivePlayer;
    std::vector<Player> players;
public:
    Game();

    bool getPlaying() const { return playing; }
    //Option getOption() const {return option;}

    void setPlaying(bool playing) { this->playing = playing; }
    void setOption(GameOption gameOption) { this->gameOption = gameOption; }

    //Methods
    void initialize();
    void gameMenu();
    void mainMenu();
};

