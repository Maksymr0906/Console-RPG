#pragma once

#include <string>

class Item {
private:
    static constexpr const char *def_name = "Unnamed";
    static constexpr const char *def_category = "Uncategoried"; 
protected:
    int itemID;
    std::string name, category;
public:
    std::string get_name() {return name;}
    std::string get_category() {return category;}
    void set_name(const char *name) {this->name = name;}
    void set_category(const char *category) {this->category = category;}

    Item(const char *name = def_name, const char *category = def_category)
    :name{name}, category{category} {};
    ~Item(){};
};