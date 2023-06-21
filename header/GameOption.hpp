#pragma once

#include <iostream>

enum class GameOption {
    BACK_TO_MAIN_MENU = 0,
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

GameOption getGameOption();