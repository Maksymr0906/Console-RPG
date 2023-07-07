#include "Player.hpp"

Player::Player()
    : Entity{def_name, def_health, def_max_health, def_min_damage, def_max_damage, def_level, def_defence},
    thirst{ def_thirst },
    thirstMax{ def_thirst_max },
    hunger{ def_hunger },
    hungerMax{ def_hunger_max },
    exp{ def_exp },
    expNext{ def_exp_next },
    stamina{ def_stamina },
    staminaMax{ def_stamina_max },
    strength{ def_strength },
    vitality{ def_vitality },
    dexterity{ def_dexterity },
    intelligence{ def_intelligence },
    luck{ def_luck },
    statPoints{ def_stat_points },
    skillPoints{ def_skill_points },
    money{ def_money },
    weapon{ std::make_shared<Weapon>()},
    armorHead{ std::make_shared<Armor>() },
    armorChest{ std::make_shared<Armor>() },
    armorLeggs{ std::make_shared<Armor>() },
    armorBoots{ std::make_shared<Armor>() },
    distanceTravelled{ def_distance_travelled },
    radiation{ def_radiation } {}

void Player::initialize(const std::string &name) {
    this->name = name;
    this->maxHealth = def_max_health + (int)(strength / 2) - 2;
    this->health = this->maxHealth;
    this->thirst = def_thirst;
    this->thirstMax = def_thirst_max;
    this->hunger = def_hunger;
    this->hungerMax = def_hunger_max;
    this->minDamage = def_min_damage + (int)(strength / 4 + vitality / 4) - 2;
    this->maxDamage = def_max_damage + (int)(strength / 4 + vitality / 4) - 2;
    this->exp = def_exp;
    this->expNext = (def_exp_next * (level - 1) + def_exp_next * (level - 1) * 0.5) + 100;
    //+150 exp to next level per level
    this->level = def_level;
    this->staminaMax = def_stamina_max + (int)(vitality / 2) - 2;
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
    this->radiation = def_radiation;
    this->inventory.initialize();
}

