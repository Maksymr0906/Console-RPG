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
    static constexpr const int def_damage = 20;
protected:
    int health, maxHealth, damage;
    std::vector<Item> inventory;
public:
    Player(int health = def_health, int maxHealth = def_max_health, int damage = def_damage, std::vector<Item> inventory = std::vector<Item>(0))
    :health{health}, maxHealth{maxHealth}, damage{damage}, inventory{inventory} {};

    int get_health() {return health;}
    void set_health(int health) {this->health = health;}
    int get_maxHealth() {return maxHealth;}
    void set_maxHealth(int maxHealth) {this->maxHealth = maxHealth;}
    int get_damage() {return damage;}
    void set_damage(int damage) {this->damage = damage;}

    void takeDamage(int damage) {health -= damage;}

    void showInventory();
    bool isAlive();
};

void Player::showInventory() {
    if(inventory.empty()) {
        std::cout << "Your inventory is empty." << std::endl;
        return ;
    }

    for(auto &item: inventory) {
        std::cout << "Name: " << item.get_name() << " Category: " << item.get_category() << std::endl;
    }
}

bool Player::isAlive() {
    return health > 0 ? true : false; 
}