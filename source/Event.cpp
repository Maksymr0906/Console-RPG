#include "Event.hpp"

std::vector<std::string> Event::nthHappened;
std::vector<Puzzle> Event::puzzles;

Event::Event() {
	this->numberOfEvents = 5;
}

//Refactor
void Event::initialize() {
	getNthHappenedFromFile();
	getPuzzlesFromFile();
}

//Refactor
void Event::getNthHappenedFromFile() {
	std::ifstream file("NothingHappened/Messages.txt");

	if(!file.is_open()) {
		std::cerr << "Error opening file" << std::endl;
		return;
	}

	std::string message{};
	while(std::getline(file, message)) {
		nthHappened.push_back(message);
	}

	file.close();
}

//Refactor
void Event::getPuzzlesFromFile() {
	std::ifstream file("Puzzles/Puzzle.txt");

	if(!file.is_open()) {
		std::cerr << "Error opening file" << std::endl;
		return;
	}
	while(!file.eof()) {
		
		std::string answer{};
		int numOfAnswers{}, indexOfCorrectAnswer{};
		std::string question;

		std::getline(file, question);
		file >> numOfAnswers;
		file.ignore();

		std::vector<std::string> answers;
		for(size_t i = 0; i < numOfAnswers; i++) {
			std::getline(file, answer);
			answers.push_back(answer);
		}

		file >> indexOfCorrectAnswer;
		file.ignore();

		Puzzle puzzle{ question, indexOfCorrectAnswer, answers };
		puzzles.push_back(puzzle);
	}

	file.close();
}

int Event::calculateRandomEvent() const {
	int event = rand() % 72 + 1;
	if(event <= 40) {
		return 1; //Nothing - 40%
	}
	else if(event <= 55) {
		return 2; //Puzzle - 15%
	}
	else if(event <= 65) {
		return 3; //Found Item - 10%
	}
	else if(event <= 72) {
		return 4; //Fight - 7%
	}
}

void Event::generateEvent(Player &p) {
	int indexOfRandomEvent = calculateRandomEvent();

	switch(indexOfRandomEvent) {
		case 1:
			nothingHappened();
			//Fight
			break;
		case 2:
			puzzleEncouter(p);
			//Puzzle
			break;
		case 3:
			foundItemEncouter(p);
			//Found item
			break;
		case 4:
			foundItemEncouter(p);
			break;
		case 5:
			puzzleEncouter(p);
			break;
		default:
			break;
	}
}

void Event::nothingHappened() const {
	std::cout << nthHappened[std::rand() % nthHappened.size()] << std::endl;
}

void Event::puzzleEncouter(Player &p) {
Puzzle puzzle = puzzles[std::rand() % puzzles.size()];
	int playerAnswer{};
	int remainingChances{puzzle.getNumberOfAnswers() - 1};

	bool completed = false;

	while(!completed && remainingChances > 0) {
		printPuzzleChances(remainingChances);
		remainingChances--;

		std::cout << puzzle.getAsString() << std::endl;

		do {
			playerAnswer = getNumber("Your answer: ") - 1;
			if(isPlayerAnswerValidate(playerAnswer, puzzle.getNumberOfAnswers() - 1)) {
				std::cout << "\nChoose one from the given variants\n" << std::endl;
			}
		} while(isPlayerAnswerValidate(playerAnswer, puzzle.getNumberOfAnswers() - 1));


		if(playerAnswer == puzzle.getIndexOfCorrectAnswer()) {
			completed = true;
			std::cout << "\nYou won" << std::endl;
			int expGained = p.getLevel() * rand() % 15 + 5;
			p.setExp(p.getExp() + expGained);
			std::cout << "\nYou received " << expGained << " exp" << std::endl;
		}
		else {
			std::cout << "You lose" << std::endl;
		}
	}
}

void Event::printPuzzleChances(const int &remainingChances) const {
	std::cout << std::endl << remainingChances;
	if(remainingChances > 1) {
		std::cout << " chances left" << std::endl;
	}
	else {
		std::cout << " chance left" << std::endl;
	}
}

