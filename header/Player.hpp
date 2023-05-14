#pragma once

#include <ctime>
#include <cstdlib>
#include <string>
#include <iostream>

#include "Inventory.hpp"

class Player {
private:
    static constexpr const int def_health = 10;
    static constexpr const int def_max_health = 10;
    static constexpr const int def_min_damage = 5;
    static constexpr const int def_max_damage = 10;
    static constexpr const int def_exp = 0;
    static constexpr const int def_exp_next = 100;
    static constexpr const int def_level = 1;
    static constexpr const char *def_name = "Unnamed";
    static constexpr const int def_stamina = 10;
    static constexpr const int def_stamina_max = 10;
    static constexpr const int def_defence = 1;
    static constexpr const int def_strength = 5;
    static constexpr const int def_dexterity = 5;
    static constexpr const int def_intelligence = 5;
    static constexpr const int def_luck = 1;
    static constexpr const int def_stat_points = 0;
    static constexpr const int def_skill_points = 0;
    static constexpr const int def_money = 30;
protected:
    std::string name;
    int health, maxHealth;
    int minDamage, maxDamage;
    int exp, expNext, level;
    int stamina, staminaMax;
    int defence;
    int strength, dexterity, intelligence;
    int luck; 
    int statPoints, skillPoints;
    int money;
    //int radiation;
    Inventory inventory;
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
    int getStamina() const {return stamina;}
    int getStaminaMax() const {return staminaMax;}
    int getDefence() const {return defence;}
    int getStrength() const {return strength;}
    int getDexterity() const {return dexterity;}
    int getIntelligence() const {return intelligence;}
    int getLuck() const {return luck;}
    int getStatPoints() const {return statPoints;}
    int getSkillPoints() const {return skillPoints;}
    int getMoney() const {return money;}
    std::string getName() const {return name;}
    Inventory &getInventory() {return inventory;}

    //Modifiers
    void setHealth(int health) {this->health = health;}
    void setMaxHealth(int maxHealth) {this->maxHealth = maxHealth;}
    void setMinDamage(int minDamage) {this->minDamage = minDamage;}
    void setMaxDamage(int maxDamage) {this->maxDamage = maxDamage;}
    void setExp(int exp) {this->exp = exp;}
    void setExpNext(int expNext) {this->expNext = expNext;}
    void setLevel(int level) {this->level = level;}
    void setStamina(int stamina) {this->stamina = stamina;}
    void setStaminaMax(int staminaMax) {this->staminaMax = staminaMax;}
    void setDefence(int defence) {this->defence = defence;}
    void setStrength(int strength) {this->strength = strength;}
    void setDexterity(int dexterity) {this->dexterity = dexterity;}
    void setIntelligence(int intelligence) {this->intelligence = intelligence;}
    void setLuck(int luck) {this->luck = luck;}
    void setStatPoints(int statPoints) {this->statPoints = statPoints;}
    void setSkillPoints(int skillPoints) {this->skillPoints = skillPoints;}
    void setMoney(int money) {this->money = money;}
    void setName(std::string name) {this->name = name;}
    //void setInventory(Inventory Inventory) {this->inventory = inventory;}

    bool isAlive() const;
    int inflictDamage();
    void initialize(const std::string &name);
    void levelUp();
    void showStats();
    void increaseAttributes();
    void buyItem(std::unique_ptr<Item> &item);
};


int getNumber(const std::string &message);