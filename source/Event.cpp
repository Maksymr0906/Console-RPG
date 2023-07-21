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

//Refactor
void Event::initialize() {
	readEnemiesFromFile();
	readEmptyEventMessagesFromFile();
	readPuzzlesFromFile();
	readProductsFromFile();
	readArmorFromFile();
	readWeaponsFromFile();
	generateItemsToSell();
}

void Event::readEnemiesFromFile() {
	std::ifstream infile("Enemies.txt");

	if(!infile.is_open()) {
		std::cerr << "Error opening file" << std::endl;
		return;
	}

	Enemy enemy;
	while(!infile.eof()) {
		enemy.readFromTxtFile(infile);
		enemies.push_back(enemy);
		infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	infile.close();
}

void Event::readWeaponsFromFile() {
	readItemsFromFile("Weapons.txt", weapons);
}

void Event::readArmorFromFile() {
	readItemsFromFile("Armor.txt", armor);
}

void Event::readProductsFromFile() {
	readItemsFromFile("Products.txt", products);
}

void Event::readItemsFromFile(const std::string fileName, std::vector<std::shared_ptr<Item>> &items) {
	std::ifstream infile(fileName);

	if(!infile.is_open()) {
		std::cerr << "Error opening file: " << fileName << std::endl;
		return;
	}

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

//Refactor this
void Event::generateItemsToSell() {
	bool isProductExist = false;
	for(size_t i = 0; i < 3; i++) {
		int randomProductIndex = rand() % products.size();
		std::shared_ptr<Item> product = std::make_shared<Product>(*dynamic_cast<Product *>(products[randomProductIndex].get()));
		for(const auto &p : itemsToSell) {
			if(*p == *product) {
				i--;
				isProductExist = true;
			}
		}

		if(!isProductExist)
			itemsToSell.push_back(product);
		isProductExist = false;

	}

	bool isWeaponExist = false;
	for(size_t i = 0; i < 3; i++) {
		int randomProductIndex = rand() % weapons.size();
		std::shared_ptr<Item> weapon = std::make_shared<Weapon>(*dynamic_cast<Weapon *>(weapons[randomProductIndex].get()));
		for(const auto &p : itemsToSell) {
			if(*p == *weapon) {
				i--;
				isWeaponExist = true;
			}
		}

		if(!isWeaponExist)
			itemsToSell.push_back(weapon);
		isWeaponExist = false;
	}

	bool isArmorExist = false;
	for(size_t i = 0; i < 3; i++) {
		int randomProductIndex = rand() % armor.size();
		std::shared_ptr<Item> armorItem = std::make_shared<Armor>(*dynamic_cast<Armor *>(armor[randomProductIndex].get()));
		for(const auto &p : itemsToSell) {
			if(*p == *armorItem) {
				i--;
				isArmorExist = true;
			}
		}

		if(!isArmorExist)
			itemsToSell.push_back(armorItem);
		isArmorExist = false;
	}
}

//Refactor
void Event::readEmptyEventMessagesFromFile() {
	std::ifstream file("EmptyEventMessages.txt");

	if(!file.is_open()) {
		std::cerr << "Error opening file" << std::endl;
		return;
	}

	std::string message{};
	while(std::getline(file, message)) {
		emptyEventMessages.push_back(message);
	}

	file.close();
}

void Event::readPuzzlesFromFile() {
	std::ifstream infile("Puzzle.txt");

	if(!infile.is_open()) {
		std::cerr << "Error opening file" << std::endl;
		return;
	}
	while(!infile.eof()) {

		std::string answer{};
		int indexOfCorrectAnswer{};
		size_t numOfAnswers{};
		std::string question;
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

int Event::calculateRandomEvent() const {
	int event = rand() % 100 + 1;
	if(event <= 50) {
		return 1; //Nothing - 50%
	}
	else if(event <= 65) {
		return 2; //Puzzle - 15%
	}
	else if(event <= 90) {
		return 3; //Found Item - 25%
	}
	else {
		return 4; //Fight - 10%
	}
}

void Event::generateEvent(Player &p) {
	int indexOfRandomEvent = calculateRandomEvent();

	switch(indexOfRandomEvent) {
		case 1:
			emptyEventEncouter();
			break;
		case 2:
			puzzleEncouter(p);
			//Puzzle
			break;
		case 3:
			foundItemEncouter(p);
			//Found Item
			break;
		case 4:
			//Fight
			fightEncouter(p);
			break;
		default:
			break;
	}
}

void Event::emptyEventEncouter() const {
	std::cout << emptyEventMessages[std::rand() % emptyEventMessages.size()] << std::endl;
}

void Event::puzzleEncouter(Player &p) {
	Puzzle puzzle = puzzles[std::rand() % puzzles.size()];
	int playerAnswer{};
	size_t remainingChances{ puzzle.getNumberOfAnswers() - 1 };

	bool completed = false;

	while(!completed && remainingChances > 0) {

		std::cout << puzzle.getAsString() << std::endl;
		printPuzzleChances(remainingChances);
		remainingChances--;
		do {
			playerAnswer = getNumber("Your answer: ") - 1;
			if(isPlayerAnswerValidate(playerAnswer, puzzle.getNumberOfAnswers() - 1)) {
				std::cout << "\nChoose one from the given variants\n" << std::endl;
			}
		} while(isPlayerAnswerValidate(playerAnswer, puzzle.getNumberOfAnswers() - 1));

		if(playerAnswer == puzzle.getIndexOfCorrectAnswer()) {
			completed = true;
			int expGained = calculateRandomCharacteristic(10 * (p.getLevel() + (p.getLuck() / 2)), 15 * (p.getLevel() + (p.getLuck() / 2)));
			int moneyGained = calculateRandomCharacteristic(10 * (p.getLevel() + (p.getLuck() / 2)), 15 * (p.getLevel() + (p.getLuck() / 2)));
			p.setExp(p.getExp() + expGained);
			p.setMoney(p.getMoney() + moneyGained);
			std::cout << "\nI chose the right answer, the safe opened and I received " << expGained << " exp and " << moneyGained << " money" << std::endl;
			return;

		}
	}

	std::cout << "Unfortunately, my attempt to open the safe was unsuccessful." << std::endl;
}

void Event::printPuzzleChances(const int &remainingChances) const {
	if(remainingChances > 1)
		std::cout << "I have " << remainingChances << " attempts left to crack the safe.I have to choose my next answer wisely!" << std::endl << std::endl;
	else
		std::cout << "I only have 1 try remaining before the safe locks permanently." << std::endl << std::endl;
}

bool Event::isPlayerAnswerValidate(const int &playerAnswer, const int &numberOfAnswers) const {
	return playerAnswer > numberOfAnswers || playerAnswer < 0;
}

void Event::fightEncouter(Player &p) {
	Enemy enemy = enemies[rand() % enemies.size()];
	enemy.updateCharacteristics(p.getLevel());

	bool isPlayerTurn = false, isEnemyTurn = false;
	rand() % 2 == 0 ? isPlayerTurn = true : isEnemyTurn = true;
	if(isPlayerTurn) {
		int choice = getValidateAnswer("\nI see an enemy, should I fight with him?\n(1) - Yes\n(2) - No\nYour choice: ", "Invalid choice", 1, 2);
		if(choice == 1) {
			std::cout << "\nThen I attack" << std::endl;
		}
		else {
			std::cout << "\nI chose to avoid fight" << std::endl;
			return;
		}
	}

	if(isEnemyTurn) {
		std::cout << "\nI was attacked by " << enemy.getName() << std::endl;
	}

	bool escape = false;

	while(p.isAlive() && enemy.isAlive() && !escape) {
		if(isPlayerTurn && p.isAlive()) {
			std::cout << std::endl;
			std::cout << std::setw(37) << std::setfill('=') << "   |   " << std::setw(30) << std::right << std::setfill('=') << " " << std::endl;
			std::cout << std::left << std::setw(30) << "== " + p.getName() + " " << std::setw(36) << std::left << "   |   == " + enemy.getName() + " " << std::endl;
			std::cout << std::left << std::setw(14) << "== Health  == " << std::setw(16) << std::setfill('=') << std::to_string(p.getHealth()) + " / " + std::to_string(p.getMaxHealth()) + " " << std::setw(36) << std::left << "   |   == " + std::to_string(enemy.getHealth()) + " / " + std::to_string(enemy.getMaxHealth()) + " " << std::endl;
			std::cout << std::left << std::setw(14) << "== Damage  == " << std::setw(16) << std::setfill('=') << std::to_string(p.getMinDamage()) + " / " + std::to_string(p.getMaxDamage()) + " " << std::setw(36) << std::left << "   |   == " + std::to_string(enemy.getMinDamage()) + " / " + std::to_string(enemy.getMaxDamage()) + " " << std::endl;
			std::cout << std::left << std::setw(14) << "== Stamina == " << std::setw(16) << std::setfill('=') << std::to_string(p.getStamina()) + " / " + std::to_string(p.getStaminaMax()) + " " << std::setw(36) << std::left << "   |   " << std::endl;
			std::cout << std::left << std::setw(14) << "== Hunger  == " << std::setw(16) << std::setfill('=') << std::to_string(p.getHunger()) + " / " + std::to_string(p.getHungerMax()) + " " << std::setw(7) << std::left << "   |   " << std::endl;
			std::cout << std::left << std::setw(14) << "== Thirst  == " << std::setw(16) << std::setfill('=') << std::to_string(p.getThirst()) + " / " + std::to_string(p.getThirstMax()) + " " << std::setw(7) << std::left << "   |   " << std::endl;
			std::cout << std::setw(37) << std::right << std::setfill('=') << "   |   " << std::endl;
			std::cout << std::right << std::setfill(' ');

			if(p.getStamina() == 0) {
				std::cout << "\nI will lose hp because my stamina is 0. To increase stamina press 3" << std::endl;
			}
			std::cout << "\n(0) - Escape" << std::endl
				<< "(1) - Attack" << std::endl
				<< "(2) - Use Item" << std::endl
				<< "(3) - Restore Energy" << std::endl;
			int choice = getNumber("Your choice: ");
			if(choice == 0) {
				if(p.getStamina() > 60 && p.getHunger() > 30 && p.getThirst() > 30) {
					escape = true;
					std::cout << "Escape successful" << std::endl;
					p.setStamina(std::max(p.getStamina() - 60, 0));
					p.setHunger(std::max(p.getHunger() - 30, 0));
					p.setThirst(std::max(p.getThirst() - 30, 0));
				}
				else {
					std::cout << "I need to raise my stamina to 60, hunger and thirst to 30 or I won't be able to escape" << std::endl;
					continue;
				}

			}
			else if(choice == 1) {
				int givenDamage = p.inflictDamage();
				enemy.takeDamage(givenDamage);
				std::cout << "I attack " << enemy.getName() << " and give him " << givenDamage << " damage" << std::endl;
			}
			else if(choice == 2) {
				if(p.getInventory().is_empty()) {
					std::cout << "\nMy Inventory is empty" << std::endl;
					continue;
				}
				if(!p.useItemInCombat())
					continue;
			}
			else if(choice == 3) {
				p.restoreStaminaInCombat();
			}

			if(p.getStamina() == 0 || p.getHunger() == 0 || p.getThirst() == 0) {
				std::cout << "I lose hp because I am tired" << std::endl;
				p.takeDamage(rand() % 10 + 1);
			}

			p.setStamina(std::max(0, p.getStamina() - calculateRandomCharacteristic(3, 8)));
			p.setHunger(std::max(0, p.getHunger() - calculateRandomCharacteristic(2, 5)));
			p.setThirst(std::max(0, p.getThirst() - calculateRandomCharacteristic(2, 5)));
			isPlayerTurn = false;
			isEnemyTurn = true;
		}
		else if(isEnemyTurn && enemy.isAlive()) {
			int damageGiven = enemy.inflictDamage();
			p.takeDamage(damageGiven);
			std::cout << "The " << enemy.getName() << "attack and gives you " << damageGiven << " damage" << std::endl;
			isPlayerTurn = true;
			isEnemyTurn = false;
		}



		if(!enemy.isAlive()) {
			p.setMoney(p.getMoney() + calculateRandomCharacteristic(10 * enemy.getLevel(), 50 * enemy.getLevel()));
			p.setExp(p.getExp() + calculateRandomCharacteristic(10 * enemy.getLevel(), 30 * enemy.getLevel()));
			int drop = rand() % 100 + 1;
			if(drop <= enemy.getDropChance()) {
				std::shared_ptr<Item> givenItem = enemy.getDroppedItem();
				std::cout << givenItem.use_count() << std::endl;
				std::cout << "You received " << givenItem->getName() << std::endl;
				p.getInventory().addItem(givenItem);
			}
			std::cout << "\nYou won" << std::endl;
			break;
		}
		if(!p.isAlive()) {
			break;
		}
	}
}

void Event::foundItemEncouter(Player &p) {
	std::string category = getRandomCategory();
	if(category == "Weapons")
		foundWeapon(p);
	else if(category == "Armor")
		foundArmor(p);
	else if(category == "Products")
		foundProduct(p);
}

void Event::displayMessageAboutFoundItem(const std::string &nameOfItem) const {
	const std::string filePath = "FoundItemMessages.txt";
	std::ifstream file(filePath);
	if(!file.is_open()) {
		std::cout << "Failed to open the file." << std::endl;
		return;
	}

	std::vector<std::string> messages;
	std::string message;
	while(std::getline(file, message)) {
		messages.push_back(message);
	}

	file.close();

	std::string outputMessage = messages[std::rand() % messages.size()];
	size_t tagPos = outputMessage.find("{}");

	if(tagPos != std::string::npos) {
		outputMessage.replace(tagPos, 2, nameOfItem);
	}

	std::cout << std::endl << outputMessage << std::endl;
}

void Event::foundWeapon(Player &p) {
	int randomIndex = std::rand() % weapons.size();
	std::shared_ptr<Item> weapon = std::make_shared<Weapon>(*dynamic_cast<Weapon *>(weapons[randomIndex].get()));
	displayMessageAboutFoundItem(weapon->getName());
	p.getInventory().addItem(weapon);
}

void Event::foundArmor(Player &p) {
	int randomIndex = std::rand() % armor.size();
	std::shared_ptr<Item> armorItem = std::make_shared<Armor>(*dynamic_cast<Armor *>(armor[randomIndex].get()));
	displayMessageAboutFoundItem(armorItem->getName());
	p.getInventory().addItem(armorItem);
}

std::string Event::getRandomCategory() const {
	int x = rand() % 10;
	if(x < 2) {
		return "Weapons";
	}
	else if(x < 5) {
		return "Products";
	}

	return "Armor";
}

void Event::foundProduct(Player &p) {
	int randomIndex = std::rand() % products.size();
	std::shared_ptr<Item> product = std::make_shared<Product>(*dynamic_cast<Product *>(products[randomIndex].get()));
	displayMessageAboutFoundItem(product->getName());
	p.getInventory().addItem(product);
}

void Event::shop(Player &p) {
	std::cout << "\nWelcome to the Golden street " << p.getName() << "!" << std::endl
		<< "In this street you can buy (almost) everything you want" << std::endl
		<< "What type of items you want to view?" << std::endl;
	int choice{}, moneyBefore{ p.getMoney() };
	do {
		std::cout << "My money: " << p.getMoney() << std::endl;
		choice = getValidateAnswer("\n(0) - Leave the shop\n(1) - Weapons\n(2) - Armor\n(3) - Products\n(4) - Increase backpack\n(5) - Sell items\nYour choice: ", "Incorrect choice", 0, 5);
		if(choice == 1) {
			weaponShop(p);
		}
		else if(choice == 2) {
			armorShop(p);
		}
		else if(choice == 3) {
			productsShop(p);
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

void Event::weaponShop(Player &p) {
	std::cout << "\n/*Weapon shop*/" << std::endl;

	int choice{};
	do {
		std::cout << "\n(0) - Go back" << std::endl;
		for(size_t i = 3, j = 1; i <= 5; i++, j++) {
			std::shared_ptr<Weapon> weapon = std::make_shared<Weapon>(*dynamic_cast<Weapon *>(itemsToSell[i].get()));
			std::cout << "(" << j << ") - " << weapon->getName() << " (+" << weapon->getMinDamage() << "-" << weapon->getMaxDamage() << ") : cost " << weapon->getPurchasePrice() << "G" << std::endl;
		}

		choice = getValidateAnswer("\nYour choice: ", "Incorrect choice", 0, 3);
		if(choice != 0) {
			std::shared_ptr<Item> weapon = std::make_shared<Weapon>(*dynamic_cast<Weapon *>(itemsToSell[choice + 2].get()));
			if(p.buyItem(weapon)) {
				std::cout << "Thank you for your purchase! Feel free to come back anytime, I always have something interesting!" << std::endl;
			}
			else {
				std::cout << "If you don't have enough money, I'm afraid I can't offer my wares at a discount. Perhaps another time when your purse is heavier." << std::endl;
			}
		}
	} while(choice != 0);

}

void Event::armorShop(Player &p) {
	std::cout << "\n/*Armor shop*/" << std::endl;

	int choice{};
	do {
		std::cout << "\n(0) - Go back" << std::endl;
		for(size_t i = 6, j = 1; i <= 8; i++, j++) {
			std::shared_ptr<Armor> armor = std::make_shared<Armor>(*dynamic_cast<Armor *>(itemsToSell[i].get()));
			std::cout << "(" << j << ") - " << armor->getName() << " (+" << armor->getDefence() << ") : cost " << armor->getPurchasePrice() << "G" << std::endl;
		}

		choice = getValidateAnswer("\nYour choice: ", "Incorrect choice", 0, 3);
		if(choice != 0) {
			std::shared_ptr<Item> armor = std::make_shared<Armor>(*dynamic_cast<Armor *>(itemsToSell[choice + 5].get()));
			if(p.buyItem(armor)) {
				std::cout << "Thank you for your purchase! Feel free to come back anytime, I always have something interesting!" << std::endl;
			}
			else {
				std::cout << "If you don't have enough money, I'm afraid I can't offer my wares at a discount. Perhaps another time when your purse is heavier." << std::endl;
			}
		}

	} while(choice != 0);
}

void Event::productsShop(Player &p) {
	std::cout << "\n/*Products shop*/" << std::endl;

	int choice{};
	do {
		std::cout << "\n(0) - Go back" << std::endl;
		for(size_t i = 0, j = 1; i <= 2; i++, j++) {
			std::shared_ptr<Product> product = std::make_shared<Product>(*dynamic_cast<Product *>(itemsToSell[i].get()));
			std::cout << "(" << j << ") - " << product->getName() << " (+" << product->getEnergyRestored() << ") : cost " << product->getPurchasePrice() << "G" << std::endl;
		}

		choice = getValidateAnswer("\nYour choice: ", "Incorrect choice", 0, 3);
		if(choice != 0) {
			std::shared_ptr<Item> product = std::make_shared<Product>(*dynamic_cast<Product *>(itemsToSell[choice - 1].get()));
			if(p.buyItem(product)) {
				std::cout << "Thank you for your purchase! Feel free to come back anytime, I always have something interesting!" << std::endl;
			}
			else {
				std::cout << "If you don't have enough money, I'm afraid I can't offer my wares at a discount. Perhaps another time when your purse is heavier." << std::endl;
			}
		}

	} while(choice != 0);
}

void Event::increaseBackpack(Player &p) {
	std::cout << "\nWelcome to Backpack shop. Hope something suits you!" << std::endl;
	int choice{};
	const std::vector<std::pair<int, size_t>> backpacks{ {1000, 9}, {3200, 13}, {8000, 19}, {14000, 23}, {20000, 25} };
	do {
		choice = getValidateAnswer("\n(0) - Go back\n(1) - School backpack (+4 slots) Cost: 1000G\n(2) - Pioneer backpack (+8 slots) Cost: 3200G\n(3) - Duffel bag (+14 slots) Cost: 8000G\n(4) - Tourist backpack (+18 slots) Cost: 14000G\n(5) - Army backpack (+20 slots) Cost: 20000G\nYour choice: ", "Incorrect choice", 0, 5);
		if(choice == 1) {
			if(setNewBackpack(p, backpacks[choice - 1]))
				std::cout << "\nYou bought a School backpack" << std::endl;
		}
		else if(choice == 2) {
			if(setNewBackpack(p, backpacks[choice - 1]))
				std::cout << "\nYou bought a Pioneer backpack" << std::endl;
		}
		else if(choice == 3) {
			if(setNewBackpack(p, backpacks[choice - 1]))
				std::cout << "\nYou bought a Duffel bag" << std::endl;
		}
		else if(choice == 4) {
			if(setNewBackpack(p, backpacks[choice - 1]))
				std::cout << "\nYou bought a Tourist backpack" << std::endl;
		}
		else if(choice == 5) {
			if(setNewBackpack(p, backpacks[choice - 1]))
				std::cout << "\nYou bought an Army backpack" << std::endl;
		}
	} while(choice != 0);
}

bool Event::setNewBackpack(Player &p, const std::pair<int, size_t> &backpack) {
	if(p.getInventory().getMaxNumberOfItems() >= backpack.second) {
		std::cout << "\nI guess you already have a bigger backpack than that" << std::endl;
		return false;
	}

	if(p.getMoney() < backpack.first) {
		std::cout << "\nYou don't have enough money" << std::endl;
		return false;
	}

	p.getInventory().setMaxNumberOfItems(backpack.second);
	p.setMoney(p.getMoney() - backpack.first);
	return true;
}

void Event::sellItems(Player &p) {
	std::cout << "Welcome to the flea market. Here you can sell all your junk." << std::endl;
	Inventory &inventory = p.getInventory();
	int choice{};

	do {
		if(inventory.getItems().size() > 0) {
			inventory.showInventory();
			choice = getValidateAnswer("Choose item that you want to sell: ", "Incorrect choice", 0, inventory.getItems().size());

			if(choice == 0) {
				return;
			}
			else {
				std::string nameOfSoldItem = inventory.getItems()[choice - 1]->getName();
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

//Refactor
void Event::updateShop() {
	itemsToSell.clear();
	Event::generateItemsToSell();
}