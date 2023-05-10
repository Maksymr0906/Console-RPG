#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "Item.hpp"

class Inventory {
private:
protected:
    std::vector<std::unique_ptr<Item>> inventory;
public:
    void addItem(std::unique_ptr<Item> item);
    void showInventory();
};

void Inventory::addItem(std::unique_ptr<Item> item) {
    inventory.push_back(item);
}

void Inventory::showInventory() {
    std::cout << "INVENTORY" << std::endl;
    for(const auto &item: this->inventory) {
        std::cout << item->getName() << " " << item->getCategory() << std::endl;
    }
}