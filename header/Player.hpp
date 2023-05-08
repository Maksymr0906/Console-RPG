#pragma once

#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>

#include "Item.hpp"

class Player {
private:
    static constexpr const int def_health = 100;
    static constexpr const int def_max_health = 100;
    static constexpr const int def_min_damage = 5;
    static constexpr const int def_max_damage = 10;
    static constexpr const int def_xp = 0;
    static constexpr const int def_level = 1;
    static constexpr const char *def_name = "Unnamed";
protected:
    std::string name;
    int health, maxHealth, minDamage, maxDamage, xp, level;
    std::vector<Item> inventory;
public:
    //Constructors
    Player();

    //Accessors
    int get_health() {return health;}
    int get_maxHealth() {return maxHealth;}
    int getMinDamage() {return minDamage;}
    int getMaxDamage() {return maxDamage;}
    int getXp() {return xp;}
    int getLevel() {return level;}
    std::string getName() {return name;}

    //Modifiers
    void setHealth(int health) {this->health = health;}
    void setMaxHealth(int maxHealth) {this->maxHealth = maxHealth;}
    void setMinDamage(int minDamage) {this->minDamage = minDamage;}
    void setMaxDamage(int maxDamage) {this->maxDamage = maxDamage;}
    void setXp(int xp) {this->xp = xp;}
    void setLevel(int level) {this->level = level;}
    void setName(std::string name) {this->name = name;}

    void showInventory();
    bool isAlive();
};
