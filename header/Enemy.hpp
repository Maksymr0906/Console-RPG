#pragma once

#include "Entity.hpp"
#include "Weapon.hpp"
#include "Armor.hpp"
#include "Product.hpp"
#include <memory>

class Enemy : public Entity {
private:
	static constexpr const char *def_name = "Unnamed";
	static constexpr const int def_health = 100;
	static constexpr const int def_min_damage = 2;
	static constexpr const int def_max_damage = 5;
	static constexpr const int def_level = 1;
	static constexpr const int def_drop_chance = 20;
	static constexpr const int def_defence = 1;
protected:
	int dropChance;
	std::shared_ptr<Item> droppedItem;
public:
	Enemy();
	Enemy(int level);
	virtual ~Enemy() = default;

	//Accessors
	virtual std::string getName() const override { return this->name; }
	int getHealth() const { return health; }
	int getMaxHealth() const { return maxHealth; }
	int getMinDamage() const { return minDamage; }
	int getMaxDamage() const { return maxDamage; }
	int getLevel() const { return level; }
	int getDropChance() const { return dropChance; }
	int getDefence() const { return defence; }

	//Modifiers
	void setHealth(int health) { this->health = health; }
	void setMaxHealth(int maxHealth) { this->maxHealth = maxHealth; }
	void setMinDamage(int minDamage) { this->minDamage = minDamage; }
	void setMaxDamage(int maxDamage) { this->maxDamage = maxDamage; }
	void setLevel(int level) { this->level = level; }
	void setDropChance(int dropChance) { this->dropChance = dropChance; }
	void setDefence(int defence) { this->defence = defence; }
	void readFromTxtFile(std::ifstream &infile);
	void writeToTxtFile(std::ofstream &outfile) const;
	std::shared_ptr<Item> getDroppedItem();
	void updateCharacteristics(int playerLevel);

	//Methods
	int inflictDamage() {
		int givenDamage{};
		givenDamage = rand() % (maxDamage - minDamage + 1) + minDamage;
		return givenDamage;
	}
	void takeDamage(int damage) {
		int effectiveDamage = std::max(damage - (defence / 3), 0);
		this->health = std::max(this->health - effectiveDamage, 0);
	}
	bool isAlive() { return health > 0; }
	void print() const;
	
};

