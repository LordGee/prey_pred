#pragma once
#include "Cell.h"
#include <vector>

class Simulator {
public:
	std::vector<std::vector<Cell>> newGrid;
	Cell m_Grid;
	int seed = 1978;
	int m_Width, m_Height;
	float m_Prey = 0.5f, m_Pred = 0.25f;

public:
	Simulator(int width, int height);
	 virtual void PopulateGrid() = 0;
};
