#include "Option.hpp"

void backstory() {
    std::cout << "Zombie Project - a simple console game in which you have to survive in an unfair world full of zombies." << std::endl
              << "You come to your senses in an empty New York, which is full of zombies."                                 << std::endl
              << "All you have in your pockets is a knife, Coca-Kolya, and a loaf of bread."                               << std::endl
              << "For now, all you need is to survive, and how to achieve this depends on you."                            << std::endl
              << "So get up and don't waste a single moment on empty thoughts, otherwise you simply won't survive."        << std::endl;
}





Option getOption() {
    std::cout << "Enter your choice: ";
    int number{};
    std::cin >> number;
    
    return static_cast<Option>(number);
}