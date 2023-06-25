#include "Armor.hpp"

void Armor::equip() {
    Item::equip();
}

void Armor::unequip() {
    Item::unequip();
}

void Armor::print(std::ostream& os) const {
    os << "\nName: " << this->name << "\nCategory: " << this->category << "\nDefence: "
        << this->defence << "\nStatus: " << this->status
        << "\nPurchase/Sale price: " << this->purchasePrice << " / " << this->salePrice
        << "\nType: ";
    if(type == 1) {
        os << "Helmet";
    }
    else if(type == 2) {
        os << "Chestplate";
    }
    else if(type == 3) {
        os << "Leggings";
    }
    else if(type == 4) {
        os << "Boots";
    }
    os << "\nLevel: " << this->level << "\nRarity: " << this->rarity;
}

Armor::Armor(const Armor &obj) 
    :Item(obj), defence{ obj.defence }, type{ obj.type } {
}

void Armor::use() {
    std::cout << "Armor used" << std::endl;
}


void Armor::serialize(std::ofstream &outfile) const {
    Item::serialize(outfile);
    outfile.write(reinterpret_cast<const char *>(&defence), sizeof(defence));
    outfile.write(reinterpret_cast<const char *>(&type), sizeof(type));
}

void Armor::deserialize(std::ifstream &infile) {
    Item::deserialize(infile);
    infile.read(reinterpret_cast<char *>(&defence), sizeof(defence));
    infile.read(reinterpret_cast<char *>(&type), sizeof(type));
}

bool Armor::operator==(const Armor &other) const {
    const Item &item1 = *this;
    const Item &item2 = other;

    return item1 == item2 &&
        defence == other.defence &&
        type == other.type;
}