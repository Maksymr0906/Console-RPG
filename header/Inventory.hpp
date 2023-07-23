#pragma once

#include <memory>
#include <vector>

#include "Functions.hpp"
#include "Armor.hpp"
#include "Weapon.hpp"
#include "Product.hpp"

class Inventory {
private:
    static constexpr const size_t def_max_number_of_items = 5;
protected:
    size_t maxNumberOfItems;
    std::vector<std::shared_ptr<Item>> items;
public:
    Inventory() :maxNumberOfItems{ def_max_number_of_items }, items{} {}

    void initialize();
    void addItem(std::shared_ptr<Item> &item);
    void printInventory() const;
    void removeItem(size_t position);
    void expand(const int &numberOfNewCells);
    bool is_empty() const { return items.empty(); }

    void writeToTxtFile(std::ofstream &outfile) const;
    void readFromTxtFile(std::ifstream &infile);

    size_t getMaxNumberOfItems() const { return maxNumberOfItems; }
    void setMaxNumberOfItems(int maxNumberOfItems) { this->maxNumberOfItems = maxNumberOfItems; }
    std::vector<std::shared_ptr<Item>> &getItems() { return items; }
};
