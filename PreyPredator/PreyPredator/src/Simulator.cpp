#include "Simulator.h"

Simulator::Simulator(int width, int height, int preyPercent, int predPercent, int randomSeed) :
width(width), height(height), seed(randomSeed) {
	prey = (float)preyPercent / 100.0f;
	pred = (float)predPercent / 100.0f;
	newGrid = std::vector<std::vector<Cell>>(width);
	for (int x = 0; x < width; x++) {
		newGrid[x] = std::vector<Cell>(height);
	}
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			newGrid[x][y].value = 0;
			newGrid[x][y].age = 0;
		}
	}
	int z = 0;
}

