#include "Player.hpp"

Player::Player()
    : Entity{ def_name, def_health, def_max_health, def_min_damage, def_max_damage, def_level, def_defence },
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
    radiation{ def_radiation },
    distanceTravelled{ def_distance_travelled },
    weapon{ std::make_shared<Weapon>() },
    armorHead{ std::make_shared<Armor>() },
    armorChest{ std::make_shared<Armor>() },
    armorLeggs{ std::make_shared<Armor>() },
    armorBoots{ std::make_shared<Armor>() } {}

void Player::initialize(const std::string &name) {
    this->name = name;
    this->maxHealth = def_max_health + (int)(vitality / 2) - 2;
    this->health = this->maxHealth;
    this->thirst = def_thirst;
    this->thirstMax = def_thirst_max;
    this->hunger = def_hunger;
    this->hungerMax = def_hunger_max;
    this->minDamage = def_min_damage + (int)(strength / 2) - 2;
    this->maxDamage = def_max_damage + (int)(strength / 2) - 2;
    this->exp = def_exp;
    this->expNext = (def_exp_next * (level - 1) + def_exp_next * (level - 1) * 0.5) + 100; //+150 exp to next level per level
    this->level = def_level;
    this->staminaMax = def_stamina_max + (int)(dexterity / 2) - 2;
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
    this->distanceTravelled = def_distance_travelled;
    this->radiation = def_radiation;
    this->inventory.initialize();
    this->weapon = def_weapon;
    this->armorHead = def_armor;
    this->armorChest = def_armor;
    this->armorLeggs = def_armor;
    this->armorBoots = def_armor;
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
    for(const auto &item : this->inventory.getItems()) {
        if(item->getStatus() == "Equipped") {
            if(*item == *weapon) 
                weapon = item;
            else if(*item == *armorHead)
                armorHead = item;
            else if(*item == *armorChest)
                armorChest = item;
            else if(*item == *armorLeggs)
                armorLeggs = item;
            else if(*item == *armorBoots)
                armorBoots = item;
        }
    }
}

void Player::printStats() const {
    CLEAR_SCREEN;
    int labelSize{ 25 }, valueSize{ 30 };
    printDivider('=', labelSize + valueSize + 4);
    std::cout << std::right << std::setw(labelSize) << std::setfill('=') << " " << std::setw(valueSize + 3) << std::left << "My stats " << std::endl;
    printDivider('=', labelSize + valueSize + 4);
    printFormattedLine("== Name:", "| " + this->name, labelSize, valueSize);
    printFormattedLine("== Level:", "| " + std::to_string(this->level) + " (" + std::to_string(this->exp) + " / " + std::to_string(this->expNext) + ")", labelSize, valueSize);
    printFormattedLine("== Health:", "| " + std::to_string(this->health) + " / " + std::to_string(this->maxHealth), labelSize, valueSize);
    printFormattedLine("== Stamina:", "| " + std::to_string(this->stamina) + " / " + std::to_string(this->staminaMax), labelSize, valueSize);
    printFormattedLine("== Hunger:", "| " + std::to_string(this->hunger) + " / " + std::to_string(this->hungerMax), labelSize, valueSize);
    printFormattedLine("== Thirst:", "| " + std::to_string(this->thirst) + " / " + std::to_string(this->thirstMax), labelSize, valueSize);
    printFormattedLine("== Radiation:", "| " + std::to_string(this->radiation), labelSize, valueSize);
    printFormattedLine("== G:", "| " + std::to_string(this->money), labelSize, valueSize);
    printFormattedLine("== Damage:", "| " + std::to_string(this->minDamage) + " / " + std::to_string(this->maxDamage), labelSize, valueSize);
    printFormattedLine("== Defence:", "| " + std::to_string(this->defence), labelSize, valueSize);
    printFormattedLine("== Strength:", "| " + std::to_string(this->strength), labelSize, valueSize);
    printFormattedLine("== Vitality:", "| " + std::to_string(this->vitality), labelSize, valueSize);
    printFormattedLine("== Dexterity:", "| " + std::to_string(this->dexterity), labelSize, valueSize);
    printFormattedLine("== Intelligence:", "| " + std::to_string(this->intelligence), labelSize, valueSize);
    printFormattedLine("== Luck:", "| " + std::to_string(this->luck), labelSize, valueSize);
    printFormattedLine("== Stats points:", "| " + std::to_string(this->statPoints), labelSize, valueSize);
    printFormattedLine("== Equipped weapon:", "| " + this->weapon->getName(), labelSize, valueSize);
    printFormattedLine("== Equipped helmet:", "| " + this->armorHead->getName(), labelSize, valueSize);
    printFormattedLine("== Equipped chestplate:", "| " + this->armorChest->getName(), labelSize, valueSize);
    printFormattedLine("== Equipped leggings:", "| " + this->armorLeggs->getName(), labelSize, valueSize);
    printFormattedLine("== Equipped boots:", "| " + this->armorBoots->getName(), labelSize, valueSize);
    printDivider('=', labelSize + valueSize + 4);
    std::cout << std::setfill(' ');
}

