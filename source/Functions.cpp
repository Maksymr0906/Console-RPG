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
    return rand() % (rightBorder - leftBorder + 1) + leftBorder;
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