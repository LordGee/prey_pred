#pragma once
#include "Cell.h"
#include <vector>

class Simulator {
public:
	std::vector<std::vector<Cell>> newGrid;
	int width, height, seed;
	float prey, pred;

public:
	Simulator(int width, int height, int preyPercent, int predPercent, int randomSeed);
	virtual void PopulateGrid() = 0;
	virtual void DrawSimToScreen(const int COUNT) = 0;
	virtual void RunSimNoDraw(const int COUNT) = 0;
	virtual void UpdateStatistics(float time, int iteration, int lPrey, int lPred, int empty) = 0;
	virtual void UpdateSimulation() = 0;
};
