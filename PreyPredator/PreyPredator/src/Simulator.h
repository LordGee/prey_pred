#pragma once
#include "Cell.h"
#include "SDL.h"
#include <vector>
#include <ostream>
#include <iostream>
#include "mpi.h"

// Statistic Variables
static int livePrey, livePred, empty;
static int deadPrey, deadPred;

// Structure to manage MPI information
struct InfoMPI {
	int procRank, numProcs;

	InfoMPI() {
		procRank = -1;
		numProcs = -1;
	}
};

class Simulator {
public:
	std::vector<std::vector<Cell>> mainGrid;
	std::vector<std::vector<Cell>> copyGrid;
	
	int width, height, seed, numThreads, numProc;
	float prey, pred;
	bool noDraw;

	std::vector<float> timerLog;

	const int PREY_BREEDING = 2;
	const int PRED_BREEDING = 3;

	const int NUM_BREEDING = 4;
	const int NUM_OF_AGE = 3;
	const int NUM_OF_WITNESSES = 4;

	const int PREY_LIVE = 10;
	const int PRED_LIVE = 20;

	const float PRED_SUDDEN_DEATH = 0.031f;

	const int MASTER = 0;

	MPI_Status status;
	MPI_Request request;
	InfoMPI info;

public:
	Simulator(int width, int height, int preyPercent, int predPercent, int randomSeed, int threads, int proc);
	virtual void PopulateGrid() = 0;
	virtual void DrawSimToScreen(const int COUNT) = 0;
	virtual void RunSimNoDraw(const int COUNT) = 0;
	virtual void RunNoDisplay(const int COUNT) = 0;
	virtual void UpdateStatistics(float time, int iteration, int lPrey, int lPred, int empty, int dPrey, int dPred) = 0;
	virtual void UpdateSimulation() = 0;
};

