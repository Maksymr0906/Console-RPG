#pragma once

#include <memory>
#include "Entity.hpp"
#include "Weapon.hpp"
#include "Armor.hpp"
#include "Product.hpp"

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
	int getDropChance() const { return dropChance; }

	//Modifiers
	void setDropChance(int dropChance) { this->dropChance = dropChance; }

	void readFromTxtFile(std::ifstream &infile);
	void writeToTxtFile(std::ofstream &outfile) const;
	std::shared_ptr<Item> getDroppedItem();
	void updateCharacteristics(int playerLevel);

	//Methods
	void print() const;
};

