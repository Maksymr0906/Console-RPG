#pragma once

#include <memory>
#include <vector>

#include "Functions.hpp"
#include "Armor.hpp"
#include "Weapon.hpp"
#include "Product.hpp"

class Inventory {
private:
protected:
    std::vector<std::shared_ptr<Item>> inventory;
    size_t sizeOfInventory;
public:
    Inventory();

    std::vector<std::shared_ptr<Item>> &getInventory() { return inventory; }

    void addItem(std::shared_ptr<Item> &item);
    void showInventory();
    void removeItem(int position);
    void expand(int numberOfNewCells);
    void initialize();
    bool is_empty() { return inventory.empty(); }

    void writeToTxtFile(std::ofstream &outfile) const;
    void readFromTxtFile(std::ifstream &infile);

    size_t getSizeOfInventory() const { return sizeOfInventory; }
    void setSizeOfInventory(int sizeOfInventory) { this->sizeOfInventory = sizeOfInventory; }
};
