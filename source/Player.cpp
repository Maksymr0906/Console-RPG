#include "Player.hpp"

Player::Player()
:   name{def_name},
    health{def_health},
    maxHealth{def_health},
    minDamage{def_min_damage},
    maxDamage{def_max_damage},
    exp{def_exp},
    expNext{def_exp_next},
    level{def_level},
    stamina{def_stamina},
    staminaMax{def_stamina_max},
    defence{def_defence},
    strength{def_strength},
    dexterity{def_dexterity},
    intelligence{def_intelligence},
    luck{def_luck},
    statPoints{def_stat_points},
    skillPoints{def_skill_points},
    money{def_money} {
}

bool Player::isAlive() const {
    return health > 0 ? true : false; 
}

int Player::inflictDamage() {
    int givenDamage{};

    givenDamage = rand() % (maxDamage - minDamage + 1) + minDamage;

    return givenDamage;
}

void Player::initialize(const std::string &name) {
    this->name = name;
    this->health = def_health;
    this->maxHealth = def_health;
    this->minDamage = def_min_damage;
    this->maxDamage = def_max_damage;
    this->exp = def_exp;
    this->expNext = def_exp_next;
    this->level = def_level;
    this->stamina = def_stamina;
    this->staminaMax = def_stamina_max;
    this->defence = def_defence;
    this->strength = def_strength;
    this->dexterity = def_dexterity;
    this->intelligence = def_intelligence;
    this->luck = def_luck;
    this->statPoints = def_stat_points;
    this->skillPoints = def_skill_points;
    this->money = def_money;
    inventory.initialize();
}

void Player::levelUp() {
    if(exp >= expNext) {
        level++;
        exp -= expNext;

        expNext = def_exp_next * (level - 1) + def_exp_next * (level - 1) * 0.5;
        skillPoints++;
        statPoints += 5;
        std::cout << "\nCongratulations, you are now " << this->level << " level!" << std::endl;
    }
    else {
        std::cout << "\nYou don't have enough experience" << std::endl;
    }
}

void Player::showStats() {
    std::cout << std::endl << "/* Player stats */" << std::endl
              << "Name: "                    << this->name << std::endl
              << "Level: "                   << this->level << std::endl
              << "XP: "                      << this->exp << " / " << this->expNext << std::endl
              << "Health: "                  << this->health << " / " << this->maxHealth << std::endl
              << "Stamina: "                 << this->stamina << " / " << this->staminaMax << std::endl
              << "Damage: "                  << this->minDamage << " - " << this->maxDamage << std::endl
              << "Defence: "                 << this->defence << std::endl
              << std::endl
              << "/* Player Atributtes */"   << std::endl
              << "Strength: "                << this->strength << std::endl
              << "Dexterity: "               << this->dexterity << std::endl
              << "Intelligence: "            << this->intelligence << std::endl
              << "Luck: "                    << this->luck << std::endl
              << "Available stats points: "  << this->statPoints << std::endl
              << "Available skill points: "  << this->skillPoints << std::endl;
}

void Player::increaseAttributes() {
    char choice{'n'};
    do {
        if(this->statPoints > 0) {
            this->statPoints--;
            std::cout << "(1) - Strength" << std::endl
                      << "(2) - Dexterity" << std::endl
                      << "(3) - Intelligence" << std::endl
                      << "(4) - Luck" << std::endl;
            int choice = getNumber("\nEnter which attribute you want to increase: ");
            if(choice == 1) {
                this->strength++;
                this->health += 1;
                this->maxHealth += 1;
                this->staminaMax += 1;
                this->stamina += 1;
            }
            else if(choice == 2) {
                this->dexterity++;
                this->minDamage+=1;
                this->maxDamage+=1;
            }
            else if(choice == 3) {
                this->intelligence++;
                this->defence += 1;
            }
            else if(choice == 4) {
                this->luck++;
                this->health -= 1;
                this->maxHealth -= 1;
                this->staminaMax += 2;
                this->stamina += 2;
            }
        }
        else {
            std::cout << "\nYou don't have enough stats points" << std::endl;
        }
        std::cout << "\nYou have " << this->statPoints << " points left.\n Do you want to continue? (y/n)";
        std::cin >> choice;
    } while(this->statPoints > 0 && choice != 'n');

}


