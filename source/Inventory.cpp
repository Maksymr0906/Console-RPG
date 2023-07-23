#include "Inventory.hpp" 

void Inventory::initialize() {
    this->maxNumberOfItems = def_max_number_of_items;
}

void Inventory::addItem(std::shared_ptr<Item> &item) {
    if(items.size() < maxNumberOfItems)
        items.push_back(std::move(item));
    else
        std::cout << "Not enough space in inventory for " << item->getName() << std::endl;
}

void Inventory::printInventory() const {
    if(this->items.empty()) {
        std::cout << "\nMy inventory is empty" << std::endl;
        return;
    }
    std::cout << "\nMy inventory" << std::endl;
    std::cout << "(0) - Go back" << std::endl;
    for(size_t i = 0; i < this->items.size(); i++) {
        std::cout << "(" << i + 1 << ") - " << this->items.at(i)->getName();
        if(this->items.at(i)->getStatus() == "Equipped")
            std::cout << " (Equipped)";
        std::cout << std::endl;
    }
}

void Inventory::removeItem(size_t position) {
    if(position >= items.size())
        std::cout << "Invalid position" << std::endl;
    else
        items.erase(items.begin() + position);
}

void Inventory::expand(const int &numberOfNewCells) {
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
    int itemCategory{};
    size_t itemCount{};

    infile >> maxNumberOfItems;
    infile >> itemCount;

    for(size_t i = 0; i < itemCount; i++) {
        infile >> itemCategory;
        std::shared_ptr<Item> item;
        if(static_cast<Category>(itemCategory) == Category::WEAPON)
            item = std::make_shared<Weapon>();
        else if(static_cast<Category>(itemCategory) == Category::ARMOR)
            item = std::make_shared<Armor>();
        else if(static_cast<Category>(itemCategory) == Category::PRODUCT)
            item = std::make_shared<Product>();

        infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        item->readFromTxtFile(infile);
        addItem(item);
    }
}