#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "Item.hpp"

class Inventory {
private:
protected:
    std::vector<std::unique_ptr<Item>> inventory;
    int size;
public:
    void addItem(std::unique_ptr<Item> item);
    void showInventory();
};
