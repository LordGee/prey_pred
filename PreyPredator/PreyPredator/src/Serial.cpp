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

void Serial::DrawSimToScreen() {
	bool quit = false;
	
	/*
	SDL_Event event;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("PREY vs PREDATOR",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	while (!quit) {
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 150, 175, 255);
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				if (newGrid[x][y].value) {
					SDL_RenderDrawPoint(renderer, x, y);
				}
			}
		}
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	*/
}
