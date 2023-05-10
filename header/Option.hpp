#pragma once

#include <iostream>

enum class Option{
    QUIT = 1,
    EXPLORE_WORLD,
    SHOP,
    VIEW_STATS,
    VIEW_INVENTORY,
    LEVEL_UP,
};

Option getOption();