void Player::previewPlayer() const {
    printDivider('=', 41);
    std::cout << std::left << std::setw(40) << "== " + this->name + " " << std::endl;
    std::cout << std::left << std::setw(40) << formatLabelValue("Level", std::to_string(this->level)) << std::endl;
    printDivider('=', 41);
    std::cout << std::left << std::setw(40) << formatLabelValue("Hp", std::to_string(this->health) + "/" + std::to_string(this->maxHealth) + " | Radiation: " + std::to_string(this->radiation)) << std::endl;
    std::cout << std::left << std::setw(40) << formatLabelValue("Stamina", std::to_string(this->stamina) + "/" + std::to_string(this->staminaMax)) << std::endl;
    std::cout << std::left << std::setw(40) << formatLabelValue("Hunger", std::to_string(this->hunger) + "/" + std::to_string(this->hungerMax) + " | Thirst: " + std::to_string(this->thirst) + "/" + std::to_string(this->thirstMax)) << std::endl;
    printDivider('=', 41);
    std::cout << std::setfill(' ') << std::endl;
}

void Player::sleep() {
    if(thirst >= MIN_ATTRIBUTE_VALUE_FOR_SLEEP && hunger >= MIN_ATTRIBUTE_VALUE_FOR_SLEEP) {
        const int thirstDecrease = getRandomNumberInRange(35, MIN_ATTRIBUTE_VALUE_FOR_SLEEP);
        const int hungerDecrease = getRandomNumberInRange(35, MIN_ATTRIBUTE_VALUE_FOR_SLEEP);
        const int healthIncrease = getRandomNumberInRange(20, 40);
        const int radiationDecrease = getRandomNumberInRange(0, 4);

        decreaseVitalAttribute(this->thirst, thirstDecrease);
        decreaseVitalAttribute(this->hunger, hungerDecrease);
        decreaseVitalAttribute(this->radiation, radiationDecrease);
        this->stamina = this->staminaMax;
        this->health = std::min(this->health + healthIncrease, this->maxHealth);
        std::cout << "I slept well. My energy are restored" << std::endl << std::endl;
    }
    else
        std::cout << "I need to raise my hunger and thirst to " << MIN_ATTRIBUTE_VALUE_FOR_SLEEP << " or I won't be able to sleep" << std::endl << std::endl;
}

