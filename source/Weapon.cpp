#include "Weapon.hpp"

void Weapon::equip() {
    Item::equip();
};

void Weapon::unequip() {
    Item::unequip();
}

void Weapon::print(std::ostream& os) const {
    os << "\nWeapon name: " << this->name << "\nCategory: " << this->category << "\nMin/Max Damage: "
        << this->minDamage << " / " << this->maxDamage << "\nStatus: " << this->status;
}