#pragma once

#include <string>
#include <iostream>

#ifdef _WIN32
#define CLEAR_SCREEN system("cls")
#else
#define CLEAR_SCREEN system("clear")
#endif

int getNumber(const std::string &message);
int getValidateAnswer(const std::string &message, const std::string &errorMessage,const int &leftBorder, const int &rightBorder);
int calculateRandomCharacteristic(int leftBorder, int rightBorder);