#include "Weapon.hpp"

void Weapon::equip() {
    Item::equip();
};

void Weapon::unequip() {
    Item::unequip();
}

void Weapon::print(std::ostream& os) const {
    os << "\nName: " << this->name << "\nCategory: " << this->category << "\nMin/Max Damage: "
        << this->minDamage << " / " << this->maxDamage << "\nStatus: " << this->status 
        << "\nPurchase/Sale price: " << this->purchasePrice << " / " << this->salePrice
        << "\nLevel: " << this->level << "\nRarity: " << this->rarity;
}

void Weapon::use(Entity &en) {
    std::cout << "Weapon used" << std::endl;
}

void Weapon::writeToTxtFile(std::ofstream &outfile) const {
    Item::writeToTxtFile(outfile);
    outfile << minDamage << "\n"
            << maxDamage << "\n";
}

void Weapon::readFromTxtFile(std::ifstream &infile) {
    Item::readFromTxtFile(infile);
    infile >> minDamage >> maxDamage;
}

void Weapon::serialize(std::ofstream &outfile) const {
    Item::serialize(outfile);
    outfile.write(reinterpret_cast<const char *>(&minDamage), sizeof(minDamage));
    outfile.write(reinterpret_cast<const char *>(&maxDamage), sizeof(maxDamage));
}

void Weapon::deserialize(std::ifstream &infile) {
    Item::deserialize(infile);
    infile.read(reinterpret_cast<char *>(&minDamage), sizeof(minDamage));
    infile.read(reinterpret_cast<char *>(&maxDamage), sizeof(maxDamage));
}

bool Weapon::operator==(const Weapon &other) const {
    const Item &item1 = *this;
    const Item &item2 = other;

    return item1 == item2 &&
        minDamage == other.minDamage &&
        maxDamage == other.maxDamage;
}