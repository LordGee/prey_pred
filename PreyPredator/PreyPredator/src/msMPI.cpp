#include "msMPI.h"
#include <cstdlib>
#include <ctime>
#include <string>

void MsMPI::PopulateGrid() {
	srand(seed);
	const int contributionY = abs(height / info.numProcs);
	int processorCounter = 1;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			// Only the master manages the initial declaration of each cell state
			if (info.procRank == MASTER) {
				float random = (float)(rand()) / (float)(RAND_MAX);
				if (random < prey) {
					mainGrid[x][y].type = 1;
					mainGrid[x][y].age = 1;
				} else if (random < prey + pred) {
					mainGrid[x][y].type = -1;
					mainGrid[x][y].age = 1;
				} else {
					mainGrid[x][y].type = 0;
					mainGrid[x][y].age = 0;
				}
			}
			// determine if the y value has exceeded the current processor split
			if (y >= contributionY * (processorCounter + 1)) {
				if (processorCounter != info.numProcs - 1) {
					processorCounter++;
				}
			}
			// If within the current processor copy the master cell to the appropriate processor
			if (y >= contributionY * processorCounter && 
				y < contributionY * (processorCounter + 1)) {
				if (info.procRank == MASTER) {
					MPI_Send(&mainGrid[x][y], 2, MPI_INT, processorCounter, y, MPI_COMM_WORLD);
				}
				if (info.procRank == processorCounter) {
					MPI_Recv(&mainGrid[x][y], 2, MPI_INT, 0, y, MPI_COMM_WORLD, &status);
				}
			}
		}
		// at the end of each y iteration reset processor to 1
		processorCounter = 1;
	}
}

void MsMPI::DrawSimToScreen(const int COUNT) {
	noDraw = false;
	int counter = 0;
	clock_t t1, t2;
	float timer;
	SDL_Event event;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	// Only master process should draw to screen
	if (info.procRank == MASTER) {
		SDL_Init(SDL_INIT_VIDEO);
		window = SDL_CreateWindow("PREY vs PREDATOR Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
		renderer = SDL_CreateRenderer(window, -1, 0);
	}
	while (counter < COUNT) {
		t1 = clock();
		livePrey = 0, livePred = 0, empty = 0;
		deadPrey = 0, deadPred = 0;
		UpdateSimulation();
		// Only master process should draw to screen
		if (info.procRank == MASTER) {
			SDL_PollEvent(&event);
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 125);
			SDL_RenderClear(renderer);
			for (int x = 0; x < width; x++) {
				for (int y = 0; y < height; y++) {
					if (mainGrid[x][y].type > 0) {
						SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
						SDL_RenderDrawPoint(renderer, x, y);
						livePrey++;
					} else if (mainGrid[x][y].type < 0) {
						SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
						SDL_RenderDrawPoint(renderer, x, y);
						livePred++;
					} else {
						empty++;
					}
				}
			}
			SDL_RenderPresent(renderer);
		}
		counter++;
		t2 = clock();
		timer = (float)(t2 - t1) / CLOCKS_PER_SEC;
		// Only master process should draw to screen
		if (info.procRank == MASTER) {
			UpdateStatistics(timer, counter, livePrey, livePred, empty, deadPrey, deadPred);
		}
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void MsMPI::RunSimNoDraw(const int COUNT) {
	noDraw = false;
	int counter = 0;
	clock_t t1, t2;
	float timer;
	while (counter < COUNT) {
		t1 = clock();
		deadPrey = 0, deadPred = 0;
		livePrey = 0, livePred = 0, empty = 0;
		UpdateSimulation();
		// Only master process should draw to screen
		if (info.procRank == MASTER) {
			for (int x = 0; x < width; x++) {
				for (int y = 0; y < height; y++) {
					if (mainGrid[x][y].type > 0) {
						livePrey++;
					} else if (mainGrid[x][y].type < 0) {
						livePred++;
					} else {
						empty++;
					}
				}
			}
		}
		counter++;
		t2 = clock();
		timer = (float)(t2 - t1) / CLOCKS_PER_SEC;
		// Only master process should draw to screen
		if (info.procRank == MASTER) {
			UpdateStatistics(timer, counter, livePrey, livePred, empty, deadPrey, deadPred);
		}
	}
}

void MsMPI::RunNoDisplay(const int COUNT) {
	noDraw = true;
	int counter = 0;
	clock_t t1, t2;
	float timer;
	while (counter < COUNT) {
		t1 = clock();
		UpdateSimulation();
		counter++;
		t2 = clock();
		timer = (float)(t2 - t1) / CLOCKS_PER_SEC;
		// Only master process should log timer information
		if (info.procRank == MASTER) {
			timerLog.push_back(timer);
		}
	}
	// Only master process should draw to screen
	if (info.procRank == MASTER) {
		float average = 0.0f;
		for (unsigned int i = 0; i < timerLog.size(); i++) {
			average += timerLog[i];
		}
		average = average / timerLog.size();
		std::cout << "Test Completed\nAverage time for each iteration - " << average << std::endl;
		fflush(stdout);
	}
}

void MsMPI::UpdateStatistics(float time, int iteration, int lPrey, int lPred, int empty, int dPrey, int dPred) {
	// system("cls"); // Removed MPI does not like this feature
	printf(" WELCOME TO THE PREY VS PREDATOR SIMULATOR\n");
	printf("\t by Gordon Johnson (k1451760)\n\n");
	printf(" -------------------------------------------\n");
	printf(" | Statistic        \t| Results\n");
	printf(" -------------------------------------------\n");
	printf(" | Speed            \t| %f\n", time);
	printf(" | Iteration Count  \t| %d\n", iteration);
	printf(" -------------------------------------------\n");
	printf(" | Living Prey      \t| %d\n", lPrey);
	printf(" | Dying Prey      \t| %d\n", dPrey);
	printf(" -------------------------------------------\n");
	printf(" | Living Predators \t| %d\n", lPred);
	printf(" | Dying Predators \t| %d\n", dPred);
	printf(" -------------------------------------------\n");
	printf(" | Empty Cells      \t| %d\n", empty);
	printf(" | Total Cells      \t| %d\n", empty + lPrey + lPred);
	printf(" -------------------------------------------\n");
	fflush(stdout);
}

void MsMPI::UpdateSimulation() {

	// generate COPY cell array
	// Loop COPY to init and zero off values
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			copyGrid[x][y].type = 0;
			copyGrid[x][y].age = 0;
		}
	}
	const int contributionY = abs(height / info.numProcs);
	srand(time(NULL));
	
	// prepare top and bottom bounderies for evaluating neighbouring states
	for (int x = 0; x < width; x++) {
		if (info.procRank == MASTER) {
			MPI_Send(&mainGrid[x][0], 2, MPI_INT, info.numProcs - 1, x, MPI_COMM_WORLD);
			MPI_Recv(&mainGrid[x][height - 1], 2, MPI_INT, info.numProcs - 1, x + width, MPI_COMM_WORLD, &status);
		}
		else if (info.procRank == info.numProcs - 1) {
			MPI_Send(&mainGrid[x][height - 1], 2, MPI_INT, 0, x + width, MPI_COMM_WORLD);
			MPI_Recv(&mainGrid[x][0], 2, MPI_INT, 0, x, MPI_COMM_WORLD, &status);
		}
		if (info.procRank != info.numProcs - 1) {
			MPI_Send(&mainGrid[x][(contributionY * (info.procRank + 1)) - 1], 2, MPI_INT, info.procRank + 1, x, MPI_COMM_WORLD);
			MPI_Recv(&mainGrid[x][(contributionY * (info.procRank + 1))], 2, MPI_INT, info.procRank + 1, x, MPI_COMM_WORLD, &status);
		}
		if (info.procRank != MASTER) {
			MPI_Send(&mainGrid[x][contributionY * info.procRank], 2, MPI_INT, info.procRank - 1, x, MPI_COMM_WORLD);
			MPI_Recv(&mainGrid[x][(contributionY * info.procRank) - 1], 2, MPI_INT, info.procRank - 1, x, MPI_COMM_WORLD, &status);
		}
	}
	// loop through all cells and determin neighbour count
	MPI_Barrier(MPI_COMM_WORLD);
	for (int x = 0; x < width; x++) {
		// Only unique processer dependent y range is processed
		for (int y = contributionY * info.procRank; y < contributionY * (info.procRank + 1); y++) {
			int preyCount = 0, preyAge = 0, predCount = 0, predAge = 0;
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					if (!(i == 0 && j == 0)) {
						int xTest = x + i, yTest = y + j;
						if (yTest < 0) { yTest = yTest + height; }
						if (xTest < 0) { xTest = xTest + width; }
						if (yTest >= height) { yTest = yTest - height; }
						if (xTest >= width) { xTest = xTest - width; }
						if (mainGrid[xTest][yTest].type > 0) {
							preyCount++;
							if (mainGrid[xTest][yTest].age >= PREY_BREEDING) {
								preyAge++;
							}
						} else if (mainGrid[xTest][yTest].type < 0) {
							predCount++;
							if (mainGrid[xTest][yTest].age >= PRED_BREEDING) {
								predAge++;
							}
						}
					}
				}
			}
			if (mainGrid[x][y].type > 0) {
				//manage prey
				if (predCount >= 5 || preyCount == 8 || mainGrid[x][y].age > PREY_LIVE) {
					copyGrid[x][y].type = 0;
					copyGrid[x][y].age = 0;
					deadPrey++;
				} else {
					copyGrid[x][y].type = mainGrid[x][y].type;
					copyGrid[x][y].age = mainGrid[x][y].age + 1;
				}
			} else if (mainGrid[x][y].type < 0) {
				// manage predator
				float random = (float)(rand()) / (float)(RAND_MAX);
				if ((predCount >= 6 && preyCount == 0) || random <= PRED_SUDDEN_DEATH || copyGrid[x][y].age > PRED_LIVE) {
					copyGrid[x][y].type = 0;
					copyGrid[x][y].age = 0;
					deadPred++;
				} else {
					copyGrid[x][y].type = mainGrid[x][y].type;
					copyGrid[x][y].age = mainGrid[x][y].age + 1;
				}
			} else {
				// manage empty space
				if (preyCount >= NUM_BREEDING && preyAge >= NUM_OF_AGE && predCount < NUM_OF_WITNESSES) {
					copyGrid[x][y].type = 1;
					copyGrid[x][y].age = 1;
				} else if (predCount >= NUM_BREEDING && predAge >= NUM_OF_AGE && preyCount < NUM_OF_WITNESSES) {
					copyGrid[x][y].type = -1;
					copyGrid[x][y].age = 1;
				} else {
					copyGrid[x][y].type = 0;
					copyGrid[x][y].age = 0;
				}
			}
		}
	}
	// copy the COPY back to the main array
	for (int x = 0; x < width; x++) {
		// Only unique processer dependent y range is processed
		for (int y = contributionY * info.procRank; y < contributionY * (info.procRank + 1); y++) {
			mainGrid[x][y] = copyGrid[x][y];
		}
	}

	// If setup dissplay is drawing stats to screen the MASTER process needs all grid information sent to it
	if (!noDraw) {
		int processorCounter = info.numProcs - 1;
		while (processorCounter != 0) {
			for (int x = 0; x < width; x++) {
				for (int y = contributionY * processorCounter; y < height; y++) {
					if (info.procRank == processorCounter) {
						MPI_Rsend(&mainGrid[x][y], 2, MPI_INT, processorCounter - 1, y * (x + processorCounter), MPI_COMM_WORLD);
					}
					if (info.procRank == processorCounter - 1) {
						MPI_Recv(&mainGrid[x][y], 2, MPI_INT, processorCounter, y * (x + processorCounter), MPI_COMM_WORLD, &status);
					}
				}
			}
			processorCounter--;
		}
	}
}

