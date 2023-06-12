#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "Armor.hpp"
#include "Weapon.hpp"

class Inventory {
private:
protected:
    std::vector<std::shared_ptr<Item>> inventory;
    int sizeOfInventory;
public:
    Inventory();

    std::vector<std::shared_ptr<Item>>& getInventory() { return inventory; }

    void addItem(std::shared_ptr<Item>& item);
    void showInventory();
    void removeItem(int position);
    void expand(int numberOfNewCells);
    void initialize();
    bool is_empty() { return inventory.empty(); }

    void serialize(std::ofstream &outfile) const;
    void deserialize(std::ifstream &infile);
};
