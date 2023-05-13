#include "Weapon.hpp"

void Weapon::equip() {
    status = "Equipped";
};
    
void Weapon::unequip() {
    status = "Unequipped";
}

void Weapon::print(std::ostream &os) const {
    os << "Weapon name: " << this->name << " Category: " << this->category << " Min/Max Damage: " 
       << this->minDamage << " / " << this->maxDamage << " Status: " << this->status;
}