#include "Armor.hpp"

void Armor::equip() {
    Item::equip();
}

void Armor::unequip() {
    Item::unequip();
}

void Armor::print(std::ostream& os) const {
    os << "\nArmor name: " << this->name << "\nCategory: " << this->category << "\nDefence: "
        << this->defence << "\nStatus: " << this->status;
}

Armor::Armor(const Armor &obj) 
    :Item(obj), defence{ obj.defence }, type{ obj.type } {
}

void Armor::use() {
    std::cout << "Armor used" << std::endl;
}