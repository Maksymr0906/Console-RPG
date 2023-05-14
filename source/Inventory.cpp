#include "Inventory.hpp"

void Inventory::addItem(std::unique_ptr<Item> &item) {
    if(inventory.size() < sizeOfInventory) {
        inventory.push_back(std::move(item));
    }
    else {
        std::cout << "Not enough space in inventory for" << std::endl;
        std::cout << *item << std::endl;
    }
}

void Inventory::showInventory() {
    if(this->inventory.empty()) {
        std::cout << "Your inventory is empty" << std::endl;
        return ;
    }
    std::cout << "Your inventory" << std::endl;
    for(size_t i = 0; i < this->inventory.size(); i++) {
        std::cout << "(" << i+1 << ") - " << this->inventory.at(i)->getName() << std::endl; 
    }
    
    std::cout << "Select the corresponding number to read more about this item or " << this->inventory.size()+1 << " to go back: ";

    int choice{};
    std::cin >> choice;

    if(choice == this->inventory.size()+1) {
        return;
    }
    else {
        std::cout << *this->inventory.at(choice-1) << std::endl;
        this->showInventory();
    }
}

void Inventory::removeItem(int position) {
    if(position < 0 || position >= inventory.size()) {
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