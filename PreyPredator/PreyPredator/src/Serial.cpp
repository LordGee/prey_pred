#include "Serial.h"
#include <cstdlib>


void Serial::PopulateGrid() {
	srand(seed);
	for (int x = 0; x < m_Width; x++) {
		for (int y = 0; y < m_Height; y++) {
			const float random = rand() % 100 / 1000;
			if (random < m_Prey) {
				m_Grid[x][y].value = 1;
				m_Grid[x][y].age = 1;
			}
			else if (random < m_Prey + m_Pred) {
				m_Grid[x][y].value = -1;
				m_Grid[x][y].age = 1;
			}
			else {
				m_Grid[x][y].value = 0;
				m_Grid[x][y].age = 0;
			}
		}
	}
}
