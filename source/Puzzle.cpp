#include "Puzzle.hpp"

std::string Puzzle::getAsString() {
	std::string result{};
	result += question + "\n\n";
	
	for(size_t i = 0; i < this->answers.size(); i++) {
		result += "(" + std::to_string(i + 1) + ") " + answers[i] + '\n';
	}

	return result;
}