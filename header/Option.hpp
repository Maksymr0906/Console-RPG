#pragma once

#include <iostream>

enum class Option {
    QUIT = 0,
    EXPLORE_WORLD,
    REST,
    SHOP,
    VIEW_STATS,
    VIEW_INVENTORY,
    LEVEL_UP,
    UPGRADE_CHARACTERISTICS,
    CREATE_NEW_PLAYER,
    SAVE_PLAYER,
    LOAD_PLAYER
};

Option getOption();