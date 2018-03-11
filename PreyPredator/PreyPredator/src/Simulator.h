#pragma once
#include "Cell.h"
#include <vector>

class Simulator {
public:
	std::vector<std::vector<Cell>> newGrid;
	int width, height, seed, count;
	float prey, pred;

public:
	Simulator(int width, int height, int preyPercent, int predPercent, int randomSeed);
	virtual void PopulateGrid() = 0;
	virtual void DrawSimToScreen(int count) = 0;

};
