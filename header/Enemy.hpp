#pragma once

#include <memory>
#include "Entity.hpp"
#include "Weapon.hpp"
#include "Armor.hpp"
#include "Product.hpp"

class Enemy : public Entity {
private:
	static constexpr const char *def_name = "Unnamed Enemy";
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
	Enemy(const char *name = def_name, int health = def_health, int maxHealth = def_health, int minDamage = def_min_damage, int maxDamage = def_max_damage,
		  int level = def_level, int defence = def_defence, int dropChance = def_drop_chance, std::shared_ptr<Item> droppedItem = nullptr) 
		: Entity { name, health, maxHealth, minDamage, maxDamage, level, defence }, dropChance{ dropChance }, droppedItem{ droppedItem } {}
	Enemy(int level);
	virtual ~Enemy() = default;

	int getDropChance() const { return dropChance; }
	void setDropChance(int dropChance) { this->dropChance = dropChance; }

	void readFromTxtFile(std::ifstream &infile);
	void writeToTxtFile(std::ofstream &outfile) const;
	void print() const;
	void updateCharacteristics(int playerLevel);
	std::shared_ptr<Item> getDroppedItem() const;
};

