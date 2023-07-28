#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include <random>

#ifdef _WIN32
#define CLEAR_SCREEN system("cls")
#else
#define CLEAR_SCREEN system("clear")
#endif

int getNumber(const std::string &message);
int getValidatedAnswer(const std::string &message, const std::string &errorMessage,const int &leftBorder, const int &rightBorder);
int getRandomNumberInRange(int leftBorder, int rightBorder);
void printFormattedLine(const std::string &label, const std::string &value, int labelSize, int valueSize);
void printDivider(const char &divideSymbol, int sizeOfDivider);
std::string formatLabelValue(const std::string &label, const std::string &value);
void pressEnterToContinue();
int askYesNo(const std::string &message);