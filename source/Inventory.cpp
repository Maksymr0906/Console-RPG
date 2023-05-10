#include "Inventory.hpp"

void Inventory::addItem(std::unique_ptr<Item> item) {
    inventory.push_back(std::move(item));
}

void Inventory::showInventory() {
    if(this->inventory.empty()) {
        std::cout << "Inventory is empty" << std::endl;
    }
    std::cout << "INVENTORY" << std::endl;
    for(const auto &item: this->inventory) {
        std::cout << item->getName() << " " << item->getCategory() << std::endl;
    }
}