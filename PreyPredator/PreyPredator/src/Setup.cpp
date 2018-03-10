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
	std::cout << std::endl;
	std::cout << "Select type of project to run:" << std::endl;
	for (int i= 0; i < 4; i++) {
		std::cout << m_ProjectType[i] << std::endl;
	}
	std::cin >> PROJECT_TYPE;
	PROJECT_TYPE = PROJECT_TYPE - 1;
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
	std::cout << "Select an option to edit (1, 2, 3, 4, 5) " << std::endl;
	std::cout << "...or press enter (0) to accept the above." << std::endl;
	int tempSelection;
	std::cin >> tempSelection;
	IncorrectValueEntry(tempSelection, std::cin.fail());
	EditOptions(tempSelection);
}

void Setup::EditOptions(int value) {
	int tempValue;
	switch (value) {
	case 0:
		break;
	case 1:
		SelectProjectType();
		DisplaySelection();
	case 2:
		std::cout << "How many grid cells would you like for the WIDTH?" << std::endl;
		std::cin >> tempValue;
		IncorrectValueEntry(tempValue, std::cin.fail());
		while (tempValue < 10) {
			std::cout << "Choose a number larger then 10 ..." << std::endl;
			std::cin >> tempValue;
			IncorrectValueEntry(tempValue, std::cin.fail());
		}
		WIDTH = tempValue;	
		DisplaySelection();
	case 3:
		std::cout << "How many grid cells would you like for the HEIGHT?" << std::endl;
		std::cin >> tempValue;
		IncorrectValueEntry(tempValue, std::cin.fail());
		while (tempValue < 10) {
			std::cout << "Choose a number larger then 10 ..." << std::endl;
			std::cin >> tempValue;
			IncorrectValueEntry(tempValue, std::cin.fail());
		}
		HEIGHT = tempValue;
		DisplaySelection();
	case 4:
		std::cout << "What percentage of starting PREY would you like?" << std::endl;
		std::cin >> tempValue;
		IncorrectValueEntry(tempValue, std::cin.fail());
		while (tempValue < 1 || tempValue > 100) {
			std::cout << "Choose a pecentage value larger then 0 and less then 100 ..." << std::endl;
			std::cin >> tempValue;
			IncorrectValueEntry(tempValue, std::cin.fail());
		}
		if (PRED_PERCENT + tempValue > 100) {
			PRED_PERCENT = 100 - tempValue;
		}
		PREY_PERCENT = tempValue;
		DisplaySelection();
	case 5:
		std::cout << "What percentage of starting PREDATORS would you like?" << std::endl;
		std::cin >> tempValue;
		IncorrectValueEntry(tempValue, std::cin.fail());
		while (tempValue < 1 || tempValue > 100) {
			std::cout << "Choose a pecentage value larger then 0 and less then 100 ..." << std::endl;
			std::cin >> tempValue;
			IncorrectValueEntry(tempValue, std::cin.fail());
		}
		if (PREY_PERCENT + tempValue > 100) {
			PREY_PERCENT = 100 - tempValue;
		}
		PRED_PERCENT = tempValue;
		DisplaySelection();
	default:
		DisplaySelection();
		break;
	}
}

void Setup::IncorrectValueEntry(int& value, bool fail) {
	while (fail) {
		std::cout << "Incorrect value entry, please try again!" << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> value;
		fail = std::cin.fail();
	}
}
