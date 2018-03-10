#pragma once
#include "Simulator.h"

class Serial : public Simulator {
public:

public:

	Serial(int width, int height)
		: Simulator(width, height) {}

	void PopulateGrid() override;
};
