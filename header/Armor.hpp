#pragma once

#include "Item.hpp"

enum class ArmorType {
    HELMET = 1,
    CHESTPLATE,
    LEGGINGS,
    BOOTS
};

class Armor : public Item {
private:
    static constexpr const int DEFENCE_ADDED_PERCENTAGE = 10;
    static constexpr const char* def_name = "Unnamed Armor";
    static constexpr const char* def_status = "Unequipped";
    static constexpr const int def_purchase_price = 200;
    static constexpr const int def_sale_price = 160;
    static constexpr const int def_defence = 0;
    static constexpr const int def_level = 1;
    static constexpr int def_category = 2;
    static constexpr const int def_rarity = 1;
    static constexpr const int def_type = 0;
protected:
    int defence;
    ArmorType type;

    virtual void printStatus(std::ostream &os) const override;
    virtual void printLevel(std::ostream &os) const override;
    virtual void printRarity(std::ostream &os) const override;
public:
    Armor(const char* name = def_name, const char* status = def_status,
        int purchasePrice = def_purchase_price, int salePrice = def_sale_price, int level = def_level, int category = def_category, int rarity = def_rarity,
        int defence = def_defence, int type = def_type)
        :Item{ name, status, purchasePrice, salePrice, level, category, rarity }, defence{ defence }, type{ static_cast<ArmorType>(type) } {};
    Armor(const Armor &obj);
    virtual ~Armor() = default;

    ArmorType getType() const { return type; }
    int getDefence() const { return defence; }

    void setDefence(int defence) { this->defence = defence; }
    void setType(int type) { this->type = static_cast<ArmorType>(type); }

    virtual void upgrade() override;
    virtual void print(std::ostream &os) const override;
    
    virtual void writeToTxtFile(std::ofstream &outfile) const override;
    virtual void readFromTxtFile(std::ifstream &infile) override;

    bool operator==(const Armor &other) const;
};