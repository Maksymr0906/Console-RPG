#include "Option.hpp"

Option getOption() {
    std::cout << "Enter your choice: ";
    int number{};
    std::cin >> number;
    
    return static_cast<Option>(number);
}