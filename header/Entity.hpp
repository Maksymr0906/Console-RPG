#pragma once

#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>

class Entity {
private:

protected:
	std::string name;
	int health, maxHealth;
	int minDamage, maxDamage;
	int level;
	int defence;
public:
	Entity(std::string name, int health, int maxHealth, int minDamage, int maxDamage, int level, int defence) 
		: name{ name }, health{ health }, maxHealth{ maxHealth }, minDamage{ minDamage }, maxDamage{ maxDamage }, level{ level }, defence{ defence } {}
	virtual ~Entity() = default;
	
	void setName(std::string name) { this->name = name; }
	void setHealth(int health) { this->health = health; }
	void setMaxHealth(int maxHealth) { this->maxHealth = maxHealth; }
	void setMinDamage(int minDamage) { this->minDamage = minDamage; }
	void setMaxDamage(int maxDamage) { this->maxDamage = maxDamage; }
	void setLevel(int level) { this->level = level; }
	void setDefence(int defence) { this->defence = defence; }

	std::string getName() const { return this->name; }
	int getHealth() const { return this->health; }
	int getMaxHealth() const { return this->maxHealth; }
	int getMinDamage() const { return this->minDamage; }
	int getMaxDamage() const { return this->maxDamage; }
	int getLevel() const { return this->level; }
	int getDefence() const { return this->defence; }

	void writeToTxtFile(std::ofstream &outfile) const;
	void readFromTxtFile(std::ifstream &infile);

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
};

