#pragma once

#include <stdlib.h>
#include <limits>

#include "Puzzle.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

class Event {
private:
	void foundArmor(Player &p, const std::string &name);
	void foundWeapon(Player &p, const std::string &name);
	int calculateRarity() const;
	int calculateType(const std::string &name) const;
	std::string getRandomCategory() const;
	bool isPlayerAnswerValidate(const int &playerAnswer, const int &numberOfAnswers) const;
	void printPuzzleChances(const int &remainingChances) const;
	void displayMessageAboutFoundItem(const std::string &nameOfItem) const;
	int calculateRandomEvent() const;

	static void getNthHappenedFromFile(); //Rename
	static void getPuzzlesFromFile();
	static void getProductsFromFile();
protected:
	static std::vector<std::string> nthHappened; //Rename
	static std::vector<Puzzle> puzzles;
	static std::vector<std::shared_ptr<Item>> products;

	int numberOfEvents;

	void puzzleEncouter(Player &p);
	void fightEncouter(Player &p);
	void foundItemEncouter(Player &p);

	void nothingHappened() const; //Rename

public:
	Event();
	void foundProductEncouter(Player &p);
	~Event() = default;
	void generateEvent(Player &p);
	static void initialize();
};

