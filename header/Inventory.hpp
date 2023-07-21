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
    std::vector<std::shared_ptr<Item>> items;
    size_t maxNumberOfItems;
public:
    Inventory();

    std::vector<std::shared_ptr<Item>> &getItems() { return items; }

    void addItem(std::shared_ptr<Item> &item);
    void showInventory();
    void removeItem(size_t position);
    void expand(int numberOfNewCells);
    void initialize();
    bool is_empty() { return items.empty(); }

    void writeToTxtFile(std::ofstream &outfile) const;
    void readFromTxtFile(std::ifstream &infile);

    size_t getMaxNumberOfItems() const { return maxNumberOfItems; }
    void setMaxNumberOfItems(int maxNumberOfItems) { this->maxNumberOfItems = maxNumberOfItems; }
};
