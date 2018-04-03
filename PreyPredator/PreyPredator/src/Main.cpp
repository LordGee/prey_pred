#include <cstdlib>
#include <cstdio>
#include "App.h"
#include "mpi.h"

int main(int argc, char *argv[]) {	

	MPI_Init(&argc, &argv);
	InfoMPI* info = new InfoMPI;
	MPI_Comm_size(MPI_COMM_WORLD, &info->numProcs);
	MPI_Comm_rank(MPI_COMM_WORLD, &info->rank);

	std::cout << "\n*** (Main.cpp) Rank " << info->rank << " out of " << info->numProcs << " ***\n" << std::endl;

	App* app = new App(*info);
	delete app;

	delete info;

	MPI_Finalize();
	system("PAUSE");
	
	return 0;
}
