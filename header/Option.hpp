#pragma once

#include <iostream>

enum class Option{
    Quit = 1,
    EXPLORE_WORLD,
    SHOP,
    VIEW_STATS,
    VIEW_INVENTORY,
    LEVEL_UP,
};

Option getOption();