#pragma once

#include "I_Printable.hpp"
#include "Entity.hpp"

#include <iostream>
#include <iomanip>
#include <fstream>

class Item : public I_Printable {
private:
    static constexpr const char* def_name = "Unnamed";
    static constexpr const char* def_category = "Uncategoried";
    static constexpr const char* def_status = "Unequipped";
    static constexpr const int def_purchase_price = 100;
    static constexpr const int def_sale_price = 80;
    static constexpr const int def_level = 1;
    static constexpr const int def_rarity = 1;
    static constexpr const int def_item_type = 0; //delete this or catecory
protected:
    std::string name, category, status/*equiped or in inventory*/;
    int purchasePrice, salePrice;
    int level, rarity;//1 - Common, 2 - Uncommon, 3 - Rare, 4 - Epic, 5 - Legendary
    int itemType; //1 - Weapon, 2 - Armor, 3 - Products
public:
    //Accesors
    std::string getName() const { return name; }
    std::string getCategory() const { return category; }
    std::string getStatus() const { return status; }
    int getPurchasePrice() const { return purchasePrice; }
    int getSalePrice() const { return salePrice; }
    int getLevel() const { return level; }
    int getRarity() const { return rarity; }
    int getItemType() const { return itemType; }

    //Modifiers
    void setName(const char* name) { this->name = name; }
    void setCategory(const char* category) { this->category = category; }
    void setPurchasePrice(int purchasePrice) { this->purchasePrice = purchasePrice; }
    void setSalePrice(int salePrice) { this->salePrice = salePrice; }
    void setLevel(int level) { this->level = level; }
    void setRarity(int rarity) { this->rarity = rarity; }
    void setStatus(const char* status) { this->status = status; }
    void setItemType(int itemType) { this->itemType = itemType; }

    Item(const char* name = def_name, const char* category = def_category, const char* status = def_status, int purchasePrice = def_purchase_price, int salePrice = def_sale_price, int level = def_level, int rarity = def_rarity, int itemType = def_item_type)
        :name{ name }, category{ category }, status{ status }, purchasePrice{ purchasePrice }, salePrice{ salePrice }, level{ level }, rarity{ rarity }, itemType{ itemType } {};
    Item(const Item &obj)
        :name{ obj.name }, category{ obj.category }, status{ obj.status }, purchasePrice{ obj.purchasePrice }, salePrice{ obj.salePrice }, level{ obj.level }, rarity{ obj.rarity }, itemType{obj.itemType} {};
    
    virtual ~Item() = default;

    virtual void equip() = 0;
    virtual void unequip() = 0;
    virtual void use(Entity &en) = 0;
    virtual void writeToTxtFile(std::ofstream &outfile) const = 0;
    virtual void readFromTxtFile(std::ifstream &infile) = 0;
    virtual void serialize(std::ofstream &outfile) const = 0;
    virtual void deserialize(std::ifstream &infile) = 0;
    bool operator==(const Item &other) const;
};