int getNumber(const std::string &message) {
    int number{};
    std::cout << message;
    std::cin >> number;
    return number;    
}

void Player::buyItem(std::unique_ptr<Item> &item) {
    if(this->money >= item->getPurchasePrice()) {
        std::cout << "\nYou successfully bought a " << item->getName() << std::endl;
        this->money -= item->getPurchasePrice();
        this->inventory.addItem(item);
    }
    else {
        std::cout << "\nYou don't have enough money to buy " << item->getName() << std::endl;
    }
}

void shop(Player &p) {
    std::cout << "\nWelcome to the Golden street " << p.getName() << "!" << std::endl;
    std::cout << "In this street you can buy (almost) everything you want" << std::endl;
    std::cout << "What type of items you want to view?" << std::endl;
    int choice;
    do {
        std::cout << "\n(1) - Weapons\n(2) - Armor\n(3) - Potions\n(4) - Leave the shop" << std::endl;
        choice = getNumber("\nYour choice: ");
        if(choice == 1) {
            weaponShop(p);
        }
        else if(choice == 2) {
            armorShop(p);
        }
        else if(choice == 3) {
            potionShop(p);
        }
        else {
            std::cout << "" << std::endl;
            break;
        }
    } while(choice != 4);

}

void weaponShop(Player &p) {
    std::cout << "\n/*Weapon shop*/" << std::endl;

    int choice{};
    do {
        std::cout << "(1) - Sword (+5 damage) : cost 20G" << std::endl;
        std::cout << "(2) - Spear (+10 damage) : cost 40G" << std::endl;
        std::cout << "(3) - Axe (+15 damage) : cost 80G" << std::endl;
        std::cout << "(4) - Go back" << std::endl;
        choice = getNumber("\nYour choice: ");
        if(choice == 1) {
            std::unique_ptr<Item> sword = std::make_unique<Weapon>(Weapon("Sword", "Weapon", "Unequipped", 20, 15, 1, 5));
            p.buyItem(sword);
        }
        else if(choice == 2) {
            std::unique_ptr<Item> spear = std::make_unique<Weapon>(Weapon("Spear", "Weapon", "Unequipped", 40, 30, 5, 10));
            p.buyItem(spear);
        }
        else if(choice == 3) {
            std::unique_ptr<Item> axe = std::make_unique<Weapon>(Weapon("Axe", "Weapon", "Unequipped", 80, 60, 10, 15));
            p.buyItem(axe);
        }
    }while(choice != 4);
    
}

void armorShop(Player &p) {
    std::cout << "\n/*Armor shop*/" << std::endl;

    int choice{};
    do {
        std::cout << "(1) - Helmet (+5 defence) : cost 20G" << std::endl;
        std::cout << "(2) - Mail (+10 defence) : cost 40G" << std::endl;
        std::cout << "(3) - Shield (+15 defence) : cost 80G" << std::endl;
        std::cout << "(4) - Go back" << std::endl;
        choice = getNumber("\nYour choice: ");
        if(choice == 1) {
        
        }
        else if(choice == 2) {
            
        }
        else if(choice == 3) {
            
        }
    }while(choice != 4);
}

void potionShop(Player &p) {
    std::cout << "\n/*Potion shop*/" << std::endl;

    int choice;
    do {
        std::cout << "(1) - Health potion (Restores all HP) : cost 20G" << std::endl;
        std::cout << "(2) - Attack potion (+10 damage) : cost 20G" << std::endl;
        std::cout << "(3) - Defend potion (+10 defence) : cost 20G" << std::endl;
        std::cout << "(4) - Go back" << std::endl;
        choice = getNumber("\nYour choice: ");
        if(choice == 1) {
            std::cout << "You have bought an Health potion" << std::endl;
        }
        else if(choice == 2) {
            std::cout << "You have bought an Attack potion" << std::endl;
        }
        else if(choice == 3) {
            std::cout << "You have bought an Defend potion" << std::endl;
        }
        else if(choice == 4) {
            return;
        }
    }while(choice != 4);
    
}

void Player::equipItem() {
    
}