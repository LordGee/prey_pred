#pragma once
#include "Serial.h"
#include "OpenMP.h"
#include "Setup.h"

class App {
public:

private:
	Setup* setup;
	Simulator* sim;
	int m_IterationCount;

protected:
	// int WIDTH, HEIGHT;

public:
	App();
	~App();

};
