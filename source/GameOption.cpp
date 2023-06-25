#include "GameOption.hpp"

GameOption getGameOption() {
    int number = getValidateAnswer("Enter your choice: ", "\nIncorrect choice", 0, 7);

    return static_cast<GameOption>(number);
}