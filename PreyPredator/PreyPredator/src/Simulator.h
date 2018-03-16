#pragma once
#include "Cell.h"
#include "SDL.h"
#include <vector>

static int livePrey, livePred, empty;
static int deadPrey, deadPred;

class Simulator {
public:
	std::vector<std::vector<Cell>> newGrid;
	std::vector<std::vector<Cell>> copyGrid;
	
	int width, height, seed, numThreads;
	float prey, pred;

	const int PREY_BREEDING = 2;
	const int PRED_BREEDING = 3;

	const int NO_BREEDING = 4;
	const int NO_AGE = 3;
	const int NO_WITNESSES = 4;

	const int PREY_LIVE = 10;
	const int PRED_LIVE = 20;

	const float PRED_SUDDEN_DEATH = 0.031f;

public:
	Simulator(int width, int height, int preyPercent, int predPercent, int randomSeed, int threads);
	virtual void PopulateGrid() = 0;
	virtual void DrawSimToScreen(const int COUNT) = 0;
	virtual void RunSimNoDraw(const int COUNT) = 0;
	virtual void UpdateStatistics(float time, int iteration, int lPrey, int lPred, int empty, int dPrey, int dPred) = 0;
	virtual void UpdateSimulation() = 0;
};