void Player::explore() {
    this->distanceTravelled++;
    const int usedRadiation = getRandomNumberInRange(0, 6) == 0 ? 1 : 0;
    const int usedStamina = getRandomNumberInRange(7, 11);
    const int usedHunger = getRandomNumberInRange(2, 6);
    const int usedThirst = getRandomNumberInRange(2, 6);

    decreaseVitalAttribute(stamina, usedStamina);
    decreaseVitalAttribute(hunger, usedHunger);
    decreaseVitalAttribute(thirst, usedThirst);
    radiation = std::min(radiation + usedRadiation, MAX_RADIATION);
    
    if(stamina == MIN_ATTRIBUTE_VALUE || hunger == MIN_ATTRIBUTE_VALUE || thirst == MIN_ATTRIBUTE_VALUE) {
        const int usedHealth = getRandomNumberInRange(4, 10);
        decreaseVitalAttribute(health, usedHealth);
        std::cout << "I feel bad. I need to eat, drink and rest regularly, otherwise I will start to lose hp" << std::endl;
    }

    exp += getRandomNumberInRange(MIN_EXP_GAIN + (3 * this->level), MAX_EXP_GAIN + (3 * this->level));
    money += getRandomNumberInRange(MIN_MONEY_GAIN + (this->luck * 2), MAX_MONEY_GAIN + (this->luck * 2));

    if(radiation >= RADIATION_THRESHOLD) {
        std::cout << "High radiation. I feel bad. I need to reduce radiation, or I will die." << std::endl;
        decreaseVitalAttribute(hunger, HIGH_RADIATION_REDUCTION);
        decreaseVitalAttribute(thirst, HIGH_RADIATION_REDUCTION);
        decreaseVitalAttribute(health, HIGH_RADIATION_REDUCTION);
    }
}

void Player::decreaseVitalAttribute(int &attribute, int amount) {
    attribute = std::max(attribute - amount, MIN_ATTRIBUTE_VALUE);
}

void Player::levelUp() {
    if(exp >= expNext) {
        level++;
        skillPoints++;
        statPoints += STAT_POINTS_PER_LEVEL;
        exp -= expNext;
        expNext = (def_exp_next * (level - 1) + def_exp_next * (level - 1) * 0.5) + def_exp_next;
        restoreVitalAttributes();
        printLevelUpMessage();
    }
}

void Player::restoreVitalAttributes() {
    this->hunger = this->hungerMax;
    this->thirst = this->thirstMax;
    this->health = this->maxHealth;
    this->stamina = this->staminaMax;
    int radiationDecreased = getRandomNumberInRange(0, 5);
    decreaseVitalAttribute(this->radiation, radiationDecreased);
}

void Player::printLevelUpMessage() const {
    printDivider('=', 110);
    std::cout << "LEVEL UP!" << std::endl;
    std::cout << "Congratulations! My level has increased to " << this->level << ". I've also received 5 extra stat points to allocate." << std::endl;
    std::cout << "I now have a total of " << this->statPoints << " stat points available for further improvement." << std::endl;
    std::cout << "All my vital parameters have been fully restored." << std::endl;
    printDivider('=', 110);
    std::cout << std::endl;
}

void Player::increaseStatAttributes() {
    CLEAR_SCREEN;
    int continueChoice{};
    do {
        if(this->statPoints > 0) {
            printAttributeOptions();
            AttributeChoice attributeChoice = static_cast<AttributeChoice>(getValidatedAnswer("\nEnter which attribute I should increase: ", "\nInvalid choice. I don't have such an attribute.", 1, 5));
            switch(attributeChoice) {
                case AttributeChoice::STRENGTH:     increaseStatAttribute(this->strength, "Strength"); break;
                case AttributeChoice::VITALITY:     increaseStatAttribute(this->vitality, "Vitality"); break;
                case AttributeChoice::DEXTERITY:    increaseStatAttribute(this->dexterity, "Dexterity"); break;
                case AttributeChoice::INTELLIGENCE: increaseStatAttribute(this->intelligence, "Intelligence"); break;
                case AttributeChoice::LUCK:         increaseStatAttribute(this->luck, "Luck"); break;
                default: std::cout << "\nInvalid attribute choice" << std::endl; break;
            }
        }
        else {
            std::cout << "I don't have enough points to update my attributes" << std::endl << std::endl;
            return;
        }

        if(this->statPoints > 0) {
            continueChoice = askYesNo("\nShould I continue?");
            if(continueChoice == 0)
                return;
        }
    } while(this->statPoints > 0 && continueChoice != 0);
}

