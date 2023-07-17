#pragma once

#include <string>
#include <iostream>

int getNumber(const std::string &message);
int getValidateAnswer(const std::string &message, const std::string &errorMessage,const int &leftBorder, const int &rightBorder);
int calculateRandomCharacteristic(int leftBorder, int rightBorder);