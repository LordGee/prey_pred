#pragma once
#include <vector>

class Setup {
public:
	int PROJECT_TYPE, WIDTH, HEIGHT, PREY_PERCENT, PRED_PERCENT;

private:
	std::vector<const char*> m_ProjectType;

	const char* m_GridOptions[2] = { 
		"Select Grid Size for X : ", 
		"Select Grid Size for Y : " 
	};
	
	int m_OptionStep = 0;

public:
	Setup();
	void DisplaySelection();

	void SelectProjectType();
	void SetWindowSize();
	
	
private:
	void RefreshConsole();
	
};
