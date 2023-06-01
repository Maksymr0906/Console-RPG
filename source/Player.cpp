#include "Player.hpp"

Player::Player()
    : name{ def_name },
    health{ def_health },
    maxHealth{ def_health },
    minDamage{ def_min_damage },
    maxDamage{ def_max_damage },
    exp{ def_exp },
    expNext{ def_exp_next },
    level{ def_level },
    stamina{ def_stamina },
    staminaMax{ def_stamina_max },
    defence{ def_defence },
    strength{ def_strength },
    vitality{ def_vitality },
    dexterity{ def_dexterity },
    intelligence{ def_intelligence },
    luck{ def_luck },
    statPoints{ def_stat_points },
    skillPoints{ def_skill_points },
    money{ def_money },
    weapon{ def_weapon},
    armorHead{ def_armor },
    armorChest{ def_armor },
    armorLeggs{ def_armor },
    armorBoots{ def_armor },
    distanceTravelled{ def_distance_travelled } {}

bool Player::isAlive() const {
    return health > 0 ? true : false;
}

int Player::inflictDamage() {
    int givenDamage{};

    givenDamage = rand() % (maxDamage - minDamage + 1) + minDamage;

    return givenDamage;
}

void Player::initialize(const std::string& name) {
    this->name = name;
    this->maxHealth = def_max_health + (int)(strength / 2) - 2;
    this->health = this->maxHealth;
    this->minDamage = def_min_damage + (int)(strength/4 + vitality/4) - 2;
    this->maxDamage = def_max_damage + (int)(strength / 4 + vitality / 4) - 2;
    this->exp = def_exp;
    this->expNext = (def_exp_next * (level - 1) + def_exp_next * (level - 1) * 0.5) + 100;
    //+150 exp to next level per level
    this->level = def_level;
    this->staminaMax = def_stamina_max + (int)(vitality/2) - 2;
    this->stamina = this->staminaMax;
    this->defence = def_defence + (intelligence / 2) - 2;
    this->strength = def_strength;
    this->vitality = def_vitality;
    this->dexterity = def_dexterity;
    this->intelligence = def_intelligence;
    this->luck = def_luck;
    this->statPoints = def_stat_points;
    this->skillPoints = def_skill_points;
    this->money = def_money;
    this->weapon = def_weapon;
    this->armorHead = def_armor;
    this->armorChest = def_armor;
    this->armorLeggs = def_armor;
    this->armorBoots = def_armor;
    this->distanceTravelled = def_distance_travelled;
    this->inventory.initialize();
}

