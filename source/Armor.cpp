#include "Armor.hpp"

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

void Armor::writeToTxtFile(std::ofstream &outfile) const {
    Item::writeToTxtFile(outfile);
    outfile << defence << "\n"
            << type << "\n";
}

void Armor::readFromTxtFile(std::ifstream &infile) {
    Item::readFromTxtFile(infile);
    infile >> defence >> type;
}

bool Armor::operator==(const Armor &other) const {
    const Item &item1 = *this;
    const Item &item2 = other;

    return item1 == item2 &&
        defence == other.defence &&
        type == other.type;
}