#pragma once

#include "I_Printable.hpp"

#include <fstream>
#include <string>
#include <iomanip>
#include <limits>

enum class Rarity {
    COMMON = 1,
    UNCOMMON,
    RARE,
    EPIC,
    LEGENDARY
};

enum class Category {
    WEAPON = 1,
    ARMOR,
    PRODUCT
};

class Item : public I_Printable {
private:
    static constexpr const int UPGRADE_COST_PERCENTAGE = 10;
    static constexpr const int MIN_PURCHASE_PRICE_ADDED = 80;
    static constexpr const int MIN_SALE_PRICE_ADDED = 40;
    static constexpr const char* def_name = "Unnamed Item";
    static constexpr const char* def_status = "Unequipped";
    static constexpr const int def_purchase_price = 100;
    static constexpr const int def_sale_price = 80;
    static constexpr const int def_level = 1;
    static constexpr const int def_category = 0;
    static constexpr const int def_rarity = 1;
protected:
    std::string name;
    std::string status; // Equipped or Unequipped
    int purchasePrice, salePrice;
    int level;
    Category category;
    Rarity rarity;
public:
    Item(const char *name = def_name, const char *status = def_status, int purchasePrice = def_purchase_price, int salePrice = def_sale_price, int level = def_level, int category = def_category, int rarity = def_rarity)
        :name{ name }, status{status}, purchasePrice{purchasePrice}, salePrice{salePrice}, level{level}, category{ static_cast<Category>(category) }, rarity{static_cast<Rarity>(rarity)} {};
    Item(const Item &obj)
        :name{ obj.name }, status{ obj.status }, purchasePrice{ obj.purchasePrice }, salePrice{ obj.salePrice }, level{ obj.level }, category{ obj.category }, rarity{ obj.rarity } {};
    virtual ~Item() = default;

    std::string getName() const { return name; }
    std::string getStatus() const { return status; }
    int getPurchasePrice() const { return purchasePrice; }
    int getSalePrice() const { return salePrice; }
    int getLevel() const { return level; }
    Category getCategory() const { return category; }
    Rarity getRarity() const { return rarity; }

    void setName(const char* name) { this->name = name; }
    void setStatus(const char *status) { this->status = status; }
    void setPurchasePrice(int purchasePrice) { this->purchasePrice = purchasePrice; }
    void setSalePrice(int salePrice) { this->salePrice = salePrice; }
    void setLevel(int level) { this->level = level; }
    void setCategory(Category category) { this->category = category; }
    void setRarity(Rarity rarity) { this->rarity = rarity; }

    void equip();
    void unequip();
    void printCategory(std::ostream &os) const;

    virtual void upgrade() = 0;
    virtual void print(std::ostream &os) const override = 0;
    virtual void printStatus(std::ostream &os) const = 0;
    virtual void printLevel(std::ostream &os) const = 0;
    virtual void printRarity(std::ostream &os) const = 0;

    virtual void writeToTxtFile(std::ofstream &outfile) const = 0;
    virtual void readFromTxtFile(std::ifstream &infile) = 0;

    bool operator==(const Item &other) const;
};