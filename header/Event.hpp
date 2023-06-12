#pragma once

#include <stdlib.h>

#include "Puzzle.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

class Event {
private:
protected:
	int numberOfEvents;
	int numberOfPuzzles;

	void puzzleEncouter(Player &p);
	bool isPlayerAnswerValidate(const int &playerAnswer, const int &numberOfAnswers) const;
	void printPuzzleChances(const int &remainingChances) const;
	void fightEncouter(Player &p);
	void foundItemEncouter(Player &p);
	void foundArmor(Player &p, const std::string &name);
	void foundPotion(Player &p, const std::string &name);
	void foundWeapon(Player &p, const std::string &name);
	int calculateRarity() const;
	int calculateType(const std::string &name) const;
	std::string getRandomCategory() const;
	void displayMessageAboutFoundItem(const std::string &nameOfItem) const;
public:
	Event();
	~Event() = default;
	void generateEvent(Player &p);
};

