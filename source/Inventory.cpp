#include "Inventory.hpp"

void Inventory::addItem(std::unique_ptr<Item> &item) {
    if(inventory.size() < sizeOfInventory) {
        inventory.push_back(std::move(item));
    }
    else {
        std::cout << "Not enough space in inventory for" << std::endl;
        std::cout << *item << std::endl;
    }
}

void Inventory::showInventory() {
    if(this->inventory.empty()) {
        std::cout << "Inventory is empty" << std::endl;
        return ;
    }
    std::cout << "INVENTORY" << std::endl;
    for(const auto &item: this->inventory) {
        std::cout << *item << std::endl;
    }
}

void Inventory::removeItem(int position) {
    if(position < 0 || position >= inventory.size()) {
        std::cout << "Invalid position" << std::endl;
    }
    else {
        inventory.erase(inventory.begin() + position);
    }
}

void Inventory::initialize() {
    this->sizeOfInventory = 10;
}

void Inventory::expand(int numberOfNewCells) {
    this->sizeOfInventory += numberOfNewCells;
}