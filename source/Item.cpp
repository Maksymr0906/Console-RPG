#include "Item.hpp"

void Item::equip() {
    this->status = "Equipped";
}

void Item::unequip() {
    this->status = "Unequipped";
}

std::ostream &operator<<(std::ostream &os, const Item &item) {
    os << "Name [" << item.name << "]  Category [" << item.category 
       << "] Purchase price [" << item.purchasePrice << "] Sale price [" << item.salePrice << "]";

    return os;
}