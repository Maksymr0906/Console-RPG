#pragma once

#include <stdlib.h>

#include "Puzzle.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

class Event {
private:
	void foundArmor(Player &p);
	void foundWeapon(Player &p);
	void foundProduct(Player &p);
	std::string getRandomCategory() const;
	bool isPlayerAnswerValidate(const int &playerAnswer, const int &numberOfAnswers) const;
	void printPuzzleChances(const int &remainingChances) const;
	void displayMessageAboutFoundItem(const std::string &nameOfItem) const;
	int calculateRandomEvent() const;
	void increaseBackpack(Player &p);
	bool setNewBackpack(Player &p, const std::pair<int, size_t> &backpack);
	void weaponShop(Player &p);
	void armorShop(Player &p);
	void productsShop(Player &p);
	void sellItems(Player &p);

	static void readEnemiesFromFile();
	static void readEmptyEventMessagesFromFile();
	static void readPuzzlesFromFile();
	static void readProductsFromFile();
	static void generateItemsToSell();
	static void readWeaponsFromFile();
	static void readArmorFromFile();
	static void readItemsFromFile(const std::string fileName, std::vector<std::shared_ptr<Item>> &items);

protected:
	static std::vector<Enemy> enemies;
	static std::vector<std::shared_ptr<Item>> itemsToSell;
	static std::vector<std::string> emptyEventMessages;
	static std::vector<Puzzle> puzzles;
	static std::vector<std::shared_ptr<Item>> products;
	static std::vector<std::shared_ptr<Item>> weapons;
	static std::vector<std::shared_ptr<Item>> armor;

	int numberOfEvents;

	void puzzleEncouter(Player &p);
	void fightEncouter(Player &p);
	void foundItemEncouter(Player &p);
	void emptyEventEncouter() const;

public:
	Event();
	~Event() = default;
	void generateEvent(Player &p);
	static void initialize();
	void shop(Player &p);
	static void updateShop();
};

