#pragma once
#include "Simulator.h"

class Serial : public Simulator {
public:

public:

	Serial(int width, int height, int preyPercent, int predPercent, int randomSeed)
		: Simulator(width, height, preyPercent, predPercent, randomSeed) {}

	void PopulateGrid() override;
	void DrawSimToScreen(int count) override;
};
