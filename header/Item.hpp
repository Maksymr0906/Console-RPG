#pragma once

#include "I_Printable.hpp"

#include <string>
#include <iostream>
class Item : public I_Printable {
private:
    static constexpr const char *def_name = "Unnamed";
    static constexpr const char *def_category = "Uncategoried"; 
    static constexpr const char *def_status = "Unequipped";
    static constexpr const int def_purchase_price = 100;
    static constexpr const int def_sale_price = 80;
protected:
    std::string name, category, status/*equiped or in inventory*/;
    int purchasePrice, salePrice;
public:
    std::string getName() const {return name;}
    std::string getCategory() const {return category;}
    int getPurchasePrice() const {return purchasePrice;}
    int getSalePrice() const {return salePrice;}

    void setName(const char *name) {this->name = name;}
    void setCategory(const char *category) {this->category = category;}
    void setPurchasePrice(int purchasePrice) {this->purchasePrice = purchasePrice;}
    void setSalePrice(int salePrice) {this->salePrice = salePrice;}

    Item(const char *name = def_name, const char *category = def_category, const char *status = def_status, int purchasePrice = def_purchase_price, int salePrice = def_sale_price)
    :name{name}, category{category}, status{status}, purchasePrice{purchasePrice}, salePrice{salePrice} {};
    virtual ~Item() = default;

    virtual void equip() = 0;
    virtual void unequip() = 0;
};