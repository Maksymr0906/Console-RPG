#include "Item.hpp"

void Item::writeToTxtFile(std::ofstream &outfile) const {
    outfile << name << '\n'
        << status << '\n'
        << purchasePrice << "\n"
        << salePrice << "\n"
        << level << "\n"
        << static_cast<int>(category) << '\n'
        << static_cast<int>(rarity) << "\n";
}

void Item::readFromTxtFile(std::ifstream &infile) {
    int rarityInt{}, categoryInt{};
    std::getline(infile, name);
    std::getline(infile, status);
    infile >> purchasePrice >> salePrice >> level >> categoryInt >> rarityInt;
    category = static_cast<Category>(categoryInt);
    rarity = static_cast<Rarity>(rarityInt);
}

void Item::equip() {
    this->status = "Equipped";
}

void Item::unequip() {
    this->status = "Unequipped";
}

void Item::upgrade() {
    int purchasePriceAdded = std::max(purchasePrice / UPGRADE_COST_PERCENTAGE, MIN_PURCHASE_PRICE_ADDED);
    int salePriceAdded = std::max(salePrice / UPGRADE_COST_PERCENTAGE, MIN_SALE_PRICE_ADDED);

    purchasePrice += purchasePriceAdded;
    salePrice += salePriceAdded;
    level++;
}

void Item::print(std::ostream &os) const {
    os << "\nName: " << this->name
       << "\nPurchase/Sale price: " << this->purchasePrice << " / " << this->salePrice;
    printCategory(os);
    printStatus(os);
    printLevel(os);
    printRarity(os);
}

void Item::printCategory(std::ostream &os) const {
    os << "\nCategory: ";
    if(category == Category::WEAPON)
        os << "Weapon";
    else if(category == Category::ARMOR)
        os << "Armor";
    else if(category == Category::PRODUCT)
        os << "Product";
}

void Item::printStatus(std::ostream &os) const {
    os << "\nStatus: " << this->status;
}

void Item::printLevel(std::ostream &os) const {
    os << "\nLevel: " << this->level;
}

void Item::printRarity(std::ostream &os) const {
    os << "\nRarity: ";
    if(rarity == Rarity::COMMON)
        os << "Common";
    if(rarity == Rarity::UNCOMMON)
        os << "Uncommon";
    if(rarity == Rarity::RARE)
        os << "Rare";
    if(rarity == Rarity::EPIC)
        os << "Epic";
    if(rarity == Rarity::LEGENDARY)
        os << "Legendary";
}

bool Item::operator==(const Item &other) const {
    return (name == other.name &&
            category == other.category &&
            status == other.status &&
            purchasePrice == other.purchasePrice &&
            salePrice == other.salePrice &&
            level == other.level &&
            rarity == other.rarity);
}