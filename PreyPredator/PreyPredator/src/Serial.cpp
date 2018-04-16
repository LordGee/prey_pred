#include "Serial.h"
#include <cstdlib>
#include <ctime>

// Initial Population of the main grid based on percentages supplied
void Serial::PopulateGrid() {
	srand(seed);
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
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
	}
}

// Display Graphics Entry Point plus Main Loop
void Serial::DrawSimToScreen(const int COUNT) {
	int counter = 0;
	clock_t t1, t2;
	float timer;
	SDL_Event event;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("PREY vs PREDATOR Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);	
	while (counter < COUNT) {
		t1 = clock();
		livePrey = 0, livePred = 0, empty = 0;
		deadPrey = 0, deadPred = 0;
		UpdateSimulation();
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
		counter++;
		t2 = clock();
		timer = (float)(t2 - t1) / CLOCKS_PER_SEC;
		UpdateStatistics(timer, counter, livePrey, livePred, empty, deadPrey, deadPred);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// Display ASCI Statistics Entry Point plus Main Loop
void Serial::RunSimNoDraw(const int COUNT) {
	int counter = 0;
	clock_t t1, t2;
	float timer;
	while (counter < COUNT) {
		t1 = clock();
		deadPrey = 0, deadPred = 0;
		livePrey = 0, livePred = 0, empty = 0;
		UpdateSimulation();
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
		t2 = clock();
		timer = (float)(t2 - t1) / CLOCKS_PER_SEC;
		UpdateStatistics(timer, counter, livePrey, livePred, empty, 
			deadPrey, deadPred);
		counter++;
	}
}

// Display Nothing Entry Point plus Main Loop
void Serial::RunNoDisplay(const int COUNT) {
	noDraw = true;
	int counter = 0;
	clock_t t1, t2;
	float timer;
	while (counter < COUNT) {
		t1 = clock();
		UpdateSimulation();
		t2 = clock();
		timer = (float)(t2 - t1) / CLOCKS_PER_SEC;
		timerLog.push_back(timer);
		counter++;
	}
	float average = 0.0f;
	for (unsigned int i = 0; i < timerLog.size(); i++) {
		average += timerLog[i];
	}
	average = average / timerLog.size();
	std::cout << "Test Completed\nAverage time for each iteration - " << average << std::endl;
}

// Display statisics to console window
void Serial::UpdateStatistics(float time, int iteration, int lPrey, int lPred, int empty, int dPrey, int dPred) {
	system("cls");
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
}

// Update Simulator
void Serial::UpdateSimulation() {
	// generate COPY cell array
		// Loop COPY to init and zero off values
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			copyGrid[x][y].type = 0;
			copyGrid[x][y].age = 0;
		}
	}
	srand(time(NULL));
	// loop through all cells and determin neighbour count
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			int preyCount = 0, preyAge = 0, predCount = 0, predAge = 0;
			// Check neighbouring states and store information for evaluation
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					if (!(i == 0 && j == 0)) {
						int newX = x + i, newY = y + j;
						if (newY < 0) { newY = newY + height; }
						if (newX < 0) { newX = newX + width; }
						if (newY >= height) { newY = newY - height; }
						if (newX >= width) { newX = newX - width; }
						if (mainGrid[newX][newY].type > 0) {
							preyCount++;
							if (mainGrid[newX][newY].age >= PREY_BREEDING) {
								preyAge++;
							}
						} else if (mainGrid[newX][newY].type < 0) {
							predCount++;
							if (mainGrid[newX][newY].age >= PRED_BREEDING) {
								predAge++;
							}
						}
					}
				}
			}
			// set current cell to new value depending on rules
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
		for (int y = 0; y < height; y++) {
			mainGrid[x][y] = copyGrid[x][y];
		}
	}
}

