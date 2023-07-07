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

