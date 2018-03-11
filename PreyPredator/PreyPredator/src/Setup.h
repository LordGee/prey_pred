#pragma once
#include <vector>

class Setup {
public:
	int PROJECT_TYPE, WIDTH, HEIGHT, PREY_PERCENT, PRED_PERCENT, RANDOM_SEED, DRAW_GRAPHICS, ITERATIONS;

private:
	std::vector<const char*> m_ProjectType;

public:
	Setup();
	void DisplaySelection();

private:
	void EditOptions(int value);
	void SelectProjectType();
	void IncorrectValueEntry(int& value, bool fail);
	int QuestionAnswer(const char* question);
	
};
