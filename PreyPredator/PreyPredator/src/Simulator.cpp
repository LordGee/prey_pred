#include "Simulator.h"

Simulator::Simulator(int width, int height, int preyPercent, int predPercent, int randomSeed, int threads, int proc) :
width(width), height(height), seed(randomSeed), numThreads(threads), numProc(proc) {
	prey = (float)preyPercent / 100.0f;
	pred = (float)predPercent / 100.0f;
	mainGrid = std::vector<std::vector<Cell>>(width);
	copyGrid = std::vector<std::vector<Cell>>(width);
	for (int x = 0; x < width; x++) {
		mainGrid[x] = std::vector<Cell>(height);
		copyGrid[x] = std::vector<Cell>(height);
	}
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			mainGrid[x][y].type = 0;
			mainGrid[x][y].age = 0;
		}
	}
}

