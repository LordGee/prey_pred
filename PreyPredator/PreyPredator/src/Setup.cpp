#include "Setup.h"
#include <iostream>


void Setup::SelectProjectType() {
	std::cout << "Select type of application to run:" << std::endl;
	for (int i= 0; i < 4; i++) {
		std::cout << m_ProjectType[i] << std::endl;
	}
	std::cin >> PROJECT_TYPE;
	PROJECT_TYPE = PROJECT_TYPE - 1;
	m_OptionStep++;
	RefreshConsole();
}

void Setup::SetWindowSize() {
	std::cout << m_GridOptions[0];
	std::cin >> WIDTH;
	m_OptionStep++;
	RefreshConsole();

	std::cout << m_GridOptions[1];
	std::cin >> HEIGHT;
	m_OptionStep++;
	RefreshConsole();
}

void Setup::RefreshConsole() {
	system("cls");
	std::cout << "You have choosen the following options:" << std::endl;
	int tempValue = m_OptionStep;
	for (int i = 0; i < tempValue; i++) {
		switch (tempValue - i) {
		case 1:
			std::cout << "\tProject Type: \t\t" << m_ProjectType[PROJECT_TYPE] << std::endl;
			break;
		case 2:
			std::cout << "\tGrid Width: \t\t" << WIDTH << std::endl;
			break;
		case 3:
			std::cout << "\tGrid Height: \t\t" << HEIGHT << std::endl;
			break;
		}
		
	}
	 
}

