#pragma once
#include <iostream>

enum class Option{
    EXPLORE_WORLD = 1,
    VIEW_INVENTORY,
    QUIT
};

void backstory();
Option getOption();