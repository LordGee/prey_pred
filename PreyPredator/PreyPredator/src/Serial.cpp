#include "Serial.h"
#include <cstdlib>
#include "SDL.h"

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

void Serial::DrawSimToScreen(int count) {
	int counter = 0;

	SDL_Event event;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("PREY vs PREDATOR",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
	SDL_Renderer* rendererPrey = SDL_CreateRenderer(window, -1, 0);
	

	while (counter < count) {
		SDL_PollEvent(&event);
		SDL_SetRenderDrawColor(rendererPrey, 0, 0, 255, 125);
		SDL_RenderClear(rendererPrey);
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				if (newGrid[x][y].value > 0) {
					SDL_SetRenderDrawColor(rendererPrey, 0, 255, 0, 255);
					SDL_RenderDrawPoint(rendererPrey, x, y);
				} else if (newGrid[x][y].value < 0) {
					
					SDL_SetRenderDrawColor(rendererPrey, 255, 0, 0, 255);
					SDL_RenderDrawPoint(rendererPrey, x, y);
				}
			}
		}
		SDL_RenderPresent(rendererPrey);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();

}
