#pragma once

#include "Item.hpp"

class Weapon : public Item {
private:
    static constexpr const char *def_name = "Unnamed";
    static constexpr const char *def_category = "Weapon"; 
    static constexpr const int def_purchase_price = 100;
    static constexpr const int def_sale_price = 80;
    static constexpr const int def_damage = 5;
protected:
    int damage;
public:
    Weapon(const char *name = def_name, const char *category = def_category, int purchasePrice = def_purchase_price, 
           int salePrice = def_sale_price, int damage = def_damage)
    :Item{name, category, purchasePrice, salePrice}, damage{damage} {};
    
};