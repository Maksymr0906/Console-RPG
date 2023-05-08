#include "Player.hpp"

Player::Player() {
    name = def_name;
    health = def_health;
    maxHealth = def_health;
    minDamage = def_min_damage;
    maxDamage = def_max_damage;
    exp = def_exp;
    expNext = def_exp_next;
    level = def_level;
    inventory = std::vector<Item>(0);
}

void Player::showInventory() {
    if(inventory.empty()) {
        std::cout << "Your inventory is empty." << std::endl;
        return ;
    }

    for(auto &item: inventory) {
        std::cout << "Name: " << item.get_name() << " Category: " << item.get_category() << std::endl;
    }
}

bool Player::isAlive() const {
    return health > 0 ? true : false; 
}