#include "Simulator.h"

Simulator::Simulator(int width, int height, int preyPercent, int predPercent, int randomSeed) :
width(width), height(height), seed(randomSeed) {
	prey = (float)preyPercent / 100.0f;
	pred = (float)predPercent / 100.0f;
	//newGrid = std::vector<std::vector<Cell>>(width);
	//copyGrid = std::vector<std::vector<Cell>>(width);
	newGrid = new Cell*[width];
	copyGrid = new Cell*[width];
	for (int x = 0; x < width; x++) {
		//newGrid[x] = std::vector<Cell>(height);
		//copyGrid[x] = std::vector<Cell>(height);
		newGrid[x] = new Cell[height];
		copyGrid[x] = new Cell[height];
	}
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			newGrid[x][y].value = 0;
			newGrid[x][y].age = 0;
		}
	}
	int z = 0;
}