bool Event::isPlayerAnswerValidate(const int &playerAnswer, const int &numberOfAnswers) const {
	return playerAnswer > numberOfAnswers || playerAnswer < 0;
}

void Event::fightEncouter(Player &p) {
	std::cout << "Fight" << std::endl;
	
}

void Event::foundItemEncouter(Player &p) {
	std::string category = getRandomCategory();

	const std::string filePath = "Items/" + category + ".txt";
	std::ifstream file(filePath);

	if(!file.is_open()) {
		std::cout << "Failed to open the file." << std::endl;
		return;
	}

	std::vector<std::string> namesOfItems;
	std::string itemName;
	while(std::getline(file, itemName)) {
		namesOfItems.push_back(itemName);
	}
	file.close();

	std::string randomItemName = namesOfItems[std::rand() % namesOfItems.size()];

	if(category == "Weapons") {
		foundWeapon(p, randomItemName);
	}
	else if(category == "Armor") {
		foundArmor(p, randomItemName);
	}
	else if(category == "Potions") {
		foundWeapon(p, randomItemName);
	}

	displayMessageAboutFoundItem(randomItemName);
}

void Event::displayMessageAboutFoundItem(const std::string &nameOfItem) const {
	const std::string filePath = "Items/Messages.txt";
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
//rewrite all this formulas
void Event::foundWeapon(Player &p, const std::string &name) {
	int playerLevel = p.getLevel();
	int rarity = calculateRarity();
	
	int minDamage = (rand() % 5 + 1) * (rand() % rarity + 1) * playerLevel;
	int maxDamage = ((rand() % 5 + 1) * (rand() % rarity + 1) * playerLevel) + minDamage;
	
	int purchasePrice = (rand() % 100 + 1) + rarity * 5 * playerLevel;
	int salePrice = purchasePrice - (rand() % purchasePrice + 1);

	std::shared_ptr<Item> weapon = std::make_shared<Weapon>(Weapon(name.c_str(), "Weapon", "Unequipped", purchasePrice, salePrice, minDamage, maxDamage, 1, rarity));
	p.getInventory().addItem(weapon);
}

void Event::foundArmor(Player &p, const std::string &name) {
	int playerLevel = p.getLevel();
	int rarity = calculateRarity();
		
	int defence = (rand() % 5 + 1) * (rand() % rarity + 1) * playerLevel;
	int type = calculateType(name);

	int purchasePrice = (rand() % 100 + 1) + rarity * 5 * playerLevel;
	int salePrice = purchasePrice - (rand() % purchasePrice + 1);
	
	std::shared_ptr<Item> armor = std::make_shared<Armor>(Armor(name.c_str(), "Armor", "Unequipped", purchasePrice, salePrice, 1, rarity, defence, type));
	p.getInventory().addItem(armor);
}

void Event::foundPotion(Player &p, const std::string &name) {
	//will be implemented soon
}

int Event::calculateRarity() const {
	int rarity = rand() % 100 + 1;
	if(rarity <= 1) {
		rarity = 5; // 1%
	}
	else if(rarity <= 6) {
		rarity = 4; // 5%
	}
	else if(rarity <= 16) {
		rarity = 3; // 10%
	}
	else if(rarity <= 41) {
		rarity = 2; // 25%
	}
	else {
		rarity = 1; //59%
	}

	return rarity;
}

int Event::calculateType(const std::string &name) const {
	if(name.find("Helmet") != std::string::npos) {
		return 1;
	}
	else if(name.find("Chestplate") != std::string::npos) {
		return 2;
	}
	else if(name.find("Leggings") != std::string::npos) {
		return 3;
	}
	else if(name.find("Boots") != std::string::npos) {
		return 4;
	}

	return 0;
}

std::string Event::getRandomCategory() const {
	int x = rand() % 3;
	if(x == 0) {
		return "Armor";
	}
	else if(x == 1) {
		return "Weapons";
	}
	else {
		return "Potions";
	}
}
