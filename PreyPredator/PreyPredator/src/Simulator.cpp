#include "Simulator.h"

Simulator::Simulator(int width, int height) :
m_Width(width), m_Height(height) {	
	newGrid = std::vector<std::vector<Cell>>(m_Width);
	for (int x = 0; x < m_Width; x++) {
		newGrid[x] = std::vector<Cell>(m_Height);
	}
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			newGrid[x][y].value = 0;
			newGrid[x][y].age = 0;
		}
	}
	int z = 0;
}

