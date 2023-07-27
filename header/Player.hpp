#pragma once

#include <ctime>
#include <map>

#include "Inventory.hpp"
#include "Entity.hpp"


enum class AttributeChoice {
    STRENGTH = 1,
    VITALITY,
    DEXTERITY,
    INTELLIGENCE,
    LUCK
};


class Player : public Entity {
private:
    static constexpr const int MAX_RADIATION = 15;
    static constexpr const int RADIATION_THRESHOLD = 10;
    static constexpr const int MIN_ATTRIBUTE_VALUE = 0;
    static constexpr const int MIN_ATTRIBUTE_VALUE_FOR_SLEEP = 40;
    static constexpr const int HIGH_RADIATION_REDUCTION = 10;
    static constexpr const int MIN_EXP_GAIN = 5;
    static constexpr const int MAX_EXP_GAIN = 10;
    static constexpr const int MIN_MONEY_GAIN = 20;
    static constexpr const int MAX_MONEY_GAIN = 30;
    static constexpr const int STAT_POINTS_PER_LEVEL = 5;
    static constexpr const int ATTRIBUTE_BONUS_FACTOR = 2;
    static constexpr const int ATTRIBUTE_BASE_VALUE = 5;

    static constexpr const char *def_name = "Unnamed Player";
    static constexpr const int def_health = 100;
    static constexpr const int def_max_health = 100;
    static constexpr const int def_min_damage = 2;
    static constexpr const int def_max_damage = 5;
    static constexpr const int def_level = 1;
    static constexpr const int def_defence = 1;
    static constexpr const int def_thirst = 100;
    static constexpr const int def_thirst_max = 100;
    static constexpr const int def_hunger = 100;
    static constexpr const int def_hunger_max = 100;
    static constexpr const int def_exp = 0;
    static constexpr const int def_exp_next = 100;
    static constexpr const int def_stamina = 100;
    static constexpr const int def_stamina_max = 100;
    static constexpr const int def_strength = 5;
    static constexpr const int def_vitality = 5;
    static constexpr const int def_dexterity = 5;
    static constexpr const int def_intelligence = 5;
    static constexpr const int def_luck = 1;
    static constexpr const int def_stat_points = 0;
    static constexpr const int def_skill_points = 0;
    static constexpr const int def_money = 30;
    static constexpr const int def_radiation = 0;
    static constexpr const int def_distance_travelled = 0;
    const std::shared_ptr<Item> def_weapon = std::make_shared<Weapon>("None");
    const std::shared_ptr<Item> def_armor = std::make_shared<Armor>("None");

    //Methods
    void decreaseVitalAttribute(int &attribute, int amount);
    void printLevelUpMessage() const;
    void restoreVitalAttributes();
    void printAttributeOptions() const;
    void increaseStatAttribute(int &attribute, const std::string &attributeName);
    void updateCharacteristics();
    int calculateAttributeBonus(const int &attribute) const;
    void equipItem(std::shared_ptr<Item> &item);
    void equipWeapon(std::shared_ptr<Item> &item);
    void equipArmor(std::shared_ptr<Item> &item);
    void unequipItem(std::shared_ptr<Item> &item);
    void unequipWeapon(std::shared_ptr<Item> &item);
    void unequipArmor(std::shared_ptr<Item> &item);
protected:
    int thirst, thirstMax;
    int hunger, hungerMax;
    int exp, expNext;
    int stamina, staminaMax;
    int strength, vitality, dexterity, intelligence;
    int luck;
    int statPoints, skillPoints;
    int money;
    int radiation;
    int distanceTravelled;
    Inventory inventory;
    std::shared_ptr<Item> weapon;
    std::shared_ptr<Item> armorHead;
    std::shared_ptr<Item> armorChest;
    std::shared_ptr<Item> armorLeggs;
    std::shared_ptr<Item> armorBoots;
public:
    //Constructors
    Player();
    virtual ~Player() = default;

    //Accessors
    int getExp() const { return exp; }
    int getExpNext() const { return expNext; }
    int getStamina() const { return stamina; }
    int getStaminaMax() const { return staminaMax; }
    int getHunger() const { return hunger; }
    int getHungerMax() const { return hungerMax; }
    int getThirst() const { return thirst; }
    int getThirstMax() const { return thirstMax; }
    int getRadiation() const { return radiation; }
    int getStrength() const { return strength; }
    int getDexterity() const { return dexterity; }
    int getIntelligence() const { return intelligence; }
    int getLuck() const { return luck; }
    int getStatPoints() const { return statPoints; }
    int getSkillPoints() const { return skillPoints; }
    int getMoney() const { return money; }
    Inventory &getInventory() { return inventory; }
    int getDistanceTravelled() const { return distanceTravelled; }

    //Modifiers
    void setExp(int exp) { this->exp = exp; }
    void setExpNext(int expNext) { this->expNext = expNext; }
    void setStamina(int stamina) { this->stamina = stamina; }
    void setStaminaMax(int staminaMax) { this->staminaMax = staminaMax; }
    void setHunger(int hunger) { this->hunger = hunger; }
    void setThirst(int thirst) { this->thirst = thirst; }
    void setRadiation(int radiation) { this->radiation = radiation; }
    void setStrength(int strength) { this->strength = strength; }
    void setDexterity(int dexterity) { this->dexterity = dexterity; }
    void setIntelligence(int intelligence) { this->intelligence = intelligence; }
    void setLuck(int luck) { this->luck = luck; }
    void setStatPoints(int statPoints) { this->statPoints = statPoints; }
    void setSkillPoints(int skillPoints) { this->skillPoints = skillPoints; }
    void setMoney(int money) { this->money = money; }
    void setDistanceTravelled(int distanceTravelled) { this->distanceTravelled = distanceTravelled; }

    //Methods
    void initialize(const std::string &name);
    void writeToTxtFile(std::ofstream &outfile) const;
    void readFromTxtFile(std::ifstream &infile);
    
    void printStats() const;
    void previewPlayer() const;
    void sleep();
    void explore();
    void levelUp();
    void increaseStatAttributes();
    bool buyItem(std::shared_ptr<Item> &item);
    void sellItem(const int &position);
    void useProduct(std::shared_ptr<Item> &item);
    void restoreStaminaInCombat();
    void upgradeItem();
    void printInventory();
    bool useItemInCombat();

    //Overloaded operators
    bool operator==(const Player &rhs) const;
    Player &operator=(const Player &rhs);
};