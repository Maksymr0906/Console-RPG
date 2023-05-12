#pragma once

#include "Item.hpp"

class Weapon : public Item {
private:
    static constexpr const char *def_name = "Unnamed";
    static constexpr const char *def_category = "Weapon"; 
    static constexpr const char *def_status = "Unequipped";
    static constexpr const int def_purchase_price = 100;
    static constexpr const int def_sale_price = 80;
    static constexpr const int def_min_damage = 5;
    static constexpr const int def_max_damage = 10;
protected:
    int minDamage, maxDamage/*, criticalHit*/;
public:
    Weapon(const char *name = def_name, const char *category = def_category, const char *status = def_status, 
           int purchasePrice = def_purchase_price, int salePrice = def_sale_price, 
           int minDamage = def_min_damage, int maxDamage = def_max_damage)
    :Item{name, category, status, purchasePrice, salePrice}, minDamage{minDamage}, maxDamage{maxDamage} {};
    
};