void Player::printAttributeOptions() const {
    std::cout << "(1) - Strength (Increase damage)" << std::endl
              << "(2) - Vitality (Increase health)" << std::endl
              << "(3) - Dexterity (Increase stamina)" << std::endl
              << "(4) - Intelligence (Increase defence)" << std::endl
              << "(5) - Luck (Increase received G and exp)" << std::endl;
}

void Player::increaseStatAttribute(int &attribute, const std::string &attributeName) {
    attribute++;
    this->statPoints--;
    this->updateCharacteristics();
    std::cout << "\nI have increased " << attributeName << ". I have " << this->statPoints << " points left.\n";
}

void Player::updateCharacteristics() {
    const int maxHealthBonus = calculateAttributeBonus(vitality), staminaMaxBonus = calculateAttributeBonus(dexterity);
    const int minDamageBonus = calculateAttributeBonus(strength), maxDamageBonus = calculateAttributeBonus(strength);
    const int defenceBonus = calculateAttributeBonus(intelligence);
    
    const int previousMaxHealth = this->maxHealth;
    this->maxHealth = def_max_health + maxHealthBonus;
    if(this->health == previousMaxHealth)
        this->health = this->maxHealth;

    const int previousStaminaMax = this->staminaMax;
    this->staminaMax = def_stamina_max + staminaMaxBonus;
    if(stamina == previousStaminaMax)
        this->stamina = this->staminaMax;

    this->minDamage = def_min_damage + minDamageBonus;
    this->maxDamage = def_max_damage + maxDamageBonus;
    this->defence = def_defence + defenceBonus;
}

int Player::calculateAttributeBonus(const int &attribute) const {
    return (attribute / ATTRIBUTE_BONUS_FACTOR) - (ATTRIBUTE_BASE_VALUE / ATTRIBUTE_BONUS_FACTOR);
}

bool Player::buyItem(std::shared_ptr<Item> &item) {
    const int purchasePrice = item->getPurchasePrice();
    if(this->money < purchasePrice) {
        std::cout << "I don't have enough G to buy " << item->getName() << std::endl;
        return false;
    }

    if(this->inventory.getItems().size() >= this->inventory.getMaxNumberOfItems()) {
        std::cout << "My backpack is full. I can't buy " << item->getName() << std::endl;
        return false;
    }

    std::cout << "\n/*I've bought the " << item->getName() << "*/" << std::endl;
    this->money -= purchasePrice;
    this->inventory.addItem(item);
    return true;
}

void Player::sellItem(const int &position) {
    std::shared_ptr<Item> &item = this->getInventory().getItems().at(position);
    this->money += item->getSalePrice();
    if(item->getStatus() == "Equipped")
        unequipItem(item);

    this->getInventory().removeItem(position);
}

void Player::equipItem(std::shared_ptr<Item> &item) {
    item->equip();
    Category itemCategory = item->getCategory();

    if(itemCategory == Category::WEAPON)
        equipWeapon(item);
    else if(itemCategory == Category::ARMOR)
        equipArmor(item);
}

void Player::equipWeapon(std::shared_ptr<Item> &item) {
    std::shared_ptr<Weapon> weaponItem = std::dynamic_pointer_cast<Weapon>(item);

    if(!weaponItem) {
        std::cerr << "Bad convert to Weapon" << std::endl;
        return;
    }

    if(this->weapon->getName() != "None")
        unequipItem(this->weapon);

    this->weapon = weaponItem;
    this->minDamage += weaponItem->getMinDamage();
    this->maxDamage += weaponItem->getMaxDamage();
}

