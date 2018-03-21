#include "msMPI.h"
#include <cstdlib>
#include <ctime>

void MsMPI::PopulateGrid() {
	srand(seed);
	if (info.rank == 0) {
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
				if (y >= height / 2) {
					MPI_Send(&newGrid[x][y].value, 1, MPI_INT, 1, y, MPI_COMM_WORLD);
					MPI_Send(&newGrid[x][y].age, 1, MPI_INT, 1, y * x + 1, MPI_COMM_WORLD);
				}
			}
		}
	} else if (info.rank == 1) {
		for (int x = 0; x < width; x++) {
			for (int y = height / 2; y < height; y++) { // is it plus one?
				MPI_Recv(&newGrid[x][y].value, 1, MPI_INT, 0, y, MPI_COMM_WORLD, &status);
				MPI_Recv(&newGrid[x][y].age, 1, MPI_INT, 0, y * x + 1, MPI_COMM_WORLD, &status);
			}
		}
	}
}

void MsMPI::DrawSimToScreen(const int COUNT) {
	int counter = 0;
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
		deadPrey = 0, deadPred = 0;
		UpdateSimulation();
		if (info.rank == 0) {
			SDL_PollEvent(&event);
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 125);
			SDL_RenderClear(renderer);
			for (int x = 0; x < width; x++) {
				for (int y = 0; y < height; y++) {
					if (newGrid[x][y].value > 0) {
						SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
						SDL_RenderDrawPoint(renderer, x, y);
						livePrey++;
					}
					else if (newGrid[x][y].value < 0) {
						SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
						SDL_RenderDrawPoint(renderer, x, y);
						livePred++;
					}
					else {
						empty++;
					}
				}
			}
			SDL_RenderPresent(renderer);
		}
		counter++;
		t2 = clock();
		timer = (float)(t2 - t1) / CLOCKS_PER_SEC;
		if (info.rank == 0) {
			UpdateStatistics(timer, counter, livePrey, livePred, empty, deadPrey, deadPred);
		}
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void MsMPI::RunSimNoDraw(const int COUNT) {
	int counter = 0;
	clock_t t1, t2;
	float timer;
	while (counter < COUNT) {
		t1 = clock();
		deadPrey = 0, deadPred = 0;
		livePrey = 0, livePred = 0, empty = 0;
		UpdateSimulation();
		if (info.rank == 0) {
			for (int x = 0; x < width; x++) {
				for (int y = 0; y < height; y++) {
					if (newGrid[x][y].value > 0) {
						livePrey++;
					} else if (newGrid[x][y].value < 0) {
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
		if (info.rank == 0) {
			UpdateStatistics(timer, counter, livePrey, livePred, empty, deadPrey, deadPred);
		}
	}
}

void MsMPI::UpdateStatistics(float time, int iteration, int lPrey, int lPred, int empty, int dPrey, int dPred) {
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
	fflush(stdout);
}

void MsMPI::UpdateSimulation() {
	// generate COPY cell array
	// Loop COPY to init and zero off values
	if (info.rank == 0) {
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				copyGrid[x][y].value = 0;
				copyGrid[x][y].age = 0;
			}
		}
	} else if (info.rank == 1) {
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				copyGrid[x][y].value = 0;
				copyGrid[x][y].age = 0;
			}
		}
	}

	// corner boundaries
	if (info.rank == 0) {
		newGrid[0][0] = newGrid[width - 2][height - 2];
		newGrid[0][height - 1] = newGrid[width - 2][1];
		newGrid[width - 1][height - 1] = newGrid[1][1];
		newGrid[width - 1][0] = newGrid[1][height - 2];
		MPI_Send(&newGrid[width - 1][height - 1].value, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
		MPI_Send(&newGrid[width - 1][height - 1].age, 1, MPI_INT, 1, 2, MPI_COMM_WORLD);
		MPI_Send(&newGrid[0][height - 1].value, 1, MPI_INT, 1, 3, MPI_COMM_WORLD);
		MPI_Send(&newGrid[0][height - 1].age, 1, MPI_INT, 1, 4, MPI_COMM_WORLD);
	} else if (info.rank == 1) {
		MPI_Recv(&newGrid[width - 1][height - 1].value , 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&newGrid[width - 1][height - 1].age, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, &status);
		MPI_Recv(&newGrid[0][height - 1].value, 1, MPI_INT, 0, 3, MPI_COMM_WORLD, &status);
		MPI_Recv(&newGrid[0][height - 1].age, 1, MPI_INT, 0, 4, MPI_COMM_WORLD, &status);
	}
	// top-bottom boundaries
	for (int x = 1; x < width - 1; x++) {
		if (info.rank == 0) {
			newGrid[x][0] = newGrid[x][height - 2];
			newGrid[x][height - 1] = newGrid[x][1];
			MPI_Send(&newGrid[x][height - 1].value, 1, MPI_INT, 1, x + 5, MPI_COMM_WORLD);
			MPI_Send(&newGrid[x][height - 1].age, 1, MPI_INT, 1, x + width + 5, MPI_COMM_WORLD);
		} else if (info.rank == 1) {
			MPI_Recv(&newGrid[x][height - 1].value, 1, MPI_INT, 0, x + 5, MPI_COMM_WORLD, &status);
			MPI_Recv(&newGrid[x][height - 1].age, 1, MPI_INT, 0, x + width + 5, MPI_COMM_WORLD, &status);
		}
	}
	
	// left-right boundaries
	if (info.rank == 0) {
		for (int y = 1; y < height / 2; y++) {
			newGrid[0][y] = newGrid[width - 2][y];
			newGrid[width - 1][y] = newGrid[1][y];
		}
	} else if (info.rank == 1) {
		for (int y = height / 2; y < height; y++) {
			newGrid[0][y] = newGrid[width - 2][y];
			newGrid[width - 1][y] = newGrid[1][y];
		}
	}
	
	// get the middle split
	if (info.rank == 0) {
		for (int x = 0; x < width; x++) {
			MPI_Send(&newGrid[x][height / 2 - 1].value, 1, MPI_INT, 1, x, MPI_COMM_WORLD);
			MPI_Send(&newGrid[x][height / 2 - 1].age, 1, MPI_INT, 1, x * 2, MPI_COMM_WORLD);
		}
	} else if (info.rank == 1) {
		for (int x = 0; x < width; x++) {
			MPI_Recv(&newGrid[x][height / 2 - 1].value, 1, MPI_INT, 0, x, MPI_COMM_WORLD, &status);
			MPI_Recv(&newGrid[x][height / 2 - 1].age, 1, MPI_INT, 0, x * 2, MPI_COMM_WORLD, &status);
		}
	}

	srand(time(NULL));
	// loop through all cells and determin neighbour count
	
	if (info.rank == 0) {
		for (int x = 1; x < width - 1; x++) {
			for (int y = 1; y < height / 2; y++) {
				int preyCount = 0, preyAge = 0, predCount = 0, predAge = 0;
				for (int i = -1; i < 2; i++) {
					for (int j = -1; j < 2; j++) {
						if (!(i == 0 && j == 0)) {
							if (newGrid[x + i][y + j].value > 0) {
								preyCount++;
								if (newGrid[x + i][y + j].age >= PREY_BREEDING) {
									preyAge++;
								}
							}
							else if (newGrid[x + i][y + j].value < 0) {
								predCount++;
								if (newGrid[x + i][y + j].age >= PRED_BREEDING) {
									predAge++;
								}
							}
						}
					}
				}
				// set current cell to new value depending on rules
				if (newGrid[x][y].value > 0) {
					//manage prey
					if (predCount >= 5 || preyCount == 8 || newGrid[x][y].age > PREY_LIVE) {
						copyGrid[x][y].value = 0;
						copyGrid[x][y].age = 0;
						deadPrey++;
					}
					else {
						copyGrid[x][y].value = newGrid[x][y].value;
						copyGrid[x][y].age = newGrid[x][y].age + 1;
					}
				}
				else if (newGrid[x][y].value < 0) {
					// manage predator
					float random = (float)(rand()) / (float)(RAND_MAX);
					if ((predCount >= 6 && preyCount == 0) || random <= PRED_SUDDEN_DEATH || copyGrid[x][y].age > PRED_LIVE) {
						if (random <= PRED_SUDDEN_DEATH) {
							int z = 0;
						}
						copyGrid[x][y].value = 0;
						copyGrid[x][y].age = 0;
						deadPred++;
					}
					else {
						copyGrid[x][y].value = newGrid[x][y].value;
						copyGrid[x][y].age = newGrid[x][y].age + 1;
					}
				}
				else {
					// manage empty space
					if (preyCount >= NO_BREEDING && preyAge >= NO_AGE && predCount < NO_WITNESSES) {
						copyGrid[x][y].value = 1;
						copyGrid[x][y].age = 1;
					}
					else if (predCount >= NO_BREEDING && predAge >= NO_AGE && preyCount < NO_WITNESSES) {
						copyGrid[x][y].value = -1;
						copyGrid[x][y].age = 1;
					}
					else {
						copyGrid[x][y].value = 0;
						copyGrid[x][y].age = 0;
					}
				}
			}
		}
	}
	else if (info.rank == 1) {
		for (int x = 1; x < width - 1; x++) {
			for (int y = height / 2; y < height - 1; y++) {
				int preyCount = 0, preyAge = 0, predCount = 0, predAge = 0;
				for (int i = -1; i < 2; i++) {
					for (int j = -1; j < 2; j++) {
						if (!(i == 0 && j == 0)) {
							if (newGrid[x + i][y + j].value > 0) {
								preyCount++;
								if (newGrid[x + i][y + j].age >= PREY_BREEDING) {
									preyAge++;
								}
							}
							else if (newGrid[x + i][y + j].value < 0) {
								predCount++;
								if (newGrid[x + i][y + j].age >= PRED_BREEDING) {
									predAge++;
								}
							}
						}
					}
				}
				// set current cell to new value depending on rules
				if (newGrid[x][y].value > 0) {
					//manage prey
					if (predCount >= 5 || preyCount == 8 || newGrid[x][y].age > PREY_LIVE) {
						copyGrid[x][y].value = 0;
						copyGrid[x][y].age = 0;
						deadPrey++;
					}
					else {
						copyGrid[x][y].value = newGrid[x][y].value;
						copyGrid[x][y].age = newGrid[x][y].age + 1;
					}
				}
				else if (newGrid[x][y].value < 0) {
					// manage predator
					float random = (float)(rand()) / (float)(RAND_MAX);
					if ((predCount >= 6 && preyCount == 0) || random <= PRED_SUDDEN_DEATH || copyGrid[x][y].age > PRED_LIVE) {
						if (random <= PRED_SUDDEN_DEATH) {
							int z = 0;
						}
						copyGrid[x][y].value = 0;
						copyGrid[x][y].age = 0;
						deadPred++;
					}
					else {
						copyGrid[x][y].value = newGrid[x][y].value;
						copyGrid[x][y].age = newGrid[x][y].age + 1;
					}
				}
				else {
					// manage empty space
					if (preyCount >= NO_BREEDING && preyAge >= NO_AGE && predCount < NO_WITNESSES) {
						copyGrid[x][y].value = 1;
						copyGrid[x][y].age = 1;
					}
					else if (predCount >= NO_BREEDING && predAge >= NO_AGE && preyCount < NO_WITNESSES) {
						copyGrid[x][y].value = -1;
						copyGrid[x][y].age = 1;
					}
					else {
						copyGrid[x][y].value = 0;
						copyGrid[x][y].age = 0;
					}
				}
			}
		}
	}

	// copy the COPY back to the main array
	if (info.rank == 1) {
		for (int x = 1; x < width - 1; x++) {
			for (int y = height / 2; y < height - 1; y++) {
				newGrid[x][y] = copyGrid[x][y];
				MPI_Send(&newGrid[x][y].value, 1, MPI_INT, 0, y, MPI_COMM_WORLD);
				MPI_Send(&newGrid[x][y].age, 1, MPI_INT, 0, y * x + 1, MPI_COMM_WORLD);
			}
		}
	}
	if (info.rank == 0) {
		for (int x = 1; x < width - 1; x++) {
			for (int y = 1; y < height - 1; y++) {
				if (y < height / 2) {
					newGrid[x][y] = copyGrid[x][y];
				} else {
					MPI_Recv(&newGrid[x][y].value, 1, MPI_INT, 1, y, MPI_COMM_WORLD, &status);
					MPI_Recv(&newGrid[x][y].age, 1, MPI_INT, 1, y * x + 1, MPI_COMM_WORLD, &status);
				}
			}
		}
	}
	MPI_Barrier(MPI_COMM_WORLD);
}