void Player::levelUp() {
    if (exp >= expNext) {
        level++;
        exp -= expNext;

        expNext = (def_exp_next * (level - 1) + def_exp_next * (level - 1) * 0.5) + 100;
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
        << "Name: " << this->name << std::endl
        << "Level: " << this->level << std::endl
        << "XP: " << this->exp << " / " << this->expNext << std::endl
        << "Health: " << this->health << " / " << this->maxHealth << std::endl
        << "Stamina: " << this->stamina << " / " << this->staminaMax << std::endl
        << "Damage: " << this->minDamage << " - " << this->maxDamage << std::endl
        << "Defence: " << this->defence << std::endl
        << std::endl
        << "/* Player Atributtes */" << std::endl
        << "Strength: " << this->strength << std::endl
        << "Vitality: " << this->vitality << std::endl
        << "Dexterity: " << this->dexterity << std::endl
        << "Intelligence: " << this->intelligence << std::endl
        << "Luck: " << this->luck << std::endl
        << "Available stats points: " << this->statPoints << std::endl
        << "Available skill points: " << this->skillPoints << std::endl
        << "Gold: " << this->money << std::endl
        << std::endl << "/*Equipment*/" << std::endl
        << "Equipped weapon: " << this->weapon->getName() << std::endl
        << "Equipped helmet: " << this->armorHead->getName() << std::endl
        << "Equipped chestplate: " << this->armorChest->getName() << std::endl
        << "Equipped leggings: " << this->armorLeggs->getName() << std::endl
        << "Equipped boots: " << this->armorBoots->getName() << std::endl;
}

void Player::increaseAttributes() {
    char continueChoice{ 'n' };
    do {
        if (this->statPoints > 0) {
            std::cout << "(1) - Strength" << std::endl
                << "(2) - Vitality" << std::endl
                << "(3) - Dexterity" << std::endl
                << "(4) - Intelligence" << std::endl
                << "(5) - Luck" << std::endl;
            int attributeChoice = getValidAttributeChoice();
            switch(attributeChoice) {
                case 1:
                    this->strength++;
                    break;
                case 2:
                    this->vitality++;
                    break;
                case 3:
                    this->dexterity++;
                    break;
                case 4:
                    this->intelligence++;
                    break;
                case 5:
                    this->luck++;
                    break;
                default:
                    std::cout << "\nInvalid attribute choice" << std::endl;
                    break;
            }
            this->statPoints--;
            this->updateCharacteristics();
        }
        else {
            std::cout << "\nYou don't have enough stats points" << std::endl;
            return;
        }
        std::cout << "\nYou have " << this->statPoints << " points left.\nDo you want to continue? (y/n)";
        std::cin >> continueChoice;
    } while (this->statPoints > 0 && continueChoice != 'n');
}

int Player::getValidAttributeChoice() const {
    int attributeChoice{};
    do {
        attributeChoice = getNumber("Enter which attribute you want to increase: ");
        if(attributeChoice < 1 || attributeChoice > 5) {
            std::cout << "\nInvalid attribute choice. Please try again." << std::endl;
        }
    } while(attributeChoice < 1 || attributeChoice > 5);

    return attributeChoice;
}

void Player::updateCharacteristics() {
    this->maxHealth = def_max_health + (int)(strength / 2) - 2;
    this->health = this->maxHealth;
    this->minDamage = def_min_damage + (int)(strength / 4 + vitality / 4) - 2;
    this->maxDamage = def_max_damage + (int)(strength / 4 + vitality / 4) - 2;
    this->staminaMax = def_stamina_max + (int)(vitality / 2) - 2;
    this->stamina = this->staminaMax;
    this->defence = def_defence + (intelligence / 2) - 2;
}

int getNumber(const std::string& message) {
    int number{};
    std::cout << message;
    std::cin >> number;
    return number;
}

void Player::buyItem(std::shared_ptr<Item>& item) {
    if (this->money >= item->getPurchasePrice()) {
        std::cout << "\nYou successfully bought a " << item->getName() << std::endl;
        this->money -= item->getPurchasePrice();
        this->inventory.addItem(item);
    }
    else {
        std::cout << "\nYou don't have enough money to buy " << item->getName() << std::endl;
    }
}

void shop(Player& p) {
    std::cout << "\nWelcome to the Golden street " << p.getName() << "!" << std::endl;
    std::cout << "In this street you can buy (almost) everything you want" << std::endl;
    std::cout << "What type of items you want to view?" << std::endl;
    int choice;
    do {
        std::cout << "\n(1) - Weapons\n(2) - Armor\n(3) - Potions\n(4) - Leave the shop" << std::endl;
        choice = getNumber("\nYour choice: ");
        if (choice == 1) {
            weaponShop(p);
        }
        else if (choice == 2) {
            armorShop(p);
        }
        else if (choice == 3) {
            potionShop(p);
        }
        else {
            std::cout << "" << std::endl;
            break;
        }
    } while (choice != 4);

}

void weaponShop(Player& p) {
    std::cout << "\n/*Weapon shop*/" << std::endl;

    int choice{};
    do {
        std::cout << "\n(1) - Sword (+5 damage) : cost 20G" << std::endl;
        std::cout << "(2) - Spear (+10 damage) : cost 40G" << std::endl;
        std::cout << "(3) - Axe (+15 damage) : cost 80G" << std::endl;
        std::cout << "(4) - Go back" << std::endl;
        choice = getNumber("\nYour choice: ");
        if (choice == 1) {
            std::shared_ptr<Item> sword = std::make_shared<Weapon>(Weapon("Sword", "Weapon", "Unequipped", 20, 15, 1, 5, 1, 1));
            p.buyItem(sword);
        }
        else if (choice == 2) {
            std::shared_ptr<Item> spear = std::make_shared<Weapon>(Weapon("Spear", "Weapon", "Unequipped", 40, 30, 5, 10, 1, 1));
            p.buyItem(spear);
        }
        else if (choice == 3) {
            std::shared_ptr<Item> axe = std::make_shared<Weapon>(Weapon("Axe", "Weapon", "Unequipped", 80, 60, 10, 15, 1, 1));
            p.buyItem(axe);
        }
    } while (choice != 4);

}

void armorShop(Player& p) {
    std::cout << "\n/*Armor shop*/" << std::endl;

    int choice{};
    do {
        std::cout << "\n(1) - Helmet (+5 defence) : cost 20G" << std::endl;
        std::cout << "(2) - Mail (+10 defence) : cost 40G" << std::endl;
        std::cout << "(3) - Leather pants (+15 defence) : cost 80G" << std::endl;
        std::cout << "(4) - Go back" << std::endl;
        choice = getNumber("\nYour choice: ");
        if (choice == 1) {
            std::shared_ptr<Item> helmet = std::make_shared<Armor>(Armor("Helmet", "Armor", "Unequipped", 20, 10, 1, 1, 5, 1));
            p.buyItem(helmet);
        }
        else if (choice == 2) {
            std::shared_ptr<Item> mail = std::make_shared<Armor>(Armor("Mail", "Armor", "Unequipped", 40, 30, 1, 1, 10, 2));
            p.buyItem(mail);
        }
        else if (choice == 3) {
            std::shared_ptr<Item> leatherPants = std::make_shared<Armor>(Armor("Leather Pants", "Armor", "Unequipped", 80, 60, 1, 1, 15, 3));
            p.buyItem(leatherPants);
        }
    } while (choice != 4);
}

void potionShop(Player& p) {
    std::cout << "\n/*Potion shop*/" << std::endl;

    int choice;
    do {
        std::cout << "\n(1) - Health potion (Restores all HP) : cost 20G" << std::endl;
        std::cout << "(2) - Attack potion (+10 damage) : cost 20G" << std::endl;
        std::cout << "(3) - Defend potion (+10 defence) : cost 20G" << std::endl;
        std::cout << "(4) - Go back" << std::endl;
        choice = getNumber("\nYour choice: ");
        if (choice == 1) {
            std::cout << "You have bought an Health potion" << std::endl;
        }
        else if (choice == 2) {
            std::cout << "You have bought an Attack potion" << std::endl;
        }
        else if (choice == 3) {
            std::cout << "You have bought an Defend potion" << std::endl;
        }
        else if (choice == 4) {
            return;
        }
    } while (choice != 4);
}

void Player::equipItem(std::shared_ptr<Item> &item) {
    item->equip();
    if(item->getCategory() == "Weapon") {
        std::shared_ptr<Weapon> weaponItem = std::dynamic_pointer_cast<Weapon>(item);
        
        if(weaponItem) {
            this->weapon = weaponItem;
            this->minDamage += weaponItem->getMinDamage();
            this->maxDamage += weaponItem->getMaxDamage();
        }
    }
    else if(item->getCategory() == "Armor") {
        std::shared_ptr<Armor> armorItem = std::dynamic_pointer_cast<Armor>(item);

        if(armorItem) {
            if(armorItem->getType() == 1) {
                this->armorHead = armorItem;
            }
            else if(armorItem->getType() == 2) {
                this->armorChest = armorItem;
            }
            else if(armorItem->getType() == 3) {
                this->armorLeggs = armorItem;
            }
            else if(armorItem->getType() == 4) {
                this->armorBoots = armorItem;
            }

            this->defence += armorItem->getDefence();
        }
    }
}

void Player::unequipItem(std::shared_ptr<Item> &item) {
    item->unequip();
    if(item->getCategory() == "Weapon") {
        std::shared_ptr<Weapon> weaponItem = std::dynamic_pointer_cast<Weapon>(item);
        if(weaponItem) {
            this->weapon = def_weapon;
            this->minDamage -= weaponItem->getMinDamage();
            this->maxDamage -= weaponItem->getMaxDamage();
        }
    }
    else if(item->getCategory() == "Armor") {
        std::shared_ptr<Armor> armorItem = std::dynamic_pointer_cast<Armor>(item);

        if(armorItem) {
            if(armorItem->getType() == 1) {
                this->armorHead = def_armor;
            }
            else if(armorItem->getType() == 2) {
                this->armorChest = def_armor;
            }
            else if(armorItem->getType() == 3) {
                this->armorLeggs = def_armor;
            }
            else if(armorItem->getType() == 4) {
                this->armorBoots = def_armor;
            }

            this->defence -= armorItem->getDefence();
        }
    }
}

void Player::showInventory() {
    if(this->inventory.is_empty()) {
        std::cout << "\nYour inventory is empty\n" << std::endl;
        return;
    }

    int selectedItemIndex{};

    do {
        this->inventory.showInventory();
        selectedItemIndex = getNumber("\nChoose the number for more details about the item or enter 0 to go back: ");
        if(selectedItemIndex == 0) {
            return;
        }
        else {
            std::shared_ptr<Item> selectedItem = this->inventory.getInventory().at(selectedItemIndex - 1);
            std::cout << *selectedItem << std::endl;

            char choice;
            if(selectedItem->getStatus() == "Equipped") {
                std::cout << "Do you want to unequip this item? (y/n)\n";
                std::cin >> choice;

                if(choice == 'y') {
                    unequipItem(selectedItem);
                }
            }
            else {
                std::cout << "Do you want to equip this item? (y/n)\n";
                std::cin >> choice;

                if(choice == 'y') {
                    equipItem(selectedItem);
                }
            }
        } 
    } while(selectedItemIndex != 0);
}

void Player::showEquipment() {
    std::cout << "\nWeapon: \n" << weapon << std::endl;
    std::cout << "\nArmor head: \n" << armorHead << std::endl;
    std::cout << "\nArmor chest: \n" << armorChest << std::endl;
    std::cout << "\nArmor leggs: \n" << armorLeggs << std::endl;
    std::cout << "\nArmor boots: \n" << armorBoots << std::endl;
}