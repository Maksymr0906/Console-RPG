#include "Armor.hpp"

void Armor::writeToTxtFile(std::ofstream &outfile) const {
    Item::writeToTxtFile(outfile);
    outfile << defence << "\n"
        << static_cast<int>(type) << "\n";
}

void Armor::readFromTxtFile(std::ifstream &infile) {
    Item::readFromTxtFile(infile);
    int typeInt{};
    infile >> defence >> typeInt;
    type = static_cast<ArmorType>(typeInt);
}

void Armor::upgrade() {
    Item::upgrade();

    int defenceAdded = std::max(defence / DEFENCE_ADDED_PERCENTAGE, 1);
    defence += defenceAdded;

    std::cout << "I upgraded " << getName() << " and defence upgraded on " << defenceAdded << std::endl;
}

void Armor::print(std::ostream& os) const {
    Item::print(os);
    os << "\nType: ";
    if(type == ArmorType::HELMET)
        os << "Helmet";
    else if(type == ArmorType::CHESTPLATE)
        os << "Chestplate";
    else if(type == ArmorType::LEGGINGS)
        os << "Leggings";
    else if(type == ArmorType::BOOTS)
        os << "Boots";
    os << "\nDefence: " << this->defence << std::endl;
}

void Armor::printStatus(std::ostream &os) const {
    Item::printStatus(os);
}

void Armor::printLevel(std::ostream &os) const {
    Item::printLevel(os);
}

void Armor::printRarity(std::ostream &os) const {
    Item::printRarity(os);
}

Armor::Armor(const Armor &obj) 
    :Item(obj), defence{ obj.defence }, type{ obj.type } {
}

bool Armor::operator==(const Armor &other) const {
    return Item::operator==(other) &&
        defence == other.defence &&
        type == other.type;
}