void Player::equipArmor(std::shared_ptr<Item> &item) {
    std::shared_ptr<Armor> armorItem = std::dynamic_pointer_cast<Armor>(item);

    if(!armorItem) {
        std::cerr << "Bad convert to Armor" << std::endl;
        return;
    }

    ArmorType armorType = armorItem->getType();
    std::map<ArmorType, std::shared_ptr<Item>&> armorSlots = {
        {ArmorType::HELMET, this->armorHead},
        {ArmorType::CHESTPLATE, this->armorChest},
        {ArmorType::LEGGINGS, this->armorLeggs},
        {ArmorType::BOOTS, this->armorBoots}
    };

    auto it = armorSlots.find(armorType);
    if(it != armorSlots.end()) {
        if(it->second->getName() != "None")
            unequipItem(it->second);
        it->second = armorItem;
    }

    this->defence += armorItem->getDefence();
}

void Player::unequipItem(std::shared_ptr<Item> &item) {
    item->unequip();
    Category itemCategory = item->getCategory();

    if(itemCategory == Category::WEAPON)
        unequipWeapon(item);
    else if(itemCategory == Category::ARMOR)
        unequipArmor(item);
}

void Player::unequipWeapon(std::shared_ptr<Item> &item) {
    std::shared_ptr<Weapon> weaponItem = std::dynamic_pointer_cast<Weapon>(item);
    if(!weaponItem) {
        std::cerr << "Bad convert to Weapon" << std::endl;
        return;
    }

    this->weapon = def_weapon;
    this->minDamage -= weaponItem->getMinDamage();
    this->maxDamage -= weaponItem->getMaxDamage();
}

void Player::unequipArmor(std::shared_ptr<Item> &item) {
    std::shared_ptr<Armor> armorItem = std::dynamic_pointer_cast<Armor>(item);

    if(!armorItem) {
        std::cerr << "Bad convert to Armor" << std::endl;
        return;
    }

    ArmorType armorType = armorItem->getType();
    std::map<ArmorType, std::shared_ptr<Item> &> armorSlots = {
        {ArmorType::HELMET, this->armorHead},
        {ArmorType::CHESTPLATE, this->armorChest},
        {ArmorType::LEGGINGS, this->armorLeggs},
        {ArmorType::BOOTS, this->armorBoots}
    };

    auto it = armorSlots.find(armorType);
    if(it != armorSlots.end())
        it->second = def_armor;

    this->defence -= armorItem->getDefence();
}

void Player::useProduct(std::shared_ptr<Item> &item) {
    std::shared_ptr<Product> product = std::dynamic_pointer_cast<Product>(item);
    this->hunger = std::min(this->hunger + product->getHungerRestored(), this->hungerMax);
    this->stamina = std::min(this->stamina + product->getEnergyRestored(), this->staminaMax);
    this->health = std::min(this->health + product->getHealthRestored(), this->maxHealth);
    this->thirst = std::min(this->thirst + product->getThirstRestored(), this->thirstMax);
    this->radiation = std::max(this->radiation + product->getRadiationRestored(), MIN_ATTRIBUTE_VALUE);
}

void Player::restoreStaminaInCombat() {
    int staminaRestored = getRandomNumberInRange(40, 50);
    this->stamina = std::min(this->staminaMax, this->stamina + staminaRestored);
    this->hunger = std::max(MIN_ATTRIBUTE_VALUE, this->hunger - getRandomNumberInRange(8, 12));
    this->thirst = std::max(MIN_ATTRIBUTE_VALUE, this->thirst - getRandomNumberInRange(8, 12));

    std::cout << "I restore " << staminaRestored << " stamina" << std::endl;
}

