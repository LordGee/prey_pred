#include "App.h"
#include "mpi.h"
#include <cstdlib>

App::App(int id, int proc) {
	InfoMPI info;
	info.rank = id;
	info.noProcs = proc;
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
		switch (setup->PROJECT_TYPE) {
		case 0:
			sim = new Serial(setup->WIDTH, setup->HEIGHT, setup->PREY_PERCENT, setup->PRED_PERCENT, setup->RANDOM_SEED, setup->THREADS);
			break;
		case 1:
			sim = new OpenMP(setup->WIDTH, setup->HEIGHT, setup->PREY_PERCENT, setup->PRED_PERCENT, setup->RANDOM_SEED, setup->THREADS);
			break;
		case 2:
			sim = new MsMPI(setup->WIDTH, setup->HEIGHT, setup->PREY_PERCENT, setup->PRED_PERCENT, setup->RANDOM_SEED, setup->THREADS);
			break;
		}
	}
	if (info.noProcs > 1) {
		MPI_Barrier(MPI_COMM_WORLD);
	}
	

	sim->PopulateGrid();

	if (setup->DRAW_GRAPHICS == 1) {
		sim->DrawSimToScreen(setup->ITERATIONS);
	} else {
		sim->RunSimNoDraw(setup->ITERATIONS);
	}

}

App::~App() {
	delete setup;
	delete sim;
}
