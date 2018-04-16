#pragma once
#include "Serial.h"
#include "OpenMP.h"
#include "msMPI.h"
#include "Hybrid.h"
#include "Setup.h"

class App {

private:
	Setup* m_Setup; // Instance of setup information
	Simulator* m_Sim; // Instance of the Simulator
	int m_IterationCount;

public:
	App(InfoMPI &info);
	~App();

};
