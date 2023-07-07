#include "Functions.hpp"

int getNumber(const std::string &message) {
    int number{};
    std::cout << message;
    std::cin >> number;
    return number;
}

int getValidateAnswer(const std::string &message, const std::string &errorMessage, const int &leftBorder, const int &rightBorder) {
    int number = getNumber(message);

    while(std::cin.fail() || number < leftBorder || number > rightBorder) {
        std::cout << errorMessage << "\n";
        std::cin.clear();
        std::cin.ignore(100, '\n');
       
        number = getNumber(message);
    }

    std::cin.ignore(100, '\n');
    std::cout << "\n";

    return number;
}