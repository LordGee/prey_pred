#pragma once
#include <vector>

class Setup {
public:
	int PROJECT_TYPE, WIDTH, HEIGHT, PREY_PERCENT, PRED_PERCENT;

private:
	std::vector<const char*> m_ProjectType;


public:
	Setup();
	void DisplaySelection();
	
	
	
private:
	void SelectProjectType();
	void EditOptions(int value);
	void IncorrectValueEntry(int& value, bool fail);
	
};
