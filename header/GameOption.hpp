#pragma once

#include "Functions.hpp"

enum class GameOption {
    BACK_TO_MAIN_MENU = 0,
    EXPLORE_WORLD,
    REST,
    SHOP,
    VIEW_STATS,
    VIEW_INVENTORY,
    UPGRADE_CHARACTERISTICS,
    SAVE_PLAYER
};

GameOption getGameOption();