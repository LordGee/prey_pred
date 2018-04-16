#pragma once
#include <vector>

class Setup {
public:
	int projectType, width, height, preyPercentage, PredPercentage, randomSeed, display, iterations, threads, processes;
	bool isMPI = false;

private:
	std::vector<const char*> m_ProjectType;
	const char* m_Exefilename;

public:
	Setup();
	void DisplaySelection();

private:
	void EditOptions(int value);
	void SelectProjectType();
	void IncorrectValueEntry(int& value, bool fail);
	int QuestionAnswer(const char* question);
	std::string GenerateExeLauncher();
	
};
