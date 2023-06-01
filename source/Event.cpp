#include "Event.hpp"

Event::Event() {
	this->numberOfEvents = 5;
	this->numberOfPuzzles = 5;
}

void Event::generateEvent(Player &p) {
	int event = rand() % numberOfPuzzles + 1;
	
	switch(event) {
		case 1:
			fightEncouter(p);
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
			puzzleEncouter(p);
			break;
		case 5:
			puzzleEncouter(p);
			break;
		default:
			break;
	}
}

void Event::puzzleEncouter(Player &p) {
	int indexForPuzzle = rand() % numberOfPuzzles + 1;
	std::string nameOfFile = "Puzzles/Puzzle" + std::to_string(indexForPuzzle) + ".txt";
	Puzzle puzzle(nameOfFile);
	
	int playerAnswer{};
	int remainingChances{puzzle.getNumberOfAnswers() - 1};

	bool completed = false;

	while(!completed && remainingChances > 0) {
		printPuzzleChances(remainingChances);
		remainingChances--;

		std::cout << puzzle.getAsString() << std::endl;

		do {
			playerAnswer = getNumber("Your answer: ");
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
	std::cout << "Found item" << std::endl;
}