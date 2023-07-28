#pragma once

#include "Functions.hpp"

enum class GameOption {
    BACK_TO_MAIN_MENU = 0,
    EXPLORE_WORLD,
    RETURN_SHELTER,
    SHOP,
    VIEW_INVENTORY,
    VIEW_STATS,
    UPDATE_CHARACTERISTICS,
    SAVE_PLAYER
};

GameOption getGameOption();