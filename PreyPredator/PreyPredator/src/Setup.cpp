#include "Setup.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdlib>

// Constructor
Setup::Setup() {
	// Set default values
	projectType = 1;
	width = 1000;
	height = 1000;
	preyPercentage = 50;
	PredPercentage = 25;
	randomSeed = 1234;
	display = 1;
	iterations = 1000;
	processes = 1;
	threads = 1;

	// Define diferent tyypes of projects
	m_ProjectType.push_back("Serial");
	m_ProjectType.push_back("OpenMP");
	m_ProjectType.push_back("MS MPI");
	m_ProjectType.push_back("Hybrid");

	/* File location depending on execution method (Comment out unused) */
	m_Exefilename = "PreyPredator.exe"; // production mode
	// exefilename = "../bin/release/PreyPredator.exe"; // release mode run through VS
	// exefilename = "../bin/debug/PreyPredator.exe"; // debug mode run through VS
	//exefilename = "../bin/debug/run.bat"; // debug mode run through VS
}

// ASCI display options
void Setup::DisplaySelection() {
	system("cls");
	std::cout << "WELCOME TO THE PREY VS PREDATOR SIMULATOR" << std::endl;
	std::cout << "\tby Gordon Johnson (k1451760)" << std::endl;
	std::cout << std::endl;
	std::cout << "You have " << processes << " processes available in this instance." << std::endl;
	std::cout << std::endl;
	std::cout << "The following options have been selected:" << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;
	std::cout << "| OPTION | DISCRIPTION                  | SELECTION " << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;
	std::cout << "| 1.\t | Simulation Type:\t\t| " << m_ProjectType[projectType] << std::endl;
	std::cout << "| 2.\t | Grid Width:\t\t\t| " << width << std::endl;
	std::cout << "| 3.\t | Grid Height:\t\t\t| " << height << std::endl;
	std::cout << "| 4.\t | Prey Percentage:\t\t| " << preyPercentage << std::endl;
	std::cout << "| 5.\t | Predator Percentage:\t\t| " << PredPercentage << std::endl;
	std::cout << "| 6.\t | Random Seed:\t\t\t| " << randomSeed << std::endl;
	std::cout << "| 7.\t | Graphics Mode:\t\t| " << ((display == 1) ? "Graphics" : (display == 2) ? "ASCI" : "No Display") << std::endl;
	std::cout << "| 8.\t | Number of Iterations:\t| " << iterations << std::endl;
	std::cout << "| 9.\t | Number of Threads:\t\t| " << threads << std::endl;
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

// Manage selected options
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
		width = tempValue;	
		DisplaySelection();
		break;
	case 3:
		tempValue = QuestionAnswer("How many grid cells would you like for the HEIGHT?");
		while (tempValue < 10) {
			tempValue = QuestionAnswer("Choose a number larger then 10 ...");
		}
		height = tempValue;
		DisplaySelection();
		break;
	case 4:
		tempValue = QuestionAnswer("What percentage of starting PREY would you like?");
		while (tempValue < 1 || tempValue > 100) {
			tempValue = QuestionAnswer("Choose a pecentage value larger then 0 and less then 100 ...");
		}
		if (PredPercentage + tempValue > 100) {
			PredPercentage = 100 - tempValue;
		}
		preyPercentage = tempValue;
		DisplaySelection();
		break;
	case 5:
		tempValue = QuestionAnswer("What percentage of starting PREDATORS would you like?");
		while (tempValue < 1 || tempValue > 100) {
			tempValue = QuestionAnswer("Choose a pecentage value larger then 0 and less then 100 ...");
		}
		if (preyPercentage + tempValue > 100) {
			preyPercentage = 100 - tempValue;
		}
		PredPercentage = tempValue;
		DisplaySelection();
		break;
	case 6:
		tempValue = QuestionAnswer("Choose the random SEED value that will be used to generate the grid?");
		while (tempValue < 0 || tempValue > 99999) {
			tempValue = QuestionAnswer("Choose a number between 1 and 99999 ...");
		}
		randomSeed = tempValue;
		DisplaySelection();
		break;
	case 7:
		tempValue = QuestionAnswer("Would you like the graphics of the simulation to be drawn to the screen? \n\t1 = Full Graphics plus Stats \n\t2 = ASCI only Stats \n\t3 = No Display Output");
		while (tempValue < 1 || tempValue > 3) {
			tempValue = QuestionAnswer("Choose option 1, 2 or 3 ...");
		}
		display = tempValue;
		DisplaySelection();
		break;
	case 8:
		tempValue = QuestionAnswer("How many iterations would you like the simulation to go through?");
		while (tempValue < 1) {
			tempValue = QuestionAnswer("You need to have at least 1 iteration ...");
		}
		iterations = tempValue;
		DisplaySelection();
		break;
	case 9:
		tempValue = QuestionAnswer("How many threads would you like to use for this simulation?");
		IncorrectValueEntry(tempValue, std::cin.fail());
		while (tempValue < 2 || tempValue > 32) {
			tempValue = QuestionAnswer("Choose a sensible thread value between 2 and 32...");
		}
		threads = tempValue;
		DisplaySelection();
		break;
	default:
		DisplaySelection();
		break;
	}
}

// Manage project type change, if MPI related relaunch application
void Setup::SelectProjectType() {
	std::cout << std::endl;
	std::cout << "Select type of project to run:" << std::endl;
	for (unsigned int i = 0; i < m_ProjectType.size(); i++) {
		std::cout << "\t" << i + 1 << ". \t" << m_ProjectType[i] << std::endl;
	}
	std::cout << ">>> ";
	int tempValue = -1;
	std::cin >> tempValue;
	IncorrectValueEntry(tempValue, std::cin.fail());
	while (tempValue < 1 || tempValue > (signed int)m_ProjectType.size()) {
		tempValue = QuestionAnswer("Choose one of the above options only...");
	}
	projectType = tempValue - 1;
	if (processes <= 1) {
		if (tempValue > 2) {
			std::cout << "WARNING: This will restart application and reset all previously configured settings back to default." << std::endl;
			int procValue = QuestionAnswer("How many processes would you like to use for this simulation?");
			IncorrectValueEntry(procValue, std::cin.fail());
			while (procValue < 2 || procValue > 32) {
				procValue = QuestionAnswer("Choose a sensible processor value between 2 and 32...");
			}
			processes = procValue;

			system(GenerateExeLauncher().c_str());
		}
	}
}

// Manage user incorrect option input
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

// Refactored to display question and manage incorrect inputs
int Setup::QuestionAnswer(const char* question) {
	int value;
	std::cout << question << std::endl;
	std::cout << "\n>>> ";
	std::cin >> value;
	IncorrectValueEntry(value, std::cin.fail());
	return value;
}

// Handles execution string for launching into MPI project type
std::string Setup::GenerateExeLauncher() {
	std::string output;
	std::string initValue = "mpiexec -n ";
	output = initValue + std::to_string(processes) + " " + m_Exefilename;
	printf("%s", output);
	return output;
}
