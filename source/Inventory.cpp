#include "Inventory.hpp"

Inventory::Inventory() {
    this->sizeOfInventory = 5;
}

void Inventory::initialize() {
    this->sizeOfInventory = 5;
}

void Inventory::addItem(std::shared_ptr<Item> &item) {
    if(inventory.size() < sizeOfInventory) {
        inventory.push_back(std::move(item));
        item.reset();
    }
    else {
        std::cout << "Not enough space in inventory for" << std::endl;
        std::cout << *item << std::endl;
    }
}

void Inventory::showInventory() {
    if(this->inventory.empty()) {
        std::cout << "\nInventory is empty" << std::endl;
        return;
    }
    std::cout << "\nYour inventory" << std::endl;
    std::cout << "(0) - Go back" << std::endl;
    for(size_t i = 0; i < this->inventory.size(); i++) {
        std::cout << "(" << i + 1 << ") - " << this->inventory.at(i)->getName();
        if(this->inventory.at(i)->getStatus() == "Equipped") {
            std::cout << " (Equipped)";
        }
        std::cout << std::endl;
    }
}

void Inventory::removeItem(int position) {
    if(position < 0 || position >= inventory.size()) {
        std::cout << "Invalid position" << std::endl;
    }
    else {
        inventory[position].reset();
        inventory.erase(inventory.begin() + position);
    }
}

void Inventory::expand(int numberOfNewCells) {
    this->sizeOfInventory += numberOfNewCells;
}

void Inventory::writeToTxtFile(std::ofstream &outfile) const {
    outfile << sizeOfInventory << "\n";
    outfile << inventory.size() << "\n";

    for(const auto &item : inventory) {
        std::string itemCategory = item->getCategory();
        outfile << itemCategory << '\n';
        item->writeToTxtFile(outfile);
    }
}

void Inventory::readFromTxtFile(std::ifstream &infile) {
    infile >> sizeOfInventory;
    
    int itemCount{};
    infile >> itemCount;
    std::string itemCategory{};
    for(size_t i = 0; i < itemCount; i++) {
        infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(infile, itemCategory);
        std::shared_ptr<Item> item;
        if(itemCategory == "Weapon") {
            item = std::make_shared<Weapon>();
        }
        else if(itemCategory == "Armor") {
            item = std::make_shared<Armor>();
        }
        else if(itemCategory == "Product") {
            item = std::make_shared<Product>();
        }
        item->readFromTxtFile(infile);
        addItem(item);
    }
}

void Inventory::serialize(std::ofstream &outfile) const {
    outfile.write(reinterpret_cast<const char *>(&sizeOfInventory), sizeof(sizeOfInventory));

    size_t itemCount = inventory.size();
    outfile.write(reinterpret_cast<const char *>(&itemCount), sizeof(itemCount));

    for(const auto &item : inventory) {
        int itemType = item->getItemType();
        outfile.write(reinterpret_cast<const char *>(&itemType), sizeof(itemType));
        item->serialize(outfile);
    }
}

void Inventory::deserialize(std::ifstream &infile) {
    infile.read(reinterpret_cast<char *>(&sizeOfInventory), sizeof(sizeOfInventory));

    size_t itemCount;
    infile.read(reinterpret_cast<char *>(&itemCount), sizeof(itemCount));
    int typeOfItem{};
    for(size_t i = 0; i < itemCount; i++) {
        infile.read(reinterpret_cast<char *>(&typeOfItem), sizeof(typeOfItem));

        std::shared_ptr<Item> item;
        if(typeOfItem == 1) {
            item = std::make_shared<Weapon>();
        }
        else if(typeOfItem == 2) {
            item = std::make_shared<Armor>();
        }
        else if(typeOfItem == 3) {
            item = std::make_shared<Product>();
        }
        item->deserialize(infile);
        addItem(item);
    }
}