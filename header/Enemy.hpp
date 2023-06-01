#pragma once

#include <cstdlib>

class Enemy {
private:
	static constexpr const int def_health = 10;
	static constexpr const int def_min_damage = 2;
	static constexpr const int def_max_damage = 5;
	static constexpr const int def_level = 1;
	static constexpr const int def_drop_chance = 20;
	static constexpr const int def_defence = 1;
protected:
	int maxHealth, health;
	int minDamage, maxDamage;
	int level;
	int dropChance;
	int defence;
public:
	Enemy();
	Enemy(int level);
	~Enemy() {};

	//Accessors
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

	//Methods
	int getDamage() {
		int givenDamage{};
		givenDamage = rand() % (maxDamage - minDamage + 1) + minDamage;
		return givenDamage;
	}
	void takeDamage(int damage) { health -= damage; }
	bool isAlive() { return health > 0; }
	
};

