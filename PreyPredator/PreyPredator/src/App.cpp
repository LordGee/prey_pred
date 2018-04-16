#include "App.h"
#include <cstdlib>
#include "FileWriter.h"

// Constructor
App::App(InfoMPI &info) {
	MPI_Barrier(MPI_COMM_WORLD);
	// Only master process should manage the setup of the simulation
	if (info.procRank == 0) {
		m_Setup = new Setup;
		if (info.numProcs > 1) {
			m_Setup->isMPI = true;
			m_Setup->projectType = 2;
			m_Setup->processes = info.numProcs;
		} else {
			m_Setup->isMPI = false;
		}
		// Holds here until all option have been confirmed
		m_Setup->DisplaySelection();
	}
	// If MPI processes are greater then 1 distribute the options selected to all processes
	if (info.numProcs > 1) {
		MPI_Status status;
		if (info.procRank != 0) {
			m_Setup = new Setup;
		}
		if (info.procRank == 0) {
			for (int p = 1; p < info.numProcs; p++) {
				MPI_Send(&m_Setup->width, 1, MPI_INT, p, 1, MPI_COMM_WORLD);
				MPI_Send(&m_Setup->height, 1, MPI_INT, p, 2, MPI_COMM_WORLD);
				MPI_Send(&m_Setup->preyPercentage, 1, MPI_INT, p, 3, MPI_COMM_WORLD);
				MPI_Send(&m_Setup->PredPercentage, 1, MPI_INT, p, 4, MPI_COMM_WORLD);
				MPI_Send(&m_Setup->randomSeed, 1, MPI_INT, p, 5, MPI_COMM_WORLD);
				MPI_Send(&m_Setup->threads, 1, MPI_INT, p, 6, MPI_COMM_WORLD);
				MPI_Send(&m_Setup->processes, 1, MPI_INT, p, 7, MPI_COMM_WORLD);
				MPI_Send(&m_Setup->projectType, 1, MPI_INT, p, 8, MPI_COMM_WORLD);
				MPI_Send(&m_Setup->display, 1, MPI_INT, p, 9, MPI_COMM_WORLD);
				MPI_Send(&m_Setup->iterations, 1, MPI_INT, p, 10, MPI_COMM_WORLD);
			}
		}
		if (info.procRank != 0) {
			MPI_Recv(&m_Setup->width, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
			MPI_Recv(&m_Setup->height, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, &status);
			MPI_Recv(&m_Setup->preyPercentage, 1, MPI_INT, 0, 3, MPI_COMM_WORLD, &status);
			MPI_Recv(&m_Setup->PredPercentage, 1, MPI_INT, 0, 4, MPI_COMM_WORLD, &status);
			MPI_Recv(&m_Setup->randomSeed, 1, MPI_INT, 0, 5, MPI_COMM_WORLD, &status);
			MPI_Recv(&m_Setup->threads, 1, MPI_INT, 0, 6, MPI_COMM_WORLD, &status);
			MPI_Recv(&m_Setup->processes, 1, MPI_INT, 0, 7, MPI_COMM_WORLD, &status);
			MPI_Recv(&m_Setup->projectType, 1, MPI_INT, 0, 8, MPI_COMM_WORLD, &status);
			MPI_Recv(&m_Setup->display, 1, MPI_INT, 0, 9, MPI_COMM_WORLD, &status);
			MPI_Recv(&m_Setup->iterations, 1, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
		}
	}
	// Due to load issue (MASTER process doing more) included barrier here
	MPI_Barrier(MPI_COMM_WORLD);
	// Depending on project type determines which type of simulator is running
	switch (m_Setup->projectType) {
	case 0:
		m_Sim = new Serial(m_Setup->width, m_Setup->height, m_Setup->preyPercentage, m_Setup->PredPercentage, m_Setup->randomSeed, m_Setup->threads, m_Setup->processes);
		break;
	case 1:
		m_Sim = new OpenMP(m_Setup->width, m_Setup->height, m_Setup->preyPercentage, m_Setup->PredPercentage, m_Setup->randomSeed, m_Setup->threads, m_Setup->processes);
		break;
	case 2:
		if (m_Setup->height % info.numProcs != 0) {
			m_Setup->height = abs(m_Setup->height / info.numProcs) * info.numProcs;
		}
		m_Sim = new MsMPI(m_Setup->width, m_Setup->height, m_Setup->preyPercentage, m_Setup->PredPercentage, m_Setup->randomSeed, m_Setup->threads, m_Setup->processes);
		m_Sim->info.numProcs = info.numProcs;
		m_Sim->info.procRank = info.procRank;
		break;
	case 3:
		if (m_Setup->height % info.numProcs != 0) {
			m_Setup->height = abs(m_Setup->height / info.numProcs) * info.numProcs;
		}
		m_Sim = new Hybrid(m_Setup->width, m_Setup->height, m_Setup->preyPercentage, m_Setup->PredPercentage, m_Setup->randomSeed, m_Setup->threads, m_Setup->processes);
		m_Sim->info.numProcs = info.numProcs;
		m_Sim->info.procRank = info.procRank;
		break;
	}

	MPI_Barrier(MPI_COMM_WORLD);
	// Populates the initial grid layout
	m_Sim->PopulateGrid();
	MPI_Barrier(MPI_COMM_WORLD);

	// Executes the entry point to the simulator
	if (m_Setup->display == 1) {
		m_Sim->DrawSimToScreen(m_Setup->iterations);
	} else if (m_Setup->display == 2) {
		m_Sim->RunSimNoDraw(m_Setup->iterations);
	} else {
		m_Sim->RunNoDisplay(m_Setup->iterations);
		if (info.procRank == 0) {
			FileWiter(m_Sim->timerLog);
		}
	}
	MPI_Barrier(MPI_COMM_WORLD);
}

// Deconstructor
App::~App() {
	delete m_Setup;
	delete m_Sim;
}
