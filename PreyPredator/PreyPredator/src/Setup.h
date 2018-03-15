#pragma once
#include <vector>

class Setup {
public:
	int PROJECT_TYPE, WIDTH, HEIGHT, PREY_PERCENT, PRED_PERCENT, RANDOM_SEED, DRAW_GRAPHICS, ITERATIONS, THREADS, PROCESSORS;
	bool isMPI = false;

private:
	std::vector<const char*> m_ProjectType;
	const char* exefilename;

public:
	Setup();
	void DisplaySelection();

private:
	void EditOptions(int value);
	void SelectProjectType();
	void IncorrectValueEntry(int& value, bool fail);
	int QuestionAnswer(const char* question);
	
};
