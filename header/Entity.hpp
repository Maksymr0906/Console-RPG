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
	virtual std::string getName() const = 0;

	void writeToTxtFile(std::ofstream &outfile) const;
	void readFromTxtFile(std::ifstream &infile);
};

