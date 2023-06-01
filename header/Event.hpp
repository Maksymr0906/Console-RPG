#pragma once

#include <stdlib.h>

#include "Puzzle.hpp"
#include "Player.hpp"

class Event {
private:
protected:
	int numberOfEvents;
	int numberOfPuzzles;
public:
	Event();
	~Event() = default;
	void generateEvent(Player &p);
	void puzzleEncouter(Player &p);
	bool isPlayerAnswerValidate(const int &playerAnswer, const int &numberOfAnswers) const;
	void printPuzzleChances(const int &remainingChances) const;
	void fightEncouter(Player &p);
	void foundItemEncouter(Player &p);
};

