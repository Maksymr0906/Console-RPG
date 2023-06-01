#include "Item.hpp"

void Item::equip() {
    this->status = "Equipped";
}

void Item::unequip() {
    this->status = "Unequipped";
}

void Item::use() {
    std::cout << "Item used" << std::endl;
}