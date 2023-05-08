#pragma once

#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>

class Zombie {
private:
    static constexpr const int def_health = 100;
    static constexpr const int def_damage = 20;
    static constexpr const int def_max_health = 100;
protected:
    int maxHealth, health, damage;
public:
    Zombie(int maxHealth = def_max_health, int health = def_health, int damage = def_damage)
    :maxHealth{maxHealth}, health{health}, damage{damage} {};
    ~Zombie() {};

    int get_health() {return health;}
    
    void takeDamage(int damage) {health -= damage;}
    bool isAlive();
};

bool Zombie::isAlive() {
    return health > 0 ? true : false; 
}