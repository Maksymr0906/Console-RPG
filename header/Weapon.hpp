#pragma once

#include "Item.hpp"

class Weapon : public Item {
private:
    static constexpr const char* def_name = "Unnamed";
    static constexpr const char* def_category = "Weapon";
    static constexpr const char* def_status = "Unequipped";
    static constexpr const int def_purchase_price = 100;
    static constexpr const int def_sale_price = 80;
    static constexpr const int def_min_damage = 5;
    static constexpr const int def_max_damage = 10;
    static constexpr const int def_level = 1;
    static constexpr const int def_rarity = 1;
    static constexpr const int def_item_type = 1;
protected:
    int minDamage, maxDamage;
public:
    Weapon(const char* name = def_name, const char* category = def_category, const char* status = def_status,
        int purchasePrice = def_purchase_price, int salePrice = def_sale_price,
        int minDamage = def_min_damage, int maxDamage = def_max_damage, int level = def_level, int rarity = def_rarity, int itemType = def_item_type)
        :Item{ name, category, status, purchasePrice, salePrice, level, rarity, itemType}, minDamage{ minDamage }, maxDamage{ maxDamage } {};

    Weapon(const Weapon &other)
        : Item(other), minDamage(other.minDamage), maxDamage(other.maxDamage) {}

    virtual ~Weapon() = default;

    int getMinDamage() const { return minDamage; }
    int getMaxDamage() const { return maxDamage; }

    void setMinDamage(int minDamage) { this->minDamage = minDamage; }
    void setMaxDamage(int maxDamage) { this->maxDamage = maxDamage; }

    virtual void equip() override;
    virtual void unequip() override;
    virtual void use(Entity &en) override;
    virtual void writeToTxtFile(std::ofstream &outfile) const override;
    virtual void readFromTxtFile(std::ifstream &infile) override;
    virtual void serialize(std::ofstream &outfile) const override;
    virtual void deserialize(std::ifstream &infile) override;
    virtual void print(std::ostream &os) const override;

    bool operator==(const Weapon &other) const;
};