#pragma once

#include "Simulator.h"
#include "mpi.h"

class MsMPI : public Simulator {
public:
	int contributionX, contributionY;

	MsMPI(int width, int height, int preyPercent, int predPercent, int randomSeed, int threads, int proc)
		: Simulator(width, height, preyPercent, predPercent, randomSeed, threads, proc) {}

	void PopulateGrid() override;
	void DrawSimToScreen(const int COUNT) override;
	void RunSimNoDraw(const int COUNT) override;
	void UpdateStatistics(float time, int iteration, int lPrey, int lPred, int empty, int dPrey, int dPred) override;
	void UpdateSimulation() override;

	int GetProcessorValue(int value) {
		int temp = abs(value / info.noProcs);
		if (temp * info.noProcs != value) {
			printf("Remainder");
		}
		return temp;
	}

};
