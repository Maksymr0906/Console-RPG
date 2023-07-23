#include "GameOption.hpp"

GameOption getGameOption() {
    int number = getValidateAnswer("Enter your choice: ", "\nInvalid choice", 0, 7);

    return static_cast<GameOption>(number);
}