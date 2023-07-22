#include "Entity.hpp"

void Entity::writeToTxtFile(std::ofstream &outfile) const {
	outfile << name << '\n';
	outfile << health << '\n';
	outfile << maxHealth << '\n';
	outfile << minDamage << '\n';
	outfile << maxDamage << '\n';
	outfile << level << '\n';
	outfile << defence << '\n';
}

void Entity::readFromTxtFile(std::ifstream &infile) {
	std::getline(infile, name);
	infile >> health;
	infile >> maxHealth;
	infile >> minDamage;
	infile >> maxDamage;
	infile >> level;
	infile >> defence;
}

int Entity::inflictDamage() const {
	int givenDamage{};
	givenDamage = rand() % (maxDamage - minDamage + 1) + minDamage;
	return givenDamage;
}

void Entity::takeDamage(int damage) {
	int effectiveDamage = std::max(damage - (defence / 3), 0);
	this->health = std::max(this->health - effectiveDamage, 0);
}

bool Entity::isAlive() const { 
	return health > 0; 
}
