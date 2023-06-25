#include "Functions.hpp"

int getNumber(const std::string &message) {
    int number{};
    std::cout << message;
    std::cin >> number;
    return number;
}

int getValidateAnswer(const std::string &message, const std::string &errorMessage, const int &leftBorder, const int &rightBorder) {
    int number = getNumber(message);

    bool isFirstTimeError = true;
    while(std::cin.fail() || number < leftBorder || number > rightBorder) {
        if(isFirstTimeError)
            std::cout << errorMessage << "\n";
        std::cin.clear();
        std::cin.ignore(100, '\n');

        if(!isFirstTimeError) {
            std::cout << "\033[1A";
            std::cout << "\033[2K";
        }
       
        number = getNumber(message);
        isFirstTimeError = false;
    }

    std::cin.ignore(100, '\n');
    std::cout << "\n";

    return number;
}