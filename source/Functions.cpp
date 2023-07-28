#include "Functions.hpp"

int getNumber(const std::string &message) {
    int number{};
    std::cout << message;
    std::cin >> number;
    return number;
}

int askYesNo(const std::string &message) {
    return getValidatedAnswer(message + "\n(1) - Yes\n(2) - No\nYour choice: ", "Invalid choice", 1, 2);
}

int getValidatedAnswer(const std::string &message, const std::string &errorMessage, const int &leftBorder, const int &rightBorder) {
    int number = getNumber(message);

    while(std::cin.fail() || number < leftBorder || number > rightBorder) {
        std::cout << errorMessage << std::endl;
        std::cin.clear();
        std::cin.ignore(100, '\n');
       
        number = getNumber(message);
    }

    std::cin.ignore(100, '\n');
    std::cout << "\n";

    return number;
}

int getRandomNumberInRange(int leftBorder, int rightBorder) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(leftBorder, rightBorder);
    return dist(gen);
}

void printFormattedLine(const std::string &label, const std::string &value, int labelSize, int valueSize) {
    std::cout << std::left << std::setw(labelSize) << std::setfill(' ') << label << std::setw(valueSize) << value << std::setfill('=') << std::setw(3) << " " << std::endl;
}

void printDivider(const char &divideSymbol, int sizeOfDivider) {
    std::cout << std::right << std::setw(sizeOfDivider) << std::setfill(divideSymbol) << " " << std::endl;
}

std::string formatLabelValue(const std::string &label, const std::string &value) {
    return "== " + label + ": " + value + " ";
}

void pressEnterToContinue() {
    std::cout << std::endl << std::setw(70) << std::right << "=== Press Enter to continue ===" << std::endl;
    std::string input{};
    std::getline(std::cin, input);
    CLEAR_SCREEN;
}