void Player::showStats() {
    std::cout << std::endl << "/* Player stats */" << std::endl
        << "Name: " << this->name << std::endl
        << "Level: " << this->level << std::endl
        << "XP: " << this->exp << " / " << this->expNext << std::endl
        << "Health: " << this->health << " / " << this->maxHealth << std::endl
        << "Hunger: " << this->hunger << " / " << this->hungerMax << std::endl
        << "Thirst: " << this->thirst << " / " << this->thirstMax << std::endl
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


//Refactor code below
void Player::showInventory() {
    if(this->inventory.is_empty()) {
        std::cout << "\nYour inventory is empty\n" << std::endl;
        return;
    }

    int selectedItemIndex{};

    do {
        this->inventory.showInventory();
        selectedItemIndex = getValidateAnswer("Your choice: ", "Incorrect choice", 0, this->inventory.getInventory().size());
        if(selectedItemIndex == 0 || selectedItemIndex > this->inventory.getInventory().size()) {
            return;
        }
        else {
            std::shared_ptr<Item> &selectedItem = this->inventory.getInventory().at(selectedItemIndex - 1);
            std::cout << *selectedItem << std::endl;
            char choice{};
            //std::cout << "\n(0) - Go back\n(1) - Equip/Use\n(2) - Info\n(3) - Delete Item\n";
            if(selectedItem->getItemType() == 3) {
                this->useProduct(selectedItem);
                this->getInventory().removeItem(selectedItemIndex-1);
                continue;
            }

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
    std::cout << "(1) - Weapon: " << this->weapon->getName() << std::endl;
    std::cout << "(2) - Head: " << this->armorHead->getName() << std::endl;
    std::cout << "(3) - Chest: " << this->armorChest->getName() << std::endl;
    std::cout << "(4) - Leggs: " << this->armorLeggs->getName() << std::endl;
    std::cout << "(5) - Boots: " << this->armorBoots->getName() << std::endl;
}

void Player::previewPlayer() const {
    std::cout << std::endl;
    std::cout << std::setw(41) << std::setfill('=') << " " << std::endl;
    std::cout << std::left << std::setw(40) << "== " + this->name + " " << std::endl;
    std::cout << std::right << std::setw(41) << std::setfill('=') << " " << std::endl;
    std::cout << std::left << std::setw(40) << "== Hp: " + std::to_string(this->health) + "/" + std::to_string(this->maxHealth) + " " << std::endl;
    std::cout << std::left << std::setw(40) << "== Stamina: " + std::to_string(this->stamina) + "/" + std::to_string(this->staminaMax) + " " << std::endl;
    std::cout << std::left << std::setw(40) << "== Hunger: " + std::to_string(this->hunger) + "/" + std::to_string(this->hungerMax) + " | Thirst: " + std::to_string(this->thirst) + "/" + std::to_string(this->thirstMax) + " " << std::endl;
    std::cout << std::right << std::setw(41) << std::setfill('=') << " " << std::endl;
    std::cout << std::setfill(' ') << std::endl;
}

bool Player::isAlive() const {
    return health > 0 ? true : false;
}

int Player::inflictDamage() {
    int givenDamage{};

    givenDamage = rand() % (maxDamage - minDamage + 1) + minDamage;

    return givenDamage;
}

void Player::writeToTxtFile(std::ofstream &outfile) const {
    Entity::writeToTxtFile(outfile);
    outfile << thirst << '\n'
            << hunger << '\n'
            << thirstMax << '\n'
            << hungerMax << '\n'
            << exp << '\n'
            << expNext << '\n'
            << stamina << '\n'
            << staminaMax << '\n'
            << strength << '\n'
            << vitality << '\n'
            << dexterity << '\n'
            << intelligence << '\n'
            << luck << '\n'
            << statPoints << '\n'
            << skillPoints << '\n'
            << money << '\n'
            << radiation << '\n'
            << distanceTravelled << '\n';
    this->inventory.writeToTxtFile(outfile);
    this->weapon->writeToTxtFile(outfile);
    this->armorHead->writeToTxtFile(outfile);
    this->armorChest->writeToTxtFile(outfile);
    this->armorLeggs->writeToTxtFile(outfile);
    this->armorBoots->writeToTxtFile(outfile);
}

void Player::readFromTxtFile(std::ifstream &infile) {
    Entity::readFromTxtFile(infile);
    infile >> thirst >> hunger
           >> thirstMax >> hungerMax
           >> exp >> expNext
           >> stamina >> staminaMax
           >> strength >> vitality >> dexterity >> intelligence
           >> luck
           >> statPoints >> skillPoints
           >> money 
           >> radiation
           >> distanceTravelled;
    this->inventory.readFromTxtFile(infile);
    infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //this->weapon = std::make_shared<Weapon>();
    this->weapon->readFromTxtFile(infile);
    infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //this->armorHead = std::make_shared<Armor>();
    this->armorHead->readFromTxtFile(infile);
    infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //this->armorChest = std::make_shared<Armor>();
    this->armorChest->readFromTxtFile(infile);
    infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //this->armorLeggs = std::make_shared<Armor>();
    this->armorLeggs->readFromTxtFile(infile);
    infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //this->armorBoots = std::make_shared<Armor>();
    this->armorBoots->readFromTxtFile(infile);

    for(const auto &item : this->inventory.getInventory()) {
        if(item->getStatus() == "Equipped") {
            if(*item == *weapon) {
                weapon = item;
            }
            else if(*item == *armorHead) {
                armorHead = item;
            }
            else if(*item == *armorChest) {
                armorChest = item;
            }
            else if(*item == *armorLeggs) {
                armorLeggs = item;
            }
            else if(*item == *armorBoots) {
                armorBoots = item;
            }
        }
    }
}

bool Player::serialize(std::ofstream &outfile) const {
    try {
        int nameLength = name.length();
        outfile.write(reinterpret_cast<const char *>(&nameLength), sizeof(nameLength));
        outfile.write(name.c_str(), nameLength);

        outfile.write(reinterpret_cast<const char *>(&health), sizeof(health));
        outfile.write(reinterpret_cast<const char *>(&maxHealth), sizeof(maxHealth));
        outfile.write(reinterpret_cast<const char *>(&thirst), sizeof(thirst));
        outfile.write(reinterpret_cast<const char *>(&thirstMax), sizeof(thirstMax));
        outfile.write(reinterpret_cast<const char *>(&hunger), sizeof(hunger));
        outfile.write(reinterpret_cast<const char *>(&hungerMax), sizeof(hungerMax));
        outfile.write(reinterpret_cast<const char *>(&minDamage), sizeof(minDamage));
        outfile.write(reinterpret_cast<const char *>(&maxDamage), sizeof(maxDamage));
        outfile.write(reinterpret_cast<const char *>(&exp), sizeof(exp));
        outfile.write(reinterpret_cast<const char *>(&expNext), sizeof(expNext));
        outfile.write(reinterpret_cast<const char *>(&level), sizeof(level));
        outfile.write(reinterpret_cast<const char *>(&stamina), sizeof(stamina));
        outfile.write(reinterpret_cast<const char *>(&staminaMax), sizeof(staminaMax));
        outfile.write(reinterpret_cast<const char *>(&defence), sizeof(defence));
        outfile.write(reinterpret_cast<const char *>(&strength), sizeof(strength));
        outfile.write(reinterpret_cast<const char *>(&vitality), sizeof(vitality));
        outfile.write(reinterpret_cast<const char *>(&dexterity), sizeof(dexterity));
        outfile.write(reinterpret_cast<const char *>(&intelligence), sizeof(intelligence));
        outfile.write(reinterpret_cast<const char *>(&luck), sizeof(luck));
        outfile.write(reinterpret_cast<const char *>(&statPoints), sizeof(statPoints));
        outfile.write(reinterpret_cast<const char *>(&skillPoints), sizeof(skillPoints));
        outfile.write(reinterpret_cast<const char *>(&radiation), sizeof(radiation));
        outfile.write(reinterpret_cast<const char *>(&distanceTravelled), sizeof(distanceTravelled));

        inventory.serialize(outfile);
        weapon->serialize(outfile);
        armorHead->serialize(outfile);
        armorChest->serialize(outfile);
        armorLeggs->serialize(outfile);
        armorBoots->serialize(outfile);
        return true;
    }
    catch(...) {
        return false;
    }
}

bool Player::deserialize(std::ifstream &infile) {
    try {
        int nameLength{};
        infile.read(reinterpret_cast<char *>(&nameLength), sizeof(nameLength));
        if(nameLength == 0) {
            throw 0;
        }
        char *nameBuffer = new char[nameLength + 1];
        infile.read(nameBuffer, nameLength);
        nameBuffer[nameLength] = '\0';
        name = nameBuffer;
        delete[] nameBuffer;

        infile.read(reinterpret_cast<char *>(&health), sizeof(health));
        infile.read(reinterpret_cast<char *>(&maxHealth), sizeof(maxHealth));
        infile.read(reinterpret_cast<char *>(&thirst), sizeof(thirst));
        infile.read(reinterpret_cast<char *>(&thirstMax), sizeof(thirstMax));
        infile.read(reinterpret_cast<char *>(&hunger), sizeof(hunger));
        infile.read(reinterpret_cast<char *>(&hungerMax), sizeof(hungerMax));
        infile.read(reinterpret_cast<char *>(&minDamage), sizeof(minDamage));
        infile.read(reinterpret_cast<char *>(&maxDamage), sizeof(maxDamage));
        infile.read(reinterpret_cast<char *>(&exp), sizeof(exp));
        infile.read(reinterpret_cast<char *>(&expNext), sizeof(expNext));
        infile.read(reinterpret_cast<char *>(&level), sizeof(level));
        infile.read(reinterpret_cast<char *>(&stamina), sizeof(stamina));
        infile.read(reinterpret_cast<char *>(&staminaMax), sizeof(staminaMax));
        infile.read(reinterpret_cast<char *>(&defence), sizeof(defence));
        infile.read(reinterpret_cast<char *>(&strength), sizeof(strength));
        infile.read(reinterpret_cast<char *>(&vitality), sizeof(vitality));
        infile.read(reinterpret_cast<char *>(&dexterity), sizeof(dexterity));
        infile.read(reinterpret_cast<char *>(&intelligence), sizeof(intelligence));
        infile.read(reinterpret_cast<char *>(&luck), sizeof(luck));
        infile.read(reinterpret_cast<char *>(&statPoints), sizeof(statPoints));
        infile.read(reinterpret_cast<char *>(&skillPoints), sizeof(skillPoints));
        infile.read(reinterpret_cast<char *>(&radiation), sizeof(radiation));
        infile.read(reinterpret_cast<char *>(&distanceTravelled), sizeof(distanceTravelled));

        inventory.deserialize(infile);
        weapon = std::make_shared<Weapon>();
        weapon->deserialize(infile);

        armorHead = std::make_shared<Armor>();
        armorHead->deserialize(infile);

        armorChest = std::make_shared<Armor>();
        armorChest->deserialize(infile);

        armorLeggs = std::make_shared<Armor>();
        armorLeggs->deserialize(infile);

        armorBoots = std::make_shared<Armor>();
        armorBoots->deserialize(infile);

        for(const auto &item : inventory.getInventory()) {
            if(item->getStatus() == "Equipped") {
                if(*item == *weapon) {
                    weapon = item;
                }
                else if(*item == *armorHead) {
                    armorHead = item;
                }
                else if(*item == *armorChest) {
                    armorChest = item;
                }
                else if(*item == *armorLeggs) {
                    armorLeggs = item;
                }
                else if(*item == *armorBoots) {
                    armorBoots = item;
                }
            }
        }

        return true;
    }
    catch(...) {
        return false;
    }
}

void Player::levelUp() {
    if(exp >= expNext) {
        level++;
        exp -= expNext;

        expNext = (def_exp_next * (level - 1) + def_exp_next * (level - 1) * 0.5) + 100;
        skillPoints++;
        statPoints += 5;
        this->hunger = this->hungerMax;
        this->thirst = this->thirstMax;
        this->health = this->maxHealth;
        this->stamina = this->staminaMax;
        std::cout << "\nCongratulations, you are now " << this->level << " level!" << std::endl;
    }
}

std::string Player::getAsString() const {
    return this->name + " " +
        std::to_string(this->health) + " " +
        std::to_string(this->maxHealth) + " " +
        std::to_string(this->minDamage) + " " +
        std::to_string(this->maxDamage) + " " +
        std::to_string(this->exp) + " " +
        std::to_string(this->expNext) + " " +
        std::to_string(this->level) + " " +
        std::to_string(this->stamina) + " " +
        std::to_string(this->staminaMax) + " " +
        std::to_string(this->defence) + " " +
        std::to_string(this->strength) + " " +
        std::to_string(this->vitality) + " " +
        std::to_string(this->dexterity) + " " +
        std::to_string(this->intelligence) + " " +
        std::to_string(this->luck) + " " +
        std::to_string(this->statPoints) + " " +
        std::to_string(this->skillPoints) + " " +
        std::to_string(money);
}

void Player::increaseAttributes() {
    char continueChoice{ 'n' };
    do {
        if(this->statPoints > 0) {
            std::cout << "(1) - Strength" << std::endl
                << "(2) - Vitality" << std::endl
                << "(3) - Dexterity" << std::endl
                << "(4) - Intelligence" << std::endl
                << "(5) - Luck" << std::endl;
            //int attributeChoice = getValidAttributeChoice();
            int attributeChoice = getValidateAnswer("Enter which attribute you want to increase: ", "\nInvalid attribute choice. Please try again.", 1, 5);
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
    } while(this->statPoints > 0 && continueChoice != 'n');
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

bool Player::buyItem(std::shared_ptr<Item> &item) {
    if(this->money >= item->getPurchasePrice()) {
        std::cout << "\n/*You bought a " << item->getName() << "*/" << std::endl;
        this->money -= item->getPurchasePrice();
        this->inventory.addItem(item);
        return true;
    }
    else {
        return false;
    }
}

void sellItems(Player &p) {
    std::cout << "Welcome to the flea market. Here you can sell all your junk." << std::endl;
    Inventory &inventory = p.getInventory();
    int choice{};

    do {
        if(inventory.getInventory().size() > 0) {
            inventory.showInventory();
            choice = getValidateAnswer("Choose item that you want to sell: ", "Incorrect choice", 0, inventory.getInventory().size());

            if(choice == 0) {
                return;
            }
            else {
                std::string nameOfSoldItem = inventory.getInventory()[choice - 1]->getName();
                p.sellItem(choice - 1);
                std::cout << nameOfSoldItem << " sold" << std::endl;
            }
        }
        else {
            std::cout << "\nYour inventory is empty" << std::endl;
            return;
        }
    } while(choice != 0);
    
}

void Player::sellItem(const int &position) {
    std::shared_ptr<Item> &item = this->getInventory().getInventory()[position];
    this->money = this->money + this->getInventory().getInventory()[position]->getSalePrice();
    if(this->getInventory().getInventory()[position]->getStatus() == "Equipped") {
        unequipItem(this->getInventory().getInventory()[position]);
    }
    this->getInventory().removeItem(position);
}

void shop(Player &p) {
    std::cout << "\nWelcome to the Golden street " << p.getName() << "!" << std::endl
              << "In this street you can buy (almost) everything you want" << std::endl
              << "What type of items you want to view?" << std::endl;
    int choice{}, moneyBefore{p.getMoney()};
    do {
        std::cout << "My money: " << p.getMoney() << std::endl;
        choice = getValidateAnswer("\n(0) - Leave the shop\n(1) - Weapons\n(2) - Armor\n(3) - Potions\n(4) - Increase backpack\n(5) - Sell items\nYour choice: ", "Incorrect choice", 0, 5);
        if(choice == 1) {
            weaponShop(p);
        }
        else if(choice == 2) {
            armorShop(p);
        }
        else if(choice == 3) {
            potionShop(p);
        }
        else if(choice == 4) {
            increaseBackpack(p);
        }
        else if(choice == 5) {
            sellItems(p);
        }
        else {
            if(moneyBefore == p.getMoney()) {
                std::cout << "Though you didn't make a purchase, I'm always happy to see you. Stay safe on your travels!" << std::endl;
            }
            break;
        }
    } while(choice != 0);

}

void weaponShop(Player &p) {
    std::cout << "\n/*Weapon shop*/" << std::endl;

    int choice{};
    do {
        std::cout << "\n(0) - Go back" << std::endl;
        std::cout << "(1) - Sword (+5 damage) : cost 20G" << std::endl;
        std::cout << "(2) - Spear (+10 damage) : cost 40G" << std::endl;
        std::cout << "(3) - Axe (+15 damage) : cost 80G" << std::endl;

        choice = getNumber("\nYour choice: ");
        if(choice == 1) {
            std::shared_ptr<Item> sword = std::make_shared<Weapon>(Weapon("Sword", "Weapon", "Unequipped", 20, 15, 1, 5, 1, 1));
            if(p.buyItem(sword)) {
                std::cout << "Thank you for your purchase! Feel free to come back anytime, I always have something interesting!" << std::endl;
            }
            else {
                std::cout << "If you don't have enough money, I'm afraid I can't offer my wares at a discount. Perhaps another time when your purse is heavier." << std::endl;
            }
        }
        else if(choice == 2) {
            std::shared_ptr<Item> spear = std::make_shared<Weapon>(Weapon("Spear", "Weapon", "Unequipped", 40, 30, 5, 10, 1, 1));
            if(p.buyItem(spear)) {
                std::cout << "Thank you for your purchase! Feel free to come back anytime, I always have something interesting!" << std::endl;
            }
            else {
                std::cout << "If you don't have enough money, I'm afraid I can't offer my wares at a discount. Perhaps another time when your purse is heavier." << std::endl;
            }
        }
        else if(choice == 3) {
            std::shared_ptr<Item> axe = std::make_shared<Weapon>(Weapon("Axe", "Weapon", "Unequipped", 80, 60, 10, 15, 1, 1));
            if(p.buyItem(axe)) {
                std::cout << "Thank you for your purchase! Feel free to come back anytime, I always have something interesting!" << std::endl;
            }
            else {
                std::cout << "If you don't have enough money, I'm afraid I can't offer my wares at a discount. Perhaps another time when your purse is heavier." << std::endl;
            }
        }
    } while(choice != 0);

}

void armorShop(Player &p) {
    std::cout << "\n/*Armor shop*/" << std::endl;

    int choice{};
    do {
        std::cout << "\n(0) - Go back" << std::endl;
        std::cout << "(1) - Helmet (+5 defence) : cost 20G" << std::endl;
        std::cout << "(2) - Mail (+10 defence) : cost 40G" << std::endl;
        std::cout << "(3) - Leather pants (+15 defence) : cost 80G" << std::endl;

        choice = getNumber("\nYour choice: ");
        if(choice == 1) {
            std::shared_ptr<Item> helmet = std::make_shared<Armor>(Armor("Helmet", "Armor", "Unequipped", 20, 10, 1, 1, 5, 1));
            if(p.buyItem(helmet)) {
                std::cout << "Thank you for your purchase! Feel free to come back anytime, I always have something interesting!" << std::endl;
            }
            else {
                std::cout << "If you don't have enough money, I'm afraid I can't offer my wares at a discount. Perhaps another time when your purse is heavier." << std::endl;
            }
        }
        else if(choice == 2) {
            std::shared_ptr<Item> mail = std::make_shared<Armor>(Armor("Mail", "Armor", "Unequipped", 40, 30, 1, 1, 10, 2));
            if(p.buyItem(mail)) {
                std::cout << "Thank you for your purchase! Feel free to come back anytime, I always have something interesting!" << std::endl;
            }
            else {
                std::cout << "If you don't have enough money, I'm afraid I can't offer my wares at a discount. Perhaps another time when your purse is heavier." << std::endl;
            }
        }
        else if(choice == 3) {
            std::shared_ptr<Item> leatherPants = std::make_shared<Armor>(Armor("Leather Pants", "Armor", "Unequipped", 80, 60, 1, 1, 15, 3));
            if(p.buyItem(leatherPants)) {
                std::cout << "Thank you for your purchase! Feel free to come back anytime, I always have something interesting!" << std::endl;
            }
            else {
                std::cout << "If you don't have enough money, I'm afraid I can't offer my wares at a discount. Perhaps another time when your purse is heavier." << std::endl;
            }
        }
    } while(choice != 4);
}

void potionShop(Player &p) {
    std::cout << "\n/*Potion shop*/" << std::endl;

    int choice{};
    do {
        std::cout << "\n(1) - Health potion (Restores all HP) : cost 20G" << std::endl;
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
    } while(choice != 4);
}

void increaseBackpack(Player &p) {
    std::cout << "\nWelcome to Backpack shop. Hope something suits you!" << std::endl;
    int choice{};
    std::vector<std::pair<int, int>> backpacks{ {30, 9}, {80, 13}, {150, 19}, {300, 23}, {500, 25} };
    do {
        choice = getValidateAnswer("\n(0) - Go back\n(1) - School backpack (+4 slots) Cost: 30G\n(2) - Pioneer backpack (+8 slots) Cost: 80G\n(3) - Duffel bag (+14 slots) Cost: 150G\n(4) - Tourist backpack (+18 slots) Cost: 300G\n(5) - Army backpack (+20 slots) Cost: 500G\nYour choice: ", "Incorrect choice", 0, 5);
        if(choice == 1) {
            if(setNewBackpack(p, backpacks[choice - 1]))
                std::cout << "\nYou bought a School backpack" << std::endl;
        }
        else if(choice == 2) {
            if(setNewBackpack(p, backpacks[choice - 1]))
                std::cout << "\nYou bought a Pioneer backpack" << std::endl;
        }
        else if(choice == 3) {
            if(setNewBackpack(p, backpacks[choice-1])) 
                std::cout << "\nYou bought a Duffel bag" << std::endl;
        }
        else if(choice == 4) {
            if(setNewBackpack(p, backpacks[choice - 1]))
                std::cout << "\nYou bought a Tourist backpack" << std::endl;
        }
        else if(choice == 5) {
            if(setNewBackpack(p, backpacks[choice-1]))
                std::cout << "\nYou bought a Army backpack" << std::endl;
        }
    } while(choice != 0);
}

bool setNewBackpack(Player &p, const std::pair<int, int> &backpack) {
    if(p.getInventory().getSizeOfInventory() >= backpack.second) {
        std::cout << "\nI guess you already have a bigger backpack than that" << std::endl;
        return false;
    }

    if(p.getMoney() < backpack.first) {
        std::cout << "\nYou don't have enough money" << std::endl;
        return false;
    }

    p.getInventory().setSizeOfInventory(backpack.second);
    p.setMoney(p.getMoney() - backpack.first);
    return true;
}

void Player::equipItem(std::shared_ptr<Item> &item) {
    item->equip();
    if(item->getCategory() == "Weapon") {
        std::shared_ptr<Weapon> weaponItem = std::dynamic_pointer_cast<Weapon>(item);

        if(weaponItem) {
            if(this->weapon->getName() != "None") {
                unequipItem(this->weapon);
            }
            this->weapon = weaponItem;
            this->minDamage += weaponItem->getMinDamage();
            this->maxDamage += weaponItem->getMaxDamage();
        }
    }
    else if(item->getCategory() == "Armor") {
        std::shared_ptr<Armor> armorItem = std::dynamic_pointer_cast<Armor>(item);

        if(armorItem) {
            if(armorItem->getType() == 1) {
                if(this->armorHead->getName() != "None") {
                    unequipItem(this->armorHead);
                }
                this->armorHead = armorItem;
            }
            else if(armorItem->getType() == 2) {
                if(this->armorChest->getName() != "None") {
                    unequipItem(this->armorChest);
                }
                this->armorChest = armorItem;
            }
            else if(armorItem->getType() == 3) {
                if(this->armorLeggs->getName() != "None") {
                    unequipItem(this->armorLeggs);
                }
                this->armorLeggs = armorItem;
            }
            else if(armorItem->getType() == 4) {
                if(this->armorBoots->getName() != "None") {
                    unequipItem(this->armorBoots);
                }
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
            this->weapon.reset();
            this->weapon = def_weapon;
            this->minDamage -= weaponItem->getMinDamage();
            this->maxDamage -= weaponItem->getMaxDamage();
        }
    }
    else if(item->getCategory() == "Armor") {
        std::shared_ptr<Armor> armorItem = std::dynamic_pointer_cast<Armor>(item);
        if(armorItem) {
            if(armorItem->getType() == 1) {
                this->armorHead.reset();
                this->armorHead = def_armor;
                std::cout << *armorHead << std::endl;
            }
            else if(armorItem->getType() == 2) {
                this->armorChest.reset();
                this->armorChest = def_armor;
            }
            else if(armorItem->getType() == 3) {
                this->armorLeggs.reset();
                this->armorLeggs = def_armor;
            }
            else if(armorItem->getType() == 4) {
                this->armorBoots.reset();
                this->armorBoots = def_armor;
            }

            this->defence -= armorItem->getDefence();
        }
    }
}

bool Player::operator==(const Player &rhs) const {
    if(this->name == rhs.name)
        return true;
}

Player &Player::operator=(const Player &rhs) {
    if(this == &rhs) {
        return *this;
    }

    this->name = rhs.name;
    this->maxHealth = rhs.maxHealth;
    this->health = rhs.health;
    this->hunger = rhs.hunger;
    this->hungerMax = rhs.hungerMax;
    this->thirst = rhs.thirst;
    this->thirstMax = rhs.thirstMax;
    this->minDamage = rhs.minDamage;
    this->maxDamage = rhs.maxDamage;
    this->exp = rhs.exp;
    this->expNext = rhs.expNext;
    this->level = rhs.level;
    this->staminaMax = rhs.staminaMax;
    this->stamina = rhs.stamina;
    this->defence = rhs.defence;
    this->strength = rhs.strength;
    this->vitality = rhs.vitality;
    this->dexterity = rhs.dexterity;
    this->intelligence = rhs.intelligence;
    this->luck = rhs.luck;
    this->statPoints = rhs.statPoints;
    this->skillPoints = rhs.skillPoints;
    this->money = rhs.money;
    this->radiation = rhs.radiation;
    this->weapon = rhs.weapon;
    this->armorHead = rhs.armorHead;
    this->armorChest = rhs.armorChest;
    this->armorLeggs = rhs.armorLeggs;
    this->armorBoots = rhs.armorBoots;
    this->distanceTravelled = rhs.distanceTravelled;
    this->inventory = rhs.inventory;
}

void Player::explore() {
    this->distanceTravelled++;
    //Do smth with radiation
    int usedStamina = calculateRandomCharacteristic(7, 11);
    int usedHunger = calculateRandomCharacteristic(2, 6);
    int usedThirst = calculateRandomCharacteristic(2, 6);
    int usedHealth = calculateRandomCharacteristic(4, 10);
    int expEarned = calculateRandomCharacteristic(5, 8);
    int moneyEarned = calculateRandomCharacteristic(3, 6);

    if(stamina != 0 && hunger != 0 && thirst != 0) {
        stamina = std::max(stamina - usedStamina, 0);
        hunger = std::max(hunger - usedHunger, 0);
        thirst = std::max(thirst - usedThirst, 0);
    }
    else {
        health = std::max(health - usedHealth, 0);
        stamina = std::max(stamina - usedStamina, 0);
        hunger = std::max(hunger - usedHunger, 0);
        thirst = std::max(thirst - usedThirst, 0);
    }

    exp += expEarned;
    money += moneyEarned;
}

void Player::sleep() {
    this->thirst -= calculateRandomCharacteristic(35, 40);
    this->hunger -= calculateRandomCharacteristic(35, 40);
    this->stamina = this->staminaMax;
    this->health += calculateRandomCharacteristic(20, 40);
}

int Player::calculateRandomCharacteristic(int leftBorder, int rightBorder) const {
    return rand() % (rightBorder - leftBorder + 1) + leftBorder;
}

void Player::useProduct(std::shared_ptr<Item> &item) {
    std::shared_ptr<Product> product = std::dynamic_pointer_cast<Product>(item);
    this->hunger = std::min(this->hunger + product->getHungerRestored(), 100);
    this->stamina = std::min(this->stamina + product->getEnergyRestored(), 100);
    this->health = std::min(this->health + product->getHealthRestored(), 100);
    this->thirst = std::min(this->thirst + product->getThirstRestored(), 100);
    this->radiation += product->getRadiationRestored();
}