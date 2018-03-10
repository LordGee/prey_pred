#include "Simulator.h"

Simulator::Simulator(int width, int height) :
m_Width(width), m_Height(height) {
	m_Grid[width][height];
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			m_Grid[x][y].value = 0;
			m_Grid[x][y].age = 0;
		}
	}
	int z = 0;
}

