#pragma once

class Setup {
public:
	int WIDTH = -1, HEIGHT = -1, PROJECT_TYPE = -1;

private:
	const char* m_ProjectType[4] = {
		"1. \tSerial",
		"2. \tOpenMP",
		"3. \tMicrosoft MPI",
		"4. \tHybrid",
	};

	const char* m_GridOptions[2] = { 
		"Select Grid Size for X : ", 
		"Select Grid Size for Y : " 
	};
	
	int m_OptionStep = 0;

public:
	void SelectProjectType();
	void SetWindowSize();

	
private:
	void RefreshConsole();
};