#pragma once

#include <ctime>
#include <cstdlib>

#include "Inventory.hpp"
#include "Weapon.hpp"
#include "Armor.hpp"

class Player {
private:
    static constexpr const int def_health = 10;
    static constexpr const int def_max_health = 10;
    static constexpr const int def_min_damage = 2;
    static constexpr const int def_max_damage = 5;
    static constexpr const int def_exp = 0;
    static constexpr const int def_exp_next = 100;
    static constexpr const int def_level = 1;
    static constexpr const char* def_name = "Unnamed";
    static constexpr const int def_stamina = 10;
    static constexpr const int def_stamina_max = 10;
    static constexpr const int def_defence = 1;
    static constexpr const int def_strength = 5;
    static constexpr const int def_vitality = 5;
    static constexpr const int def_dexterity = 5;
    static constexpr const int def_intelligence = 5;
    static constexpr const int def_luck = 1;
    static constexpr const int def_stat_points = 0;
    static constexpr const int def_skill_points = 0;
    static constexpr const int def_money = 30;
    const std::shared_ptr<Item> def_weapon = std::make_shared<Weapon>("None");
    const std::shared_ptr<Item> def_armor = std::make_shared<Armor>("None");
    static constexpr const int def_distance_travelled = 0;
protected:
    std::string name;
    int health, maxHealth;
    int minDamage, maxDamage;
    int exp, expNext, level;
    int stamina, staminaMax;
    int defence;
    int strength, vitality, dexterity, intelligence;
    int luck;
    int statPoints, skillPoints;
    int money;
    //int radiation;
    Inventory inventory;
    std::shared_ptr<Item> weapon;
    std::shared_ptr<Item> armorHead;
    std::shared_ptr<Item> armorChest;
    std::shared_ptr<Item> armorLeggs;
    std::shared_ptr<Item> armorBoots;
    int distanceTravelled;
public:
    //Constructors
    Player();

    //Accessors
    int getHealth() const { return health; }
    int getMaxHealth() const { return maxHealth; }
    int getMinDamage() const { return minDamage; }
    int getMaxDamage() const { return maxDamage; }
    int getExp() const { return exp; }
    int getExpNext() const { return expNext; }
    int getLevel() const { return level; }
    int getStamina() const { return stamina; }
    int getStaminaMax() const { return staminaMax; }
    int getDefence() const { return defence; }
    int getStrength() const { return strength; }
    int getDexterity() const { return dexterity; }
    int getIntelligence() const { return intelligence; }
    int getLuck() const { return luck; }
    int getStatPoints() const { return statPoints; }
    int getSkillPoints() const { return skillPoints; }
    int getMoney() const { return money; }
    std::string getName() const { return name; }
    Inventory& getInventory() { return inventory; }
    int getDistanceTravelled() const { return distanceTravelled; }

    //Modifiers
    void setHealth(int health) { this->health = health; }
    void setMaxHealth(int maxHealth) { this->maxHealth = maxHealth; }
    void setMinDamage(int minDamage) { this->minDamage = minDamage; }
    void setMaxDamage(int maxDamage) { this->maxDamage = maxDamage; }
    void setExp(int exp) { this->exp = exp; }
    void setExpNext(int expNext) { this->expNext = expNext; }
    void setLevel(int level) { this->level = level; }
    void setStamina(int stamina) { this->stamina = stamina; }
    void setStaminaMax(int staminaMax) { this->staminaMax = staminaMax; }
    void setDefence(int defence) { this->defence = defence; }
    void setStrength(int strength) { this->strength = strength; }
    void setDexterity(int dexterity) { this->dexterity = dexterity; }
    void setIntelligence(int intelligence) { this->intelligence = intelligence; }
    void setLuck(int luck) { this->luck = luck; }
    void setStatPoints(int statPoints) { this->statPoints = statPoints; }
    void setSkillPoints(int skillPoints) { this->skillPoints = skillPoints; }
    void setMoney(int money) { this->money = money; }
    void setName(std::string name) { this->name = name; }
    void setDistanceTravelled(int distanceTravelled) { this->distanceTravelled = distanceTravelled; }
    //void setInventory(Inventory Inventory) {this->inventory = inventory;}

    //Methods
    int getValidAttributeChoice() const;
    bool isAlive() const;
    int inflictDamage();
    void initialize(const std::string &name);
    void levelUp();
    void showStats();
    void increaseAttributes();
    bool buyItem(std::shared_ptr<Item> &item);
    void equipItem(std::shared_ptr<Item> &item);
    void unequipItem(std::shared_ptr<Item> &item);
    void showInventory();
    void updateCharacteristics();
    void explore() { distanceTravelled++; }
    void showEquipment();
    std::string getAsString() const;
    bool serialize(std::ofstream &outfile) const;
    bool deserialize(std::ifstream &infile);
    void previewPlayer() const;

    //Overloaded operators
    bool operator==(const Player &rhs) const;
    Player &operator=(const Player &rhs);
};


int getNumber(const std::string& message);
void shop(Player& p);
void weaponShop(Player& p);
void armorShop(Player& p);
void potionShop(Player& p);