#pragma once

#include <string>
#include <vector>
#include <fstream>

class Puzzle {
private:
protected:
	std::string question;
	std::vector<std::string> answers;
	int indexOfCorrectAnswer;
public:
	Puzzle(std::string nameFile);
	~Puzzle() = default;
	std::string getAsString();

	int getIndexOfCorrectAnswer() const { return indexOfCorrectAnswer; }
	int getNumberOfAnswers() const { return answers.size(); }
};

