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

void Weapon::use() {
    std::cout << "Weapon used" << std::endl;
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