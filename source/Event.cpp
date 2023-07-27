#include "Event.hpp"

std::vector<std::string> Event::emptyEventMessages;
std::vector<Puzzle> Event::puzzles;
std::vector<std::shared_ptr<Item>> Event::products;
std::vector<std::shared_ptr<Item>> Event::itemsToSell;
std::vector<std::shared_ptr<Item>> Event::weapons;
std::vector<std::shared_ptr<Item>> Event::armor;
std::vector<Enemy> Event::enemies;

Event::Event() {
	this->numberOfEvents = 5;
}

void Event::initialize() {
	try {
		readEnemiesFromFile("Enemies.txt");
		readEmptyEventMessagesFromFile("EmptyEventMessages.txt");
		readPuzzlesFromFile("Puzzle.txt");
		readWeaponsFromFile("Weapons.txt");
		readArmorFromFile("Armor.txt");
		readProductsFromFile("Products.txt");
		generateItemsToSell();
	}
	catch(const std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

void Event::readEnemiesFromFile(const std::string &fileName) {
	std::ifstream infile(fileName);

	if(!infile.is_open())
		throw std::runtime_error("Error opening file: " + fileName);


	Enemy enemy;
	while(!infile.eof()) {
		enemy.readFromTxtFile(infile);
		enemies.push_back(enemy);
		infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	infile.close();
}

void Event::readEmptyEventMessagesFromFile(const std::string &fileName) {
	std::ifstream file(fileName);

	if(!file.is_open())
		throw std::runtime_error("Error opening file: " + fileName);

	std::string message{};
	while(std::getline(file, message)) {
		emptyEventMessages.push_back(message);
	}

	file.close();
}

void Event::readPuzzlesFromFile(const std::string &fileName) {
	std::ifstream infile(fileName);

	if(!infile.is_open())
		throw std::runtime_error("Error opening file: " + fileName);

	while(!infile.eof()) {
		std::string answer{}, question{};
		int indexOfCorrectAnswer{};
		size_t numOfAnswers{};
		std::getline(infile, question);
		infile >> numOfAnswers;
		infile.ignore();

		std::vector<std::string> answers;
		for(size_t i = 0; i < numOfAnswers; i++) {
			std::getline(infile, answer);
			answers.push_back(answer);
		}

		infile >> indexOfCorrectAnswer;
		infile.ignore();

		puzzles.emplace_back(question, indexOfCorrectAnswer, answers);
	}

	infile.close();
}


void Event::readWeaponsFromFile(const std::string &fileName) {
	readItemsFromFile(fileName, weapons);
}

void Event::readArmorFromFile(const std::string &fileName) {
	readItemsFromFile(fileName, armor);
}

void Event::readProductsFromFile(const std::string &fileName) {
	readItemsFromFile(fileName, products);
}

void Event::readItemsFromFile(const std::string &fileName, std::vector<std::shared_ptr<Item>> &items) {
	std::ifstream infile(fileName);

	if(!infile.is_open())
		throw std::runtime_error("Error opening file: " + fileName);

	while(!infile.eof()) {
		std::shared_ptr<Item> item;

		if(fileName == "Weapons.txt")
			item = std::make_shared<Weapon>();
		else if(fileName == "Armor.txt")
			item = std::make_shared<Armor>();
		else if(fileName == "Products.txt")
			item = std::make_shared<Product>();

		item->readFromTxtFile(infile);
		items.push_back(item);
		infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	infile.close();
}

void Event::generateItemsToSell() {
	addRandomItemsToSell(itemsToSell, products);
	addRandomItemsToSell(itemsToSell, weapons);
	addRandomItemsToSell(itemsToSell, armor);
}

void Event::addRandomItemsToSell(std::vector<std::shared_ptr<Item>> &itemsToSell, std::vector<std::shared_ptr<Item>> &items) {
	int i{};
	while(i < MAX_ITEMS_TO_SELL_IN_EACH_CATEGORY) {
		std::shared_ptr<Item> item = getRandomItem(items);
		if(!itemExistsInItemsToSell(itemsToSell, item)) {
			itemsToSell.push_back(item);
			i++;
		}
	}
}

bool Event::itemExistsInItemsToSell(const std::vector<std::shared_ptr<Item>> &itemsToSell, std::shared_ptr<Item> &newItem) {
	return std::any_of(itemsToSell.begin(), itemsToSell.end(), [&](const auto &item) {
		return *item == *newItem;
	});
}

std::shared_ptr<Item> Event::getRandomItem(std::vector<std::shared_ptr<Item>> &items) {
	int randomItemIndex = rand() % items.size();
	if(items[randomItemIndex]->getCategory() == Category::WEAPON)
		return std::make_shared<Weapon>(*dynamic_cast<Weapon *>(items[randomItemIndex].get()));
	else if(items[randomItemIndex]->getCategory() == Category::ARMOR)
		return std::make_shared<Armor>(*dynamic_cast<Armor *>(items[randomItemIndex].get()));
	else if(items[randomItemIndex]->getCategory() == Category::PRODUCT)
		return std::make_shared<Product>(*dynamic_cast<Product *>(items[randomItemIndex].get()));
}

void Event::generateEvent(Player &p) {
	RandomEvent randomEvent = calculateRandomEvent();

	switch(randomEvent) {
		case RandomEvent::EMPTY_EVENT:
			emptyEventEncouter();
			break;
		case RandomEvent::PUZZLE:
			puzzleEncouter(p);
			break;
		case RandomEvent::FOUND_ITEM:
			foundItemEncouter(p);
			break;
		case RandomEvent::FIGHT:
			fightEncouter(p);
			break;
		default:
			break;
	}
}

RandomEvent Event::calculateRandomEvent() const {
	int event = rand() % 100 + 1;
	if(event <= 60)
		return RandomEvent::EMPTY_EVENT;
	else if(event <= 75)
		return RandomEvent::PUZZLE;
	else if(event <= 90)
		return RandomEvent::FOUND_ITEM;
	else
		return RandomEvent::FIGHT;
}

void Event::emptyEventEncouter() const {
	std::cout << emptyEventMessages[std::rand() % emptyEventMessages.size()] << std::endl;
}

void Event::puzzleEncouter(Player &p) {
	Puzzle puzzle = getRandomPuzzle();
	int playerAnswer{};
	size_t remainingChances{ puzzle.getNumberOfAnswers() - 1 };

	while(remainingChances > 0) {
		std::cout << puzzle.getAsString() << std::endl;
		printPuzzleChances(remainingChances);
		remainingChances--;

		playerAnswer = getValidatedAnswer("Your answer: ", "\nChoose one from the given variants\n", 1, puzzle.getNumberOfAnswers()) - 1;

		if(playerAnswer == puzzle.getIndexOfCorrectAnswer()) {
			completePuzzle(p);
			return;
		}
	}

	std::cout << "Unfortunately, my attempt to open the safe was unsuccessful." << std::endl;
}

void Event::completePuzzle(Player &p) const {
	CLEAR_SCREEN;
	int rewardMultiplier = (p.getLevel() + (p.getLuck() / 2));
	int expGained = getRandomNumberInRange(MIN_REWARD_FOR_COMPLETED_PUZZLE * rewardMultiplier, MAX_REWARD_FOR_COMPLETED_PUZZLE * rewardMultiplier);
	int moneyGained = getRandomNumberInRange(MIN_REWARD_FOR_COMPLETED_PUZZLE * rewardMultiplier, MAX_REWARD_FOR_COMPLETED_PUZZLE * rewardMultiplier);
	p.setExp(p.getExp() + expGained);
	p.setMoney(p.getMoney() + moneyGained);
	std::cout << "I chose the right answer, the safe opened and I received " << expGained << " exp and " << moneyGained << " G" << std::endl;
}

Puzzle Event::getRandomPuzzle() const {
	return puzzles[std::rand() % puzzles.size()];
}

void Event::printPuzzleChances(const int &remainingChances) const {
	if(remainingChances > 1)
		std::cout << "I have " << remainingChances << " attempts left to crack the safe.I have to choose my next answer wisely!" << std::endl << std::endl;
	else
		std::cout << "I only have 1 try remaining before the safe locks permanently." << std::endl << std::endl;
}

void Event::foundItemEncouter(Player &p) {
	Category category = getRandomCategory();
	try {
		if(category == Category::WEAPON)
			foundWeapon(p);
		else if(category == Category::ARMOR)
			foundArmor(p);
		else if(category == Category::PRODUCT)
			foundProduct(p);
	}
	catch(const std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

Category Event::getRandomCategory() const {
	int x = rand() % 10;
	if(x < 2)
		return Category::WEAPON;
	else if(x < 6)
		return Category::PRODUCT;

	return Category::ARMOR;
}

void Event::foundWeapon(Player &p) const {
	foundItem(p, weapons);
}

void Event::foundArmor(Player &p) const {
	foundItem(p, armor);
}

void Event::foundProduct(Player &p) const {
	foundItem(p, products);
}

void Event::foundItem(Player &p, const std::vector<std::shared_ptr<Item>> &items) const {
	if(items.empty())
		return;

	int randomIndex = std::rand() % items.size();
	std::shared_ptr<Item> newItem = getFoundItem(items, randomIndex);
	printMessageAboutFoundItem("FoundItemMessages.txt", newItem->getName());
	p.getInventory().addItem(newItem);
}

std::shared_ptr<Item> Event::getFoundItem(const std::vector<std::shared_ptr<Item>> &items, const int &foundItemIndex) const {
	if(items[foundItemIndex]->getCategory() == Category::WEAPON)
		return std::make_shared<Weapon>(*dynamic_cast<Weapon *>(items[foundItemIndex].get()));
	else if(items[foundItemIndex]->getCategory() == Category::ARMOR)
		return std::make_shared<Armor>(*dynamic_cast<Armor *>(items[foundItemIndex].get()));
	else if(items[foundItemIndex]->getCategory() == Category::PRODUCT)
		return std::make_shared<Product>(*dynamic_cast<Product *>(items[foundItemIndex].get()));
}

void Event::printMessageAboutFoundItem(const std::string &fileName, const std::string &nameOfItem) const {
	const std::string filePath = fileName;
	std::ifstream file(filePath);
	if(!file.is_open())
		throw std::runtime_error("Error opening file: " + fileName);

	std::vector<std::string> messages;
	std::string message;
	while(std::getline(file, message))
		messages.push_back(message);

	file.close();

	std::string outputMessage = messages[std::rand() % messages.size()];
	size_t tagPos = outputMessage.find("{}");

	if(tagPos != std::string::npos)
		outputMessage.replace(tagPos, 2, nameOfItem);
	std::cout << outputMessage << std::endl;
}

void Event::fightEncouter(Player &p) const {
	Enemy enemy = generateRandomEnemy(p);
	bool isPlayerTurn = getRandomNumberInRange(0,1) == 0;

	if(!handlePlayerFirstMoveDecision(isPlayerTurn, enemy))
		return;

	bool isEscaping = false;
	while(p.isAlive() && enemy.isAlive() && !isEscaping) {
		if(isPlayerTurn && p.isAlive()) {
			if(handlePlayerTurn(p, enemy, isEscaping))
				isPlayerTurn = false;
		}
		else if(enemy.isAlive()) {
			handleEnemyTurn(p, enemy);
			isPlayerTurn = true;
		}

		if(!enemy.isAlive()) {
			CLEAR_SCREEN;
			handleCombatReward(p, enemy);
			break;
		}
		if(!p.isAlive()) {
			CLEAR_SCREEN;
			break;
		}
	}
}

Enemy Event::generateRandomEnemy(Player &p) const {
	Enemy enemy = enemies[getRandomNumberInRange(0, enemies.size() - 1)];
	enemy.updateCharacteristics(p.getLevel());
	return enemy;
}

bool Event::handlePlayerFirstMoveDecision(bool isPlayerTurn, Enemy &enemy) const {
	if(isPlayerTurn) {
		int choice = getValidatedAnswer("\nI see an enemy, should I fight with him?\n(1) - Yes\n(2) - No\nYour choice: ", "Invalid choice", 1, 2);
		if(choice == 1) {
			std::cout << "\nThen I attack" << std::endl;
			return true;
		}
		else {
			std::cout << "\nI chose to avoid fight" << std::endl;
			return false;
		}
	}
	else {
		std::cout << "I was attacked by " << enemy.getName() << std::endl;
		return true;
	}
}

bool Event::handlePlayerTurn(Player &p, Enemy &enemy, bool &isEscaping) const {
	printCombatStatus(p, enemy);
	printFightOptions();
	FightOption choice = static_cast<FightOption>(getValidatedAnswer("Your choice: ", "Invalid choice", 0, 3));
	CLEAR_SCREEN;
	if(choice == FightOption::ESCAPE) {
		isEscaping = handleEscape(p);
		return isEscaping;
	}
	else if(choice == FightOption::ATTACK) {
		handleAttack(p, enemy);
	}
	else if(choice == FightOption::USE_ITEM) {
		bool isItemUsed = handleUsingItem(p);
		CLEAR_SCREEN;
		return isItemUsed;
	}
	else if(choice == FightOption::RESTORE_ENERGY) {
		p.restoreStaminaInCombat();
	}

	handleLowVitalParameters(p);
	consumePlayerParameters(p);

	return true;
}

void Event::printCombatStatus(Player &p, Enemy &enemy) const {
	std::cout << std::endl;
	std::cout << std::right << std::setw(37) << std::setfill('=') << "   |   " << std::setw(30) << std::right << std::setfill('=') << " " << std::endl;
	std::cout << std::left << std::setw(30) << "== " + p.getName() + " " << std::setw(36)
		<< std::left << "   |   == " + enemy.getName() + " " << std::endl;

	std::cout << std::left << std::setw(14) << "== Health  == " << std::setw(16) << std::setfill('=')
		<< std::to_string(p.getHealth()) + " / " + std::to_string(p.getMaxHealth()) + " "
		<< std::setw(36) << std::left << "   |   == " + std::to_string(enemy.getHealth()) + " / " + std::to_string(enemy.getMaxHealth()) + " " << std::endl;

	std::cout << std::left << std::setw(14) << "== Damage  == " << std::setw(16) << std::setfill('=')
		<< std::to_string(p.getMinDamage()) + " / " + std::to_string(p.getMaxDamage()) + " "
		<< std::setw(36) << std::left << "   |   == " + std::to_string(enemy.getMinDamage()) + " / " + std::to_string(enemy.getMaxDamage()) + " " << std::endl;

	std::cout << std::left << std::setw(14) << "== Stamina == " << std::setw(16) << std::setfill('=')
		<< std::to_string(p.getStamina()) + " / " + std::to_string(p.getStaminaMax()) + " " << std::setw(36)
		<< std::left << "   |   " << std::endl;

	std::cout << std::left << std::setw(14) << "== Hunger  == " << std::setw(16) << std::setfill('=')
		<< std::to_string(p.getHunger()) + " / " + std::to_string(p.getHungerMax()) + " " << std::setw(7) << std::left << "   |   " << std::endl;

	std::cout << std::left << std::setw(14) << "== Thirst  == " << std::setw(16) << std::setfill('=')
		<< std::to_string(p.getThirst()) + " / " + std::to_string(p.getThirstMax()) + " " << std::setw(7) << std::left << "   |   " << std::endl;

	std::cout << std::setw(37) << std::right << std::setfill('=') << "   |   " << std::endl;
	std::cout << std::right << std::setfill(' ');
}

void Event::printFightOptions() const {
	std::cout << "\n(0) - Escape" << std::endl
		<< "(1) - Attack" << std::endl
		<< "(2) - Use Item" << std::endl
		<< "(3) - Restore Energy" << std::endl;
}

bool Event::handleEscape(Player &p) const {
	if(isPlayerCanEscape(p)) {
		std::cout << "I was able to escape" << std::endl;

		p.setStamina(std::max(p.getStamina() - STAMINA_TO_ESCAPE_FROM_FIGHT, 0));
		p.setHunger(std::max(p.getHunger() - HUNGER_TO_ESCAPE_FROM_FIGHT, 0));
		p.setThirst(std::max(p.getThirst() - THIRST_TO_ESCAPE_FROM_FIGHT, 0));
		return true;
	}
	else {
		std::cout << "I need to raise my stamina to 60, hunger and thirst to 30 or I won't be able to escape" << std::endl;
		return false;
	}
}

bool Event::isPlayerCanEscape(Player &p) const {
	return p.getStamina() > STAMINA_TO_ESCAPE_FROM_FIGHT && p.getHunger() > HUNGER_TO_ESCAPE_FROM_FIGHT && p.getThirst() > THIRST_TO_ESCAPE_FROM_FIGHT;
}

void Event::handleAttack(Player &p, Enemy &enemy) const {
	int givenDamage = p.inflictDamage();
	enemy.takeDamage(givenDamage);
	std::cout << "I attacked " << enemy.getName() << " and gave him " << givenDamage << " damage" << std::endl;
}

bool Event::handleUsingItem(Player &p) const {
	return p.useItemInCombat();
}

void Event::handleLowVitalParameters(Player &p) const {
	if(p.getStamina() == 0 || p.getHunger() == 0 || p.getThirst() == 0) {
		std::cout << "I feel weak and lose some health due to one of my vital parameters being critically low." << std::endl;
		p.setHealth(std::max(p.getHealth() - getRandomNumberInRange(1, 10), 0));
	}
}

void Event::consumePlayerParameters(Player &p) const {
	p.setStamina(std::max(0, p.getStamina() - getRandomNumberInRange(3, 8)));
	p.setHunger(std::max(0, p.getHunger() - getRandomNumberInRange(2, 5)));
	p.setThirst(std::max(0, p.getThirst() - getRandomNumberInRange(2, 5)));
}

void Event::handleEnemyTurn(Player &p, Enemy &enemy) const {
	int givenDamage = enemy.inflictDamage();
	p.takeDamage(givenDamage);
	std::cout << "The " << enemy.getName() << " attacked and gave me " << givenDamage << " damage" << std::endl;
}

void Event::handleCombatReward(Player &player, Enemy &enemy) const {
	int moneyReward = getRandomNumberInRange(10 * enemy.getLevel(), 50 * enemy.getLevel());
	int expReward = getRandomNumberInRange(10 * enemy.getLevel(), 30 * enemy.getLevel());
	player.setMoney(player.getMoney() + moneyReward);
	player.setExp(player.getExp() + expReward);
	std::cout << "\nI defeated " << enemy.getName() << " and won the battle!\n";
	std::cout << "I gained " << expReward << " experience points and " << moneyReward << " G.\n";

	if(getRandomNumberInRange(1, 100) <= enemy.getDropChance()) {
		std::shared_ptr<Item> givenItem = enemy.getDroppedItem();
		std::cout << "I received " << givenItem->getName() << " from the enemy corpse" << std::endl;
		player.getInventory().addItem(givenItem);
	}
}

void Event::shop(Player &p) const {
	CLEAR_SCREEN;
	std::cout << "\nWelcome to the Golden street " << p.getName() << "!" << std::endl
		<< "In this street you can buy (almost) everything you want" << std::endl
		<< "What type of items you want to view?" << std::endl;
	ShopOption choice{};
	int moneyBefore{ p.getMoney() };
	do {
		std::cout << "My G: " << p.getMoney() << std::endl;
		choice = static_cast<ShopOption>(getValidatedAnswer("\n(0) - Leave the shop\n(1) - Weapons\n(2) - Armor\n(3) - Products\n(4) - Increase backpack\n(5) - Sell items\nYour choice: ", "Invalid choice", 0, 5));
		if(choice == ShopOption::WEAPON_SHOP) 
			weaponShop(p);
		else if(choice == ShopOption::ARMOR_SHOP) 
			armorShop(p);
		else if(choice == ShopOption::PRODUCTS_SHOP) 
			productsShop(p);
		else if(choice == ShopOption::INCREASE_BACKPACK) 
			increaseBackpack(p);
		else if(choice == ShopOption::SELL_ITEMS) 
			sellItems(p);
		else {
			if(moneyBefore == p.getMoney())
				std::cout << "Though you didn't make a purchase, I'm always happy to see you. Stay safe on your travels!" << std::endl;
			break;
		}
	} while(choice != ShopOption::LEAVE_SHOP);
	CLEAR_SCREEN;
}

void Event::weaponShop(Player &p) const {
	shopInteraction(p, "Weapon shop", { itemsToSell[3], itemsToSell[4], itemsToSell[5] });
}

void Event::armorShop(Player &p) const {
	shopInteraction(p, "Armor shop", { itemsToSell[6], itemsToSell[7], itemsToSell[8] });
}

void Event::productsShop(Player &p) const {
	shopInteraction(p, "Products shop", { itemsToSell[0], itemsToSell[1], itemsToSell[2] });
}

void Event::shopInteraction(Player &p, const std::string &shopName, const std::vector<std::shared_ptr<Item>> &itemsToSell) const {
	int choice{};
	CLEAR_SCREEN;
	do {
		std::cout << "My G: " << p.getMoney() << std::endl;
		printShopAssortment(shopName, itemsToSell);

		choice = getValidatedAnswer("\nYour choice: ", "Invalid choice", 0, itemsToSell.size());
		if(choice != 0) {
			std::shared_ptr<Item> itemToSell = getItemToSell(shopName, choice);
			if(p.buyItem(itemToSell))
				std::cout << "Thank you for your purchase! Feel free to come back anytime, I always have something interesting!" << std::endl;
			else 
				std::cout << "If you don't have enough money, I'm afraid I can't offer my wares at a discount. Perhaps another time when your purse is heavier." << std::endl;
		}

	} while(choice != 0);
	CLEAR_SCREEN;
}

std::shared_ptr<Item> Event::getItemToSell(const std::string &shopName, size_t index) const {
	if(shopName == "Weapon shop")
		return std::make_shared<Weapon>(*dynamic_cast<Weapon *>(itemsToSell[index+2].get()));
	else if(shopName == "Armor shop")
		return std::make_shared<Armor>(*dynamic_cast<Armor *>(itemsToSell[index+5].get()));
	else if(shopName == "Products shop")
		return std::make_shared<Product>(*dynamic_cast<Product *>(itemsToSell[index-1].get()));
	else
		return nullptr;
}

void Event::printShopAssortment(const std::string &shopName, const std::vector<std::shared_ptr<Item>> &itemsToSell) const {
	std::cout << "\n" << shopName << std::endl;
	for(size_t i = 0; i < itemsToSell.size(); i++)
		printItemDetails(i, itemsToSell[i]);
}

void Event::printItemDetails(size_t index, const std::shared_ptr<Item> &itemToSell) const {
	auto weapon = std::dynamic_pointer_cast<Weapon>(itemToSell);
	auto armor = std::dynamic_pointer_cast<Armor>(itemToSell);
	auto product = std::dynamic_pointer_cast<Product>(itemToSell);

	if(weapon)
		std::cout << "(" << index + 1 << ") - " << weapon->getName() << " (+" << weapon->getMinDamage() << "-" << weapon->getMaxDamage() << " damage) : cost " << weapon->getPurchasePrice() << "G" << std::endl;
	else if(armor)
		std::cout << "(" << index + 1 << ") - " << armor->getName() << " (+" << armor->getDefence() << " defence) : cost " << armor->getPurchasePrice() << "G" << std::endl;
	else if(product)
		std::cout << "(" << index + 1 << ") - " << product->getName() << " (+" << product->getEnergyRestored() << ") : cost " << product->getPurchasePrice() << "G" << std::endl;
}

void Event::increaseBackpack(Player &p) const {
	CLEAR_SCREEN;
	std::cout << "Welcome to the Backpack shop. Hope something suits you!" << std::endl;

	static const std::map<std::string, std::pair<int, size_t>> backpacks{
		{"School backpack", {1000, 9}},
		{"Pioneer backpack", {3200, 13}},
		{"Duffel bag", {8000, 19}},
		{"Tourist backpack", {14000, 23}},
		{"Army backpack", {20000, 25}}
	};

	int choice{};
	do {
		std::cout << "My G: " << p.getMoney() << std::endl;
		choice = getValidatedAnswer("\n(0) - Go back\n(1) - School backpack (+4 slots) Cost: 1000G\n(2) - Pioneer backpack (+8 slots) Cost: 3200G\n(3) - Duffel bag (+14 slots) Cost: 8000G\n(4) - Tourist backpack (+18 slots) Cost: 14000G\n(5) - Army backpack (+20 slots) Cost: 20000G\nYour choice: ", "Invalid choice", 0, 5);
		CLEAR_SCREEN;
		if(choice == 0)
			return;

		auto it = backpacks.find(getBackpackName(choice));
		if(it != backpacks.end())
			if(setNewBackpack(p, it->second))
				std::cout << "\nYou bought a " << it->first << std::endl;
	} while(choice != 0);
}

std::string Event::getBackpackName(size_t choice) const {
	const std::vector<std::string> backpackNames{
		"School backpack",
		"Pioneer backpack",
		"Duffel bag",
		"Tourist backpack",
		"Army backpack"
	};
	return backpackNames[choice - 1];
}

bool Event::setNewBackpack(Player &p, const std::pair<int, size_t> &backpack) const {
	if(p.getInventory().getMaxNumberOfItems() >= backpack.second) {
		std::cout << "I guess you already have a bigger backpack than that" << std::endl;
		return false;
	}

	if(p.getMoney() < backpack.first) {
		std::cout << "You don't have enough G" << std::endl;
		return false;
	}

	p.getInventory().setMaxNumberOfItems(backpack.second);
	p.setMoney(p.getMoney() - backpack.first);
	return true;
}

void Event::sellItems(Player &p) const {
	CLEAR_SCREEN;
	Inventory &inventory = p.getInventory();
	if(inventory.getItems().size() <= 0) {
		std::cout << "\My inventory is empty" << std::endl;
		return;
	}

	std::cout << "Welcome to the flea market. Here you can sell all your junk." << std::endl;
	size_t choice{};
	do {
		if(inventory.getItems().size() <= 0) {
			std::cout << "\My inventory is empty" << std::endl;
			return;
		}
		inventory.printInventory();
		choice = getValidatedAnswer("Choose item that you want to sell: ", "Invalid choice", 0, inventory.getItems().size());

		if(choice == 0)
			return;

		std::string nameOfSoldItem = inventory.getItems()[choice - 1]->getName();
		p.sellItem(choice - 1);
		std::cout << nameOfSoldItem << " sold" << std::endl;
	} while(choice != 0);

	CLEAR_SCREEN;
}

void Event::updateShop() {
	itemsToSell.clear();
	Event::generateItemsToSell();
}