void Player::upgradeItem() {
    CLEAR_SCREEN;
    if(this->inventory.is_empty()) {
        std::cout << "My inventory is empty" << std::endl << std::endl;
        return;
    }
    this->inventory.printInventory();
    int selectedItemIndex = getValidatedAnswer("Choose the item I want to upgrade: ", "Invalid choice", 0, this->inventory.getItems().size());
    if(selectedItemIndex == 0)
        return;

    std::shared_ptr<Item> &item = this->inventory.getItems()[selectedItemIndex - 1];
    if(item->getCategory() == Category::PRODUCT) {
        std::cout << "\nI can't upgrade products" << std::endl;
        return;
    }

    const int moneyToSpend = item->getPurchasePrice() / 10;
    std::cout << "To upgrade " << item->getName() << " I need to spend " << moneyToSpend << " G" << std::endl;

    int choice = askYesNo("Should I do it?");
    if(choice == 2)
        return;
    if(moneyToSpend > this->money) {
        std::cout << "I don't have enough G to spend" << std::endl;
        return;
    }

    this->money -= moneyToSpend;

    std::string status = item->getStatus();
    if(status == "Equipped")
        unequipItem(item);
    item->upgrade();
    if(status == "Equipped")
        equipItem(item);
}

void Player::printInventory() {
    CLEAR_SCREEN;
    if(this->inventory.is_empty()) {
        std::cout << "\My inventory is empty\n" << std::endl;
        return;
    }

    int selectedItemIndex{};
    do {
        CLEAR_SCREEN;
        this->inventory.printInventory();
        if(this->inventory.is_empty())
            return;
        
        selectedItemIndex = getValidatedAnswer("Your choice: ", "Invalid choice", 0, this->inventory.getItems().size());
        if(selectedItemIndex == 0) {
            CLEAR_SCREEN;
            return;
        }
       
        std::shared_ptr<Item> &selectedItem = this->inventory.getItems().at(selectedItemIndex - 1);
        std::cout << *selectedItem << std::endl;
        int choice{};
        if(selectedItem->getCategory() == Category::PRODUCT) {
            choice = askYesNo("Should I use this item?");
            if(choice == 1) {
                this->useProduct(selectedItem);
                this->getInventory().removeItem(selectedItemIndex - 1);
            }
        }
        else {
            std::string status = selectedItem->getStatus();
            if(status == "Equipped") {
                choice = askYesNo("Should I unequip this item?");
                if(choice == 1) 
                    unequipItem(selectedItem);
            }
            else {
                choice = askYesNo("Should I equip this item?");
                if(choice == 1)
                    equipItem(selectedItem);
            }
        }
    } while(selectedItemIndex != 0);
}

bool Player::useItemInCombat() {
    if(this->getInventory().is_empty()) {
        std::cout << "My Inventory is empty" << std::endl;
        return false;
    }
    std::cout << "\nI can use only one item per turn!" << std::endl;

    this->inventory.printInventory();
    int selectedItemIndex{};
    selectedItemIndex = getValidatedAnswer("Your choice: ", "Invalid choice", 0, this->inventory.getItems().size());
    if(selectedItemIndex == 0) {
        return false;
    }

    int choice{};
    do {
        CLEAR_SCREEN;
        std::shared_ptr<Item> &selectedItem = this->inventory.getItems().at(selectedItemIndex - 1);
        std::cout << *selectedItem << std::endl;

        if(selectedItem->getCategory() == Category::PRODUCT) {
            choice = askYesNo("Should I use this item?");
            if(choice == 1) {
                this->useProduct(selectedItem);
                this->getInventory().removeItem(selectedItemIndex - 1);
                return true;
            }
        }
        else {
            if(selectedItem->getStatus() == "Equipped") {
                choice = askYesNo("Should I unequip this item?");

                if(choice == 1) {
                    unequipItem(selectedItem);
                    return true;
                }
            }
            else {
                choice = askYesNo("Should I equip this item?");

                if(choice == 1) {
                    equipItem(selectedItem);
                    return true;
                }
            }
        }
    } while(choice != 2);
    return false;
}

bool Player::operator==(const Player &rhs) const {
    if(this->name == rhs.name)
        return true;
    else
        return false;
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

    return *this;
}