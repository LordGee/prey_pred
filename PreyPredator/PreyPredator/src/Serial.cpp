#include "Serial.h"
#include <cstdlib>
#include "SDL.h"
#include <ctime>

void Serial::PopulateGrid() {
	srand(seed);
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			float random = (float)(rand()) / (float)(RAND_MAX);
			if (random < prey) {
				newGrid[x][y].value = 1;
				newGrid[x][y].age = 1;
			} else if (random < prey + pred) {
				newGrid[x][y].value = -1;
				newGrid[x][y].age = 1;
			} else {
				newGrid[x][y].value = 0;
				newGrid[x][y].age = 0;
			}
		}
	}
	int z = 0;
}

void Serial::DrawSimToScreen(const int COUNT) {
	int counter = 0;
	int livePrey, livePred, empty;
	clock_t t1, t2;
	float timer;
	SDL_Event event;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("PREY vs PREDATOR Simulation",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	
	while (counter < COUNT) {
		t1 = clock();
		livePrey = 0, livePred = 0, empty = 0;
		SDL_PollEvent(&event);
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 125);
		SDL_RenderClear(renderer);
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				if (newGrid[x][y].value > 0) {
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
					SDL_RenderDrawPoint(renderer, x, y);
					livePrey++;
				} else if (newGrid[x][y].value < 0) {
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
		UpdateStatistics(timer, counter, livePrey, livePred, empty);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Serial::RunSimNoDraw(const int COUNT) {
	int counter = 0;
	int livePrey, livePred, empty;
	clock_t t1, t2;
	float timer;
	while (counter < COUNT) {
		t1 = clock();
		livePrey = 0, livePred = 0, empty = 0;

		// run sim

		counter++;
		t2 = clock();
		timer = (float)(t2 - t1) / CLOCKS_PER_SEC;
		UpdateStatistics(timer, counter, livePrey, livePred, empty);
	}
}

void Serial::UpdateStatistics(float time, int iteration, int lPrey, int lPred, int empty) {
	system("cls");
	printf(" WELCOME TO THE PREY VS PREDATOR SIMULATOR\n");
	printf("\t by Gordon Johnson (k1451760)\n\n");
	printf(" -------------------------------------------\n");
	printf(" | Stats            \t| Results            |\n");
	printf(" -------------------------------------------\n");
	printf(" | Speed            \t| %f\n", time);
	printf(" | Iteration Count  \t| %d\n", iteration);
	printf(" | Living Prey      \t| %d\n", lPrey);
	printf(" | Living Predators \t| %d\n", lPred);
	printf(" | Empty Cells      \t| %d\n", empty);
	printf(" -------------------------------------------\n");
}

void Serial::UpdateSimulation() {
	
}

