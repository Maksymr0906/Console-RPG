#include "Puzzle.hpp"

Puzzle::Puzzle(std::string fileName) {
	std::ifstream file(fileName);

	std::string answer{};
	int numOfAnswers{};

	if(file.is_open()) {
		std::getline(file, question);
		file >> numOfAnswers;
		file.ignore();

		for(size_t i = 0; i < numOfAnswers; i++) {
			std::getline(file, answer);
			this->answers.push_back(answer);
		}

		file >> indexOfCorrectAnswer;
		file.ignore();
	}
	else {
		std::cout << "Failed to open the file" << std::endl;
	}

	file.close();
}

std::string Puzzle::getAsString() {
	std::string result{};
	result += question + "\n\n";
	
	for(size_t i = 0; i < this->answers.size(); i++) {
		result += "(" + std::to_string(i + 1) + ") " + answers[i] + '\n';
	}

	return result;
}