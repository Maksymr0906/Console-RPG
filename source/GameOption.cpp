#include "GameOption.hpp"

GameOption getGameOption() {
    std::cout << "\nEnter your choice: ";
    int number{};
    std::cin >> number;

    return static_cast<GameOption>(number);
}