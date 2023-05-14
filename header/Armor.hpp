#pragma once

#include "Item.hpp"

class Armor {
private:
    static constexpr const char *def_name = "Unnamed";
    static constexpr const char *def_category = "Armor"; 
    static constexpr const char *def_status = "Unequipped";
    static constexpr const int def_purchase_price = 200;
    static constexpr const int def_sale_price = 160;
    static constexpr const int def_defence = 5;
protected:
    int defence;
public:
    virtual ~Armor() = default;
};