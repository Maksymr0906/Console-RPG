#include "Item.hpp"

void Item::equip() {
    this->status = "Equipped";
}

void Item::unequip() {
    this->status = "Unequipped";
}

void Item::writeToTxtFile(std::ofstream &outfile) const {
    outfile << name << '\n'
            << category << '\n'
            << status << '\n'
            << purchasePrice << "\n"
            << salePrice << "\n"
            << level << "\n"
            << rarity << "\n";
}

void Item::readFromTxtFile(std::ifstream &infile) {
    std::getline(infile, name);
    std::getline(infile, category);
    std::getline(infile, status);
    infile >> purchasePrice >> salePrice >> level >> rarity;
}


void Item::serialize(std::ofstream &outfile) const {
    int nameLength = name.size();
    outfile.write(reinterpret_cast<const char *>(&nameLength), sizeof(nameLength));
    outfile.write(name.c_str(), nameLength);

    int categoryLength = category.size();
    outfile.write(reinterpret_cast<const char *>(&categoryLength), sizeof(categoryLength));
    outfile.write(category.c_str(), categoryLength);

    int statusLength = status.size();
    outfile.write(reinterpret_cast<const char *>(&statusLength), sizeof(statusLength));
    outfile.write(status.c_str(), statusLength);

    outfile.write(reinterpret_cast<const char *>(&purchasePrice), sizeof(purchasePrice));
    outfile.write(reinterpret_cast<const char *>(&salePrice), sizeof(salePrice));
    outfile.write(reinterpret_cast<const char *>(&level), sizeof(level));
    outfile.write(reinterpret_cast<const char *>(&rarity), sizeof(rarity));
}

void Item::deserialize(std::ifstream &infile) {
    int nameLength;
    infile.read(reinterpret_cast<char *>(&nameLength), sizeof(nameLength));
    char *nameBuffer = new char[nameLength + 1];
    infile.read(nameBuffer, nameLength);
    nameBuffer[nameLength] = '\0';
    name = nameBuffer;
    delete[] nameBuffer;

    int categoryLength;
    infile.read(reinterpret_cast<char *>(&categoryLength), sizeof(categoryLength));
    char *categoryBuffer = new char[categoryLength + 1];
    infile.read(categoryBuffer, categoryLength);
    categoryBuffer[categoryLength] = '\0';
    category = categoryBuffer;
    delete[] categoryBuffer;

    int statusLength;
    infile.read(reinterpret_cast<char *>(&statusLength), sizeof(statusLength));
    char *statusBuffer = new char[statusLength + 1];
    infile.read(statusBuffer, statusLength);
    statusBuffer[statusLength] = '\0';
    status = statusBuffer;
    delete[] statusBuffer;

    infile.read(reinterpret_cast<char *>(&purchasePrice), sizeof(purchasePrice));
    infile.read(reinterpret_cast<char *>(&salePrice), sizeof(salePrice));
    infile.read(reinterpret_cast<char *>(&level), sizeof(level));
    infile.read(reinterpret_cast<char *>(&rarity), sizeof(rarity));
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