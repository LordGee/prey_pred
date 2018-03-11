#include "Serial.h"
#include <cstdlib>


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
	
}
