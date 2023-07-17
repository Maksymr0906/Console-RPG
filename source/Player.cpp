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
        << "Radiation: " << this->radiation << std::endl
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
        << "Money: " << this->money << std::endl
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
        if(selectedItemIndex == 0) {
            return;
        }
        else {
            std::shared_ptr<Item> &selectedItem = this->inventory.getInventory().at(selectedItemIndex - 1);
            std::cout << *selectedItem << std::endl;
            int choice{};
            //std::cout << "\n(0) - Go back\n(1) - Equip/Use\n(2) - Info\n(3) - Delete Item\n";
            if(selectedItem->getCategory() == "Product") {
                choice = getValidateAnswer("Do you want to use this item?\n(1) - Yes\n(2) - No\nYour choice: ", "Incorrect choice", 1, 2);
                if(choice == 1) {
                    this->useProduct(selectedItem);
                    this->getInventory().removeItem(selectedItemIndex - 1);
                    continue;
                }
            }
            else {
                if(selectedItem->getStatus() == "Equipped") {
                    choice = getValidateAnswer("Do you want to unequip this item?\n(1) - Yes\n(2) - No\nYour choice: ", "Incorrect choice", 1, 2);

                    if(choice == 1) {
                        unequipItem(selectedItem);
                    }
                }
                else {
                    choice = getValidateAnswer("Do you want to equip this item?\n(1) - Yes\n(2) - No\nYour choice: ", "Incorrect choice", 1, 2);

                    if(choice == 1) {
                        equipItem(selectedItem);
                    }
                }
            }
        }
    } while(selectedItemIndex != 0);
}

bool Player::useItemInCombat() {
    if(this->getInventory().is_empty()) {
        std::cout << "\nMy Inventory is empty" << std::endl;
        return false;
    }
    std::cout << "\nI can use only one item per turn!" << std::endl;
    
    this->inventory.showInventory();
    int selectedItemIndex{};
    selectedItemIndex = getValidateAnswer("Your choice: ", "Incorrect choice", 0, this->inventory.getInventory().size());
    if(selectedItemIndex == 0) {
        return false;
    }

    int choice{};
    do {
        std::shared_ptr<Item> &selectedItem = this->inventory.getInventory().at(selectedItemIndex - 1);
        std::cout << *selectedItem << std::endl;

        if(selectedItem->getCategory() == "Product") {
            choice = getValidateAnswer("Should I use this item?\n(1) - Yes\n(2) - No\nYour choice: ", "Incorrect choice", 1, 2);
            if(choice == 1) {
                this->useProduct(selectedItem);
                this->getInventory().removeItem(selectedItemIndex - 1);
                return true;
            }
        }
        else {
            if(selectedItem->getStatus() == "Equipped") {
                choice = getValidateAnswer("Should I unequip this item?\n(1) - Yes\n(2) - No\nYour choice: ", "Incorrect choice", 1, 2);

                if(choice == 1) {
                    unequipItem(selectedItem);
                    return true;
                }
            }
            else {
                choice = getValidateAnswer("Should I equip this item?\n(1) - Yes\n(2) - No\nYour choice: ", "Incorrect choice", 1, 2);

                if(choice == 1) {
                    equipItem(selectedItem);
                    return true;
                }
            }
        }
    } while(choice != 2);
    return false;
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
    std::cout << std::left << std::setw(40) << "== Level: " + std::to_string(this->level) + " " << std::endl;
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

void Player::takeDamage(int damage) {
    int effectiveDamage = std::max(damage - (defence / 3), 0);
    this->health = std::max(this->health - effectiveDamage, 0);
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
    this->weapon->readFromTxtFile(infile);
    infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    this->armorHead->readFromTxtFile(infile);
    infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    this->armorChest->readFromTxtFile(infile);
    infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    this->armorLeggs->readFromTxtFile(infile);
    infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    this->armorBoots->readFromTxtFile(infile);

    for(const auto &item : this->inventory.getInventory()) {
        if(item->getStatus() == "Equipped") {
            if(*item == *weapon) {
                weapon.reset();
                weapon = item;
            }
            else if(*item == *armorHead) {
                armorHead.reset();
                armorHead = item;
            }
            else if(*item == *armorChest) {
                armorChest.reset();
                armorChest = item;
            }
            else if(*item == *armorLeggs) {
                armorLeggs.reset();
                armorLeggs = item;
            }
            else if(*item == *armorBoots) {
                armorBoots.reset();
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
        std::cout << "\nLEVEL UP!" << std::endl;
        std::cout << "Congratulations! Your level has increased to " << this->level << ". You have also received 5 extra stat points to allocate." << std::endl;
        std::cout << "You now have a total of " << this->statPoints << " stat points available for further improvement." << std::endl;
        std::cout << "All your vital parameters have been fully restored." << std::endl;
    }
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
        if(this->statPoints > 0) {
            std::cout << "\nYou have " << this->statPoints << " points left.\nDo you want to continue? (y/n)";
            std::cin >> continueChoice;
        }
        else {
            std::cout << "\nYou don't have enough stat points" << std::endl;
            break;
        }
    } while(this->statPoints > 0 && continueChoice != 'n');
}

void Player::updateCharacteristics() {
    this->maxHealth = def_max_health + (int)(vitality / 2) - 2;
    this->minDamage = def_min_damage + (int)(strength / 4 + vitality / 4) - 2;
    this->maxDamage = def_max_damage + (int)(strength / 4 + vitality / 4) - 2;
    this->staminaMax = def_stamina_max + (int)(dexterity / 2) - 2;
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

void Player::sellItem(const int &position) {
    std::shared_ptr<Item> &item = this->getInventory().getInventory()[position];
    this->money = this->money + this->getInventory().getInventory()[position]->getSalePrice();
    if(this->getInventory().getInventory()[position]->getStatus() == "Equipped") {
        unequipItem(this->getInventory().getInventory()[position]);
    }
    this->getInventory().removeItem(position);
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
    int usedRadiation = rand() % 4 == 0? 1 : 0;
    int usedStamina = calculateRandomCharacteristic(7, 11);
    int usedHunger = calculateRandomCharacteristic(2, 6);
    int usedThirst = calculateRandomCharacteristic(2, 6);
    int usedHealth = calculateRandomCharacteristic(4, 10);

    if(stamina != 0 && hunger != 0 && thirst != 0) {
        stamina = std::max(stamina - usedStamina, 0);
        hunger = std::max(hunger - usedHunger, 0);
        thirst = std::max(thirst - usedThirst, 0);
        radiation = std::min(radiation + usedRadiation, 15);
    }
    else {
        health = std::max(health - usedHealth, 0);
        stamina = std::max(stamina - usedStamina, 0);
        hunger = std::max(hunger - usedHunger, 0);
        thirst = std::max(thirst - usedThirst, 0);
        radiation = std::min(radiation + usedRadiation, 15);

    }

    exp += calculateRandomCharacteristic(5 + (3 * this->level), 10 + (3 * this->level));
    money += calculateRandomCharacteristic(20 + (this->luck * 2), 30 + (this->luck * 2));

    if(radiation >= 10) {
        std::cout << "High radiation. I feel bad. I need to reduce radiation, or I will die." << std::endl;
        hunger = std::max(hunger - 10, 0);
        thirst = std::max(thirst - 10, 0);
        health = std::max(health - 10, 0);
    }
}

void Player::sleep() {
    this->thirst = std::max(this->thirst - calculateRandomCharacteristic(35, 40), 0);
    this->hunger = std::max(this->hunger - calculateRandomCharacteristic(35, 40), 0);
    this->stamina = this->staminaMax;
    this->health = std::min(100, this->health + calculateRandomCharacteristic(20, 40));
}

void Player::useProduct(std::shared_ptr<Item> &item) {
    std::shared_ptr<Product> product = std::dynamic_pointer_cast<Product>(item);
    this->hunger = std::min(this->hunger + product->getHungerRestored(), 100);
    this->stamina = std::min(this->stamina + product->getEnergyRestored(), 100);
    this->health = std::min(this->health + product->getHealthRestored(), 100);
    this->thirst = std::min(this->thirst + product->getThirstRestored(), 100);
    this->radiation = std::max(this->radiation + product->getRadiationRestored(), 0);
}

void Player::restoreStaminaInCombat() {
    this->stamina = std::min(100, this->stamina + calculateRandomCharacteristic(40, 50));

    this->hunger = std::max(0, this->hunger - calculateRandomCharacteristic(8, 12));
    this->thirst = std::max(0, this->thirst - calculateRandomCharacteristic(8, 12));
}

void Player::upgradeItems() {
    if(this->inventory.is_empty()) {
        std::cout << "\nYour inventory is empty\n" << std::endl;
        return;
    }

    int selectedItemIndex{};

    this->inventory.showInventory();
    selectedItemIndex = getValidateAnswer("Choose the item I want to upgrade: ", "Incorrect choice", 0, this->inventory.getInventory().size());

    if(selectedItemIndex == 0)
        return;
    if(this->inventory.getInventory()[selectedItemIndex - 1]->getCategory() == "Product") {
        std::cout << "I can't upgrade products!" << std::endl;
    }
    else if(this->inventory.getInventory()[selectedItemIndex - 1]->getCategory() == "Weapon") {
        upgradeWeapon(selectedItemIndex - 1);
    }
    else if(this->inventory.getInventory()[selectedItemIndex - 1]->getCategory() == "Armor") {
        upgradeArmor(selectedItemIndex - 1);
    }
}

void Player::upgradeWeapon(int indexOfWeapon) {
    std::shared_ptr<Weapon> weaponToUpgrade = std::dynamic_pointer_cast<Weapon>(this->inventory.getInventory()[indexOfWeapon]);
    int spendedMoney = weaponToUpgrade->getPurchasePrice() / 10;
    std::cout << "To upgrade " << weaponToUpgrade->getName() << " I need to spend " << spendedMoney << " money" << std::endl;
    int choice = getValidateAnswer("Should I do it?\n(1) - Yes\n(2) - No\nYour choice: ", "Incorrect choice", 1, 2);
    if(choice == 2)
        return;
    if(spendedMoney > this->money) {
        std::cout << "I don't have enough resources to spend" << std::endl;
        return;
    }
    std::cout << "I need to unequip item before I upgrade him" << std::endl;
    unequipItem(this->inventory.getInventory()[indexOfWeapon]);

    int minDamageAdded = std::max(weaponToUpgrade->getMinDamage() / 10, 1);
    int maxDamageAdded = std::max(weaponToUpgrade->getMaxDamage() / 10, 1);
    int purchasePriceAdded = std::max(weaponToUpgrade->getPurchasePrice() / 10, 80);
    int salePriceAdded = std::max(weaponToUpgrade->getSalePrice() / 10, 40);
    weaponToUpgrade->setPurchasePrice(weaponToUpgrade->getPurchasePrice() + purchasePriceAdded);
    weaponToUpgrade->setSalePrice(weaponToUpgrade->getSalePrice() + salePriceAdded);
    weaponToUpgrade->setMinDamage(weaponToUpgrade->getMinDamage() + minDamageAdded);
    weaponToUpgrade->setMaxDamage(weaponToUpgrade->getMaxDamage() + maxDamageAdded);
    this->money -= spendedMoney;

    std::cout << "I upgraded " << weaponToUpgrade->getName() << " and damage upgraded on " << minDamageAdded << " / " << maxDamageAdded << std::endl;
    equipItem(this->inventory.getInventory()[indexOfWeapon]);
}

void Player::upgradeArmor(int indexOfArmor) {
    std::shared_ptr<Armor> armorToUpgrade = std::dynamic_pointer_cast<Armor>(this->inventory.getInventory()[indexOfArmor]);
    int spendedMoney = armorToUpgrade->getPurchasePrice() / 10;
    std::cout << "To upgrade " << armorToUpgrade->getName() << " I need to spend " << spendedMoney << "money" << std::endl;
    int choice = getValidateAnswer("Should I do it?\n(1) - Yes\n(2) - No\nYour choice: ", "Incorrect choice", 1, 2);
    if(choice == 2)
        return;
    if(spendedMoney > this->money) {
        std::cout << "I don't have enough resources to spend" << std::endl;
        return;
    }
    unequipItem(this->inventory.getInventory()[indexOfArmor]);

    int defenceAdded = std::max(armorToUpgrade->getDefence() / 10, 1);
    int purchasePriceAdded = std::max(armorToUpgrade->getPurchasePrice() / 10, 80);
    int salePriceAdded = std::max(armorToUpgrade->getSalePrice() / 10, 40);
    armorToUpgrade->setDefence(armorToUpgrade->getDefence() + defenceAdded);
    armorToUpgrade->setPurchasePrice(armorToUpgrade->getPurchasePrice() + purchasePriceAdded);
    armorToUpgrade->setSalePrice(armorToUpgrade->getSalePrice() + salePriceAdded);

    this->money -= spendedMoney;

    std::cout << "I upgraded " << armorToUpgrade->getName() << " and defence upgraded on " << defenceAdded << std::endl;
    equipItem(this->inventory.getInventory()[indexOfArmor]);
}