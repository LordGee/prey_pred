#include "Setup.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdlib>

Setup::Setup() {
	// Set default values
	PROJECT_TYPE = 1;
	WIDTH = 12;
	HEIGHT = 12;
	PREY_PERCENT = 50;
	PRED_PERCENT = 25;
	RANDOM_SEED = 1234;
	DRAW_GRAPHICS = 0;
	ITERATIONS = 1000;
	PROCESSORS = 1;
	THREADS = 1;

	// Define diferent tyypes of projects
	m_ProjectType.push_back("Serial");
	m_ProjectType.push_back("OpenMP");
	m_ProjectType.push_back("MS MPI");
	m_ProjectType.push_back("Hybrid");

	/* File location depending on execution method (Comment out unused) */
	// exefilename = "PreyPredator.exe"; // production mode
	// exefilename = "../bin/release/PreyPredator.exe"; // release mode run through VS
	exefilename = "../bin/debug/PreyPredator.exe"; // debug mode run through VS

	//exefilename = "../bin/debug/run.bat"; // debug mode run through VS
}

void Setup::DisplaySelection() {
	// system("cls");
	std::cout << "WELCOME TO THE PREY VS PREDATOR SIMULATOR" << std::endl;
	std::cout << "\tby Gordon Johnson (k1451760)" << std::endl;
	std::cout << std::endl;
	std::cout << "You have " << PROCESSORS << " processes available in this instance." << std::endl;
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
	std::cout << "| 6.\t | Random Seed:\t\t\t| " << RANDOM_SEED << std::endl;
	std::cout << "| 7.\t | Graphics Mode:\t\t| " << ((DRAW_GRAPHICS == 1) ? "YES" : "NO") << std::endl;
	std::cout << "| 8.\t | Number of Iterations:\t| " << ITERATIONS << std::endl;
	std::cout << "| 9.\t | Number of Threads:\t\t| " << THREADS << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << "Select an option to edit (1, 2, 3, 4, 5, 6, 7, 8, 9) " << std::endl;
	std::cout << "...or press enter (0) to accept the above." << std::endl;
	int tempValue = -1;
	std::cout << "\n>>> ";
	std::cin >> tempValue;
	IncorrectValueEntry(tempValue, std::cin.fail());
	while (tempValue < 0 || tempValue > 9) {
		tempValue = QuestionAnswer("Choose one of the above options only...");
	}
	EditOptions(tempValue);
}

void Setup::EditOptions(int value) {
	int tempValue = -1;
	switch (value) {
	case 0:
		break;
	case 1:
		SelectProjectType();
		DisplaySelection();
		break;
	case 2:
		tempValue = QuestionAnswer("How many grid cells would you like for the WIDTH?");
		while (tempValue < 10) {
			tempValue = QuestionAnswer("Choose a number larger then 10 ...");
		}
		WIDTH = tempValue;	
		DisplaySelection();
		break;
	case 3:
		tempValue = QuestionAnswer("How many grid cells would you like for the HEIGHT?");
		while (tempValue < 10) {
			tempValue = QuestionAnswer("Choose a number larger then 10 ...");
		}
		HEIGHT = tempValue;
		DisplaySelection();
		break;
	case 4:
		tempValue = QuestionAnswer("What percentage of starting PREY would you like?");
		while (tempValue < 1 || tempValue > 100) {
			tempValue = QuestionAnswer("Choose a pecentage value larger then 0 and less then 100 ...");
		}
		if (PRED_PERCENT + tempValue > 100) {
			PRED_PERCENT = 100 - tempValue;
		}
		PREY_PERCENT = tempValue;
		DisplaySelection();
		break;
	case 5:
		tempValue = QuestionAnswer("What percentage of starting PREDATORS would you like?");
		while (tempValue < 1 || tempValue > 100) {
			tempValue = QuestionAnswer("Choose a pecentage value larger then 0 and less then 100 ...");
		}
		if (PREY_PERCENT + tempValue > 100) {
			PREY_PERCENT = 100 - tempValue;
		}
		PRED_PERCENT = tempValue;
		DisplaySelection();
		break;
	case 6:
		tempValue = QuestionAnswer("Choose the random SEED value that will be used to generate the grid?");
		while (tempValue < 0 || tempValue > 99999) {
			tempValue = QuestionAnswer("Choose a number between 1 and 99999 ...");
		}
		RANDOM_SEED = tempValue;
		DisplaySelection();
		break;
	case 7:
		tempValue = QuestionAnswer("Would you like the graphics of the simulation to be drawn to the screen? \n\t( 1 = YES / 0 = NO )");
		while (tempValue < 0 || tempValue > 1) {
			tempValue = QuestionAnswer("Choose option 1 or 0 ...");
		}
		DRAW_GRAPHICS = tempValue;
		DisplaySelection();
		break;
	case 8:
		tempValue = QuestionAnswer("How many iterations would you like the simulation to go through?");
		while (tempValue < 1) {
			tempValue = QuestionAnswer("You need to have at least 1 iteration ...");
		}
		ITERATIONS = tempValue;
		DisplaySelection();
		break;
	case 9:
		tempValue = QuestionAnswer("How many threads would you like to use for this simulation?");
		IncorrectValueEntry(tempValue, std::cin.fail());
		while (tempValue < 1 || tempValue > 32) {
			tempValue = QuestionAnswer("Choose a sensible thread value between 1 and 32...");
		}
		THREADS = tempValue;
		DisplaySelection();
		break;
	default:
		DisplaySelection();
		break;
	}
}

void Setup::SelectProjectType() {
	std::cout << std::endl;
	std::cout << "Select type of project to run:" << std::endl;
	for (int i = 0; i < m_ProjectType.size(); i++) {
		std::cout << "\t" << i + 1 << ". \t" << m_ProjectType[i] << std::endl;
	}
	std::cout << ">>> ";
	int tempValue = -1;
	std::cin >> tempValue;
	IncorrectValueEntry(tempValue, std::cin.fail());
	while (tempValue < 1 || tempValue > m_ProjectType.size()) {
		tempValue = QuestionAnswer("Choose one of the above options only...");
	}
	PROJECT_TYPE = tempValue - 1;
	if (PROCESSORS <= 1) {
		if (tempValue > 2) {
			std::cout << "WARNING: This will restart application and reset all previously configured settings back to default." << std::endl;
			int procValue = QuestionAnswer("How many processes would you like to use for this simulation?");
			IncorrectValueEntry(procValue, std::cin.fail());
			while (procValue < 1 || procValue > 32) {
				procValue = QuestionAnswer("Choose a sensible processor value between 1 and 32...");
			}
			PROCESSORS = procValue;

			system(GenerateExeLauncher().c_str());
		}
	}
}

void Setup::IncorrectValueEntry(int& value, bool fail) {
	while (fail) {
		std::cout << "Incorrect value entry, please try again!" << std::endl;
		std::cout << "\n>>> ";
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> value;
		fail = std::cin.fail();
	}
}

int Setup::QuestionAnswer(const char* question) {
	int value;
	std::cout << question << std::endl;
	std::cout << "\n>>> ";
	std::cin >> value;
	IncorrectValueEntry(value, std::cin.fail());
	return value;
}

std::string Setup::GenerateExeLauncher() {
	std::string output;
	std::string initValue = "mpiexec -n ";
	output = initValue + std::to_string(PROCESSORS) + " " + exefilename;
	printf("%s", output);
	return output;
}
