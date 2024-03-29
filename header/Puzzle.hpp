#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class Puzzle {
private:
protected:
	std::string question;
	int indexOfCorrectAnswer;
	std::vector<std::string> answers;
public:
	Puzzle(std::string question, int indexOfCorrectAnswer, std::vector<std::string> answers)
		:question{ question }, indexOfCorrectAnswer{ indexOfCorrectAnswer }, answers{ answers } {}
	~Puzzle() = default;

	std::string getAsString();

	int getIndexOfCorrectAnswer() const { return indexOfCorrectAnswer; }
	size_t getNumberOfAnswers() const { return answers.size(); }
	std::string getQuestion() const { return question; }

	void setIndexOfCorrectAnswer(int indexOfCorrectAnswer) { this->indexOfCorrectAnswer = indexOfCorrectAnswer; }
	void setQuestion(std::string question) { this->question = question; }
	void setAnswers(std::vector<std::string> answers) { this->answers = answers; }
};

