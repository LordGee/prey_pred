#include "Setup.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

Setup::Setup() {
	PROJECT_TYPE = 0;
	WIDTH = 100;
	HEIGHT = 100;
	PREY_PERCENT = 50;
	PRED_PERCENT = 25;
	m_ProjectType.push_back("Serial");
	m_ProjectType.push_back("OpenMP");
	m_ProjectType.push_back("MS MPI");
	m_ProjectType.push_back("Hybrid");
}

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

void Setup::DisplaySelection() {
	system("cls");
	std::cout << "WELCOME TO THE PREY VS PREDATOR SIMULATOR" << std::endl;
	std::cout << "\tby Gordon Johnson (k1451760)" << std::endl;
	std::cout << std::endl;
	std::cout << "The following options have been selected:" << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;
	std::cout << "| OPTION | DISCRIPTION                  | SELECTION " << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;
	std::cout << "| 1.\t | Simulation Type:\t\t| " << m_ProjectType[PROJECT_TYPE] << std::endl;
	std::cout << "| 2.\t | Grid Width:\t\t\t| " << WIDTH << std::endl;
	std::cout << "| 3.\t | Grid Height:\t\t\t| " << HEIGHT << std::endl;
	std::cout << "| 4.\t | Prey Percentage:\t\t| " << PREY_PERCENT << std::endl;
	std::cout << "| 5.\t | Predator Percentage:\t\t| " << PRED_PERCENT << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << "Select an option to edit (1, 2, 3, 4, 5) or press enter to accept";
	int tempSelection;
	std::cin >> tempSelection;
	switch (tempSelection) {
	case 1:
		std::cout << "You selected something good" << std::endl;
		break;
	case 2:
		std::cout << "Change grid size" << std::endl;
		break;
	case 3:
		std::cout << "Change grid size" << std::endl;
		break;
	case 4:
		std::cout << "Change grid size" << std::endl;
		break;
	case 5:
		std::cout << "Change grid size" << std::endl;
		break;
	default:
		DisplaySelection();
	}
	
}
