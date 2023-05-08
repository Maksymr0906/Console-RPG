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
    static constexpr const int def_exp = 0;
    static constexpr const int def_exp_next = 100;
    static constexpr const int def_level = 1;
    static constexpr const char *def_name = "Unnamed";
protected:
    std::string name;
    int health, maxHealth, minDamage, maxDamage, exp, expNext, level;
    std::vector<Item> inventory;
public:
    //Constructors
    Player();

    //Accessors
    int get_health() const {return health;}
    int get_maxHealth() const {return maxHealth;}
    int getMinDamage() const {return minDamage;}
    int getMaxDamage() const {return maxDamage;}
    int getExp() const {return exp;}
    int getExpNext() const {return expNext;}
    int getLevel() const {return level;}
    std::string getName() const {return name;}

    //Modifiers
    void setHealth(int health) {this->health = health;}
    void setMaxHealth(int maxHealth) {this->maxHealth = maxHealth;}
    void setMinDamage(int minDamage) {this->minDamage = minDamage;}
    void setMaxDamage(int maxDamage) {this->maxDamage = maxDamage;}
    void setExp(int exp) {this->exp = exp;}
    void setExpNext(int expNext) {this->expNext = expNext;}
    void setLevel(int level) {this->level = level;}
    void setName(std::string name) {this->name = name;}

    void showInventory();
    bool isAlive() const;
};
