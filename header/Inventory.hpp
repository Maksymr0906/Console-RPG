#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "Item.hpp"

class Inventory {
private:
protected:
    std::vector<std::shared_ptr<Item>> inventory;
    int sizeOfInventory;
public:

    std::vector<std::shared_ptr<Item>>& getInventory() { return inventory; }

    void addItem(std::shared_ptr<Item>& item);
    void showInventory();
    void removeItem(int position);
    void expand(int numberOfNewCells);
    void initialize();
};
