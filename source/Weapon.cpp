#include "Weapon.hpp"

void Weapon::writeToTxtFile(std::ofstream &outfile) const {
    Item::writeToTxtFile(outfile);
    outfile << minDamage << "\n"
        << maxDamage << "\n";
}

void Weapon::readFromTxtFile(std::ifstream &infile) {
    Item::readFromTxtFile(infile);
    infile >> minDamage >> maxDamage;
}

void Weapon::print(std::ostream& os) const {
    Item::print(os);
    std::cout << "\nMin/Max damage: " << this->minDamage << " / " << this->maxDamage << std::endl;
}

void Weapon::printStatus(std::ostream &os) const {
    Item::printStatus(os);
}

void Weapon::printLevel(std::ostream &os) const {
    Item::printLevel(os);
}

void Weapon::printRarity(std::ostream &os) const {
    Item::printRarity(os);
}

bool Weapon::operator==(const Weapon &other) const {
    return Item::operator==(other) &&
        minDamage == other.minDamage &&
        maxDamage == other.maxDamage;
}