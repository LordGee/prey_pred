#include <cstdlib>
#include <cstdio>
#include "App.h"
#include "mpi.h"

int main(int argc, char *argv[]) {	

	// Setting up initial MPI
	MPI_Init(&argc, &argv);
	InfoMPI* info = new InfoMPI;
	MPI_Comm_size(MPI_COMM_WORLD, &info->numProcs);
	MPI_Comm_rank(MPI_COMM_WORLD, &info->procRank);

	std::cout << "\n*** MPI Rank " << info->procRank << " out of " << info->numProcs << " ***\n" << std::endl;

	// Creates instance of the application setup features
	App* app = new App(*info);

	delete app;
	delete info;

	MPI_Finalize();
	system("PAUSE");
	
	return 0;
}
