#pragma once

#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>

class Entity {
private:
	static constexpr const char *def_name = "Unnamed Entity";
	static constexpr const int def_health = 100;
	static constexpr const int def_max_health = 100;
	static constexpr const int def_min_damage = 2;
	static constexpr const int def_max_damage = 5;
	static constexpr const int def_level = 1;
	static constexpr const int def_defence = 1;
protected:
	std::string name;
	int health, maxHealth;
	int minDamage, maxDamage;
	int level;
	int defence;
public:
	Entity(const char *name = def_name, int health = def_health, int maxHealth = def_max_health, 
		   int minDamage = def_min_damage, int maxDamage = def_max_damage, int level= def_level, int defence = def_defence) 
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

	int inflictDamage() const;
	void takeDamage(int damage);
	bool isAlive() const;
};

