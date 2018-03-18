#include "App.h"
#include <cstdlib>

App::App(InfoMPI &info) {

	std::cout << "\n*** (App.cpp) Rank " << info.rank << " out of " << info.noProcs << " ***\n" << std::endl;
	MPI_Barrier(MPI_COMM_WORLD);
	if (info.rank == 0) {
		setup = new Setup;
		if (info.noProcs > 1) {
			setup->isMPI = true;
			setup->PROJECT_TYPE = 2;
			setup->PROCESSORS = info.noProcs;

		} else {
			setup->isMPI = false;
		}
		setup->DisplaySelection();
	}
	if (info.noProcs > 1) {
		MPI_Status status;
		if (info.rank != 0) {
			setup = new Setup;
		}
		if (info.rank == 0) {
			for (int p = 1; p < info.noProcs; p++) {
				MPI_Send(&setup->WIDTH, 1, MPI_INT, p, 1, MPI_COMM_WORLD);
				MPI_Send(&setup->HEIGHT, 1, MPI_INT, p, 2, MPI_COMM_WORLD);
				MPI_Send(&setup->PREY_PERCENT, 1, MPI_INT, p, 3, MPI_COMM_WORLD);
				MPI_Send(&setup->PRED_PERCENT, 1, MPI_INT, p, 4, MPI_COMM_WORLD);
				MPI_Send(&setup->RANDOM_SEED, 1, MPI_INT, p, 5, MPI_COMM_WORLD);
				MPI_Send(&setup->THREADS, 1, MPI_INT, p, 6, MPI_COMM_WORLD);
				MPI_Send(&setup->PROCESSORS, 1, MPI_INT, p, 7, MPI_COMM_WORLD);
				MPI_Send(&setup->PROJECT_TYPE, 1, MPI_INT, p, 8, MPI_COMM_WORLD);
			}
		}
		if (info.rank != 0) {
			MPI_Recv(&setup->WIDTH, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
			MPI_Recv(&setup->HEIGHT, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, &status);
			MPI_Recv(&setup->PREY_PERCENT, 1, MPI_INT, 0, 3, MPI_COMM_WORLD, &status);
			MPI_Recv(&setup->PRED_PERCENT, 1, MPI_INT, 0, 4, MPI_COMM_WORLD, &status);
			MPI_Recv(&setup->RANDOM_SEED, 1, MPI_INT, 0, 5, MPI_COMM_WORLD, &status);
			MPI_Recv(&setup->THREADS, 1, MPI_INT, 0, 6, MPI_COMM_WORLD, &status);
			MPI_Recv(&setup->PROCESSORS, 1, MPI_INT, 0, 7, MPI_COMM_WORLD, &status);
			MPI_Recv(&setup->PROJECT_TYPE, 1, MPI_INT, 0, 8, MPI_COMM_WORLD, &status);
		}
		
	}
	MPI_Barrier(MPI_COMM_WORLD);
	switch (setup->PROJECT_TYPE) {
	case 0:
		sim = new Serial(setup->WIDTH, setup->HEIGHT, setup->PREY_PERCENT, setup->PRED_PERCENT, setup->RANDOM_SEED, setup->THREADS, setup->PROCESSORS);
		break;
	case 1:
		sim = new OpenMP(setup->WIDTH, setup->HEIGHT, setup->PREY_PERCENT, setup->PRED_PERCENT, setup->RANDOM_SEED, setup->THREADS, setup->PROCESSORS);
		break;
	case 2:
		sim = new MsMPI(setup->WIDTH, setup->HEIGHT, setup->PREY_PERCENT, setup->PRED_PERCENT, setup->RANDOM_SEED, setup->THREADS, setup->PROCESSORS);
		sim->info.noProcs = setup->PROCESSORS;
		sim->info.rank = info.rank;
		break;
	}
	
	
	MPI_Barrier(MPI_COMM_WORLD);
	sim->PopulateGrid();
	MPI_Barrier(MPI_COMM_WORLD);
	if (setup->DRAW_GRAPHICS == 1) {
		sim->DrawSimToScreen(setup->ITERATIONS);
	} else {
		sim->RunSimNoDraw(setup->ITERATIONS);
	}
	MPI_Barrier(MPI_COMM_WORLD);
}

App::~App() {
	delete setup;
	delete sim;
}
