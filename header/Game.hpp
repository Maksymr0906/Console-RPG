#pragma once

#include "GameOption.hpp"
#include "Event.hpp"

class Game {
private:
    static constexpr const int MAX_SIZE_OF_NAME = 15;
    //Methods
    void backstory() const;
    void explore();
    void createNewPlayer();
    void savePlayers();
    int selectPlayer();
    std::vector<Player> loadPlayers(const std::string &filePath);
    void printAllPlayers() const;
    void printGameMenu() const;
    int findPlayerIndexByName(const std::string &name) const;
    void askToSavePlayer();
    void deletePlayer();
    void deletePlayerByIndex(int index);
    void shelter();
    void sleep();
    void shop();
protected:
    GameOption gameOption;
    bool playing;
    int indexOfActivePlayer;
    std::vector<Player> players;
    bool isPlayerSaved;
    int timeToUpdateStore;
public:
    Game();

    bool getPlaying() const { return playing; }

    void setPlaying(bool playing) { this->playing = playing; }
    void setOption(GameOption gameOption) { this->gameOption = gameOption; }

    //Methods
    void initialize();
    void mainMenu();
    void gameMenu();
};

