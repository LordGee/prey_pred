#pragma once
#include "Simulator.h"

class Serial : public Simulator {
public:
	Serial(int width, int height, int preyPercent, int predPercent, int randomSeed, int threads, int proc)
		: Simulator(width, height, preyPercent, predPercent, randomSeed, threads, proc) {}

	void PopulateGrid() override;
	void DrawSimToScreen(const int COUNT) override;
	void RunSimNoDraw(const int COUNT) override;
	void RunNoDisplay(const int COUNT) override;
	void UpdateStatistics(float time, int iteration, int lPrey, int lPred, int empty, int dPrey, int dPred) override;
	void UpdateSimulation() override;
};
