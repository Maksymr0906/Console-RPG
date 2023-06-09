#pragma once

#include "Item.hpp"

class Armor : public Item {
private:
    static constexpr const char* def_name = "Unnamed";
    static constexpr const char* def_category = "Armor";
    static constexpr const char* def_status = "Unequipped";
    static constexpr const int def_purchase_price = 200;
    static constexpr const int def_sale_price = 160;
    static constexpr const int def_defence = 0;
    static constexpr const int def_level = 1;
    static constexpr const int def_rarity = 1;
    static constexpr const int def_type = 0;
    static constexpr const int def_item_type = 2;
protected:
    int defence;
    int type; //1 - head, 2 - chestplate, 3 - leggings, 4 - boots
public:
    Armor(const char* name = def_name, const char* category = def_category, const char* status = def_status,
        int purchasePrice = def_purchase_price, int salePrice = def_sale_price, int level = def_level, int rarity = def_rarity,
        int defence = def_defence, int type = def_type, int itemType = def_item_type)
        :Item{ name, category, status, purchasePrice, salePrice, level, rarity, itemType }, defence{ defence }, type{ type } {};
    Armor(const Armor &obj);
    virtual ~Armor() = default;

    virtual void equip() override;
    virtual void unequip() override;
    virtual void use(Entity &en) override;
    virtual void writeToTxtFile(std::ofstream &outfile) const override;
    virtual void readFromTxtFile(std::ifstream &infile) override;
    virtual void serialize(std::ofstream &outfile) const override;
    virtual void deserialize(std::ifstream &infile) override;
    virtual void print(std::ostream &os) const override;

    int getType() const { return type; }
    int getDefence() const { return defence; }

    bool operator==(const Armor &other) const;
};