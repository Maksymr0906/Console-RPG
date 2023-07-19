#include "Item.hpp"

void Item::equip() {
    this->status = "Equipped";
}

void Item::unequip() {
    this->status = "Unequipped";
}

void Item::writeToTxtFile(std::ofstream &outfile) const {
    outfile << name << '\n'
            << category << '\n'
            << status << '\n'
            << purchasePrice << "\n"
            << salePrice << "\n"
            << level << "\n"
            << rarity << "\n";
}

void Item::readFromTxtFile(std::ifstream &infile) {
    std::getline(infile, name);
    std::getline(infile, category);
    std::getline(infile, status);
    infile >> purchasePrice >> salePrice >> level >> rarity;
}

bool Item::operator==(const Item &other) const {
    return (name == other.name &&
            category == other.category &&
            status == other.status &&
            purchasePrice == other.purchasePrice &&
            salePrice == other.salePrice &&
            level == other.level &&
            rarity == other.rarity);
}