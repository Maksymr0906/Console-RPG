#include "Inventory.hpp"

void Inventory::addItem(std::shared_ptr<Item>& item) {
    if (inventory.size() < sizeOfInventory) {
        inventory.push_back(std::move(item));
        item.reset();
    }
    else {
        std::cout << "Not enough space in inventory for" << std::endl;
        std::cout << *item << std::endl;
    }
}

void Inventory::showInventory() {
    if (this->inventory.empty()) {
        std::cout << "\nInventory is empty" << std::endl;
        return;
    }
    std::cout << "\nYour inventory" << std::endl;
    for (size_t i = 0; i < this->inventory.size(); i++) {
        std::cout << "(" << i + 1 << ") - " << this->inventory.at(i)->getName() << std::endl;
    }
}

void Inventory::removeItem(int position) {
    if (position < 0 || position >= inventory.size()) {
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