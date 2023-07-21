#include "Inventory.hpp"

Inventory::Inventory() {
    this->maxNumberOfItems = 5;
}

void Inventory::initialize() {
    this->maxNumberOfItems = 5;
}

void Inventory::addItem(std::shared_ptr<Item> &item) {
    if(items.size() < maxNumberOfItems) {
        items.push_back(std::move(item));
    }
    else {
        std::cout << "Not enough space in inventory for " << item->getName() << std::endl;
    }
}

void Inventory::showInventory() {
    if(this->items.empty()) {
        std::cout << "\nInventory is empty" << std::endl;
        return;
    }
    std::cout << "\nYour inventory" << std::endl;
    std::cout << "(0) - Go back" << std::endl;
    for(size_t i = 0; i < this->items.size(); i++) {
        std::cout << "(" << i + 1 << ") - " << this->items.at(i)->getName();
        if(this->items.at(i)->getStatus() == "Equipped") {
            std::cout << " (Equipped)";
        }
        std::cout << std::endl;
    }
}

void Inventory::removeItem(size_t position) {
    if(position >= items.size()) {
        std::cout << "Invalid position" << std::endl;
    }
    else {
        items.erase(items.begin() + position);
    }
}

void Inventory::expand(int numberOfNewCells) {
    this->maxNumberOfItems += numberOfNewCells;
}

void Inventory::writeToTxtFile(std::ofstream &outfile) const {
    outfile << maxNumberOfItems << "\n";
    outfile << items.size() << "\n";

    for(const auto &item : items) {
        int itemCategory = static_cast<int>(item->getCategory());
        outfile << itemCategory << '\n';
        item->writeToTxtFile(outfile);
    }
}

void Inventory::readFromTxtFile(std::ifstream &infile) {
    infile >> maxNumberOfItems;

    size_t itemCount{};
    infile >> itemCount;
    int itemCategory{};
    for(size_t i = 0; i < itemCount; i++) {
        infile >> itemCategory;
        std::shared_ptr<Item> item;
        if(itemCategory == 1) {
            item = std::make_shared<Weapon>();
        }
        else if(itemCategory == 2) {
            item = std::make_shared<Armor>();
        }
        else if(itemCategory == 3) {
            item = std::make_shared<Product>();
        }
        infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        item->readFromTxtFile(infile);
        addItem(item);
    }
}