#include "Serial.h"
#include <cstdlib>


void Serial::PopulateGrid() {
	srand(seed);
	for (int x = 0; x < m_Width; x++) {
		for (int y = 0; y < m_Height; y++) {
			float random = (float)(rand()) / (float)(RAND_MAX);
			if (random < m_Prey) {
				newGrid[x][y].value = 1;
				newGrid[x][y].age = 1;
			}
			else if (random < m_Prey + m_Pred) {
				newGrid[x][y].value = -1;
				newGrid[x][y].age = 1;
			}
			else {
				newGrid[x][y].value = 0;
				newGrid[x][y].age = 0;
			}
		}
	}
	int z = 0;
}
