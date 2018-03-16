#pragma once

#include "Simulator.h"

struct InfoMPI {
	int rank, noProcs;
};

class MsMPI : public Simulator {
public:
	MsMPI(int width, int height, int preyPercent, int predPercent, int randomSeed, int threads)
		: Simulator(width, height, preyPercent, predPercent, randomSeed, threads) {}

	void PopulateGrid() override;
	void DrawSimToScreen(const int COUNT) override;
	void RunSimNoDraw(const int COUNT) override;
	void UpdateStatistics(float time, int iteration, int lPrey, int lPred, int empty, int dPrey, int dPred) override;
	void UpdateSimulation() override;
};
