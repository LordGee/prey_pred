#include <cstdlib>
#include <cstdio>
#include "App.h"
#include "mpi.h"
#include <string>



int main(int argc, char* argv[]) {
	InfoMPI info;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &info.noProcs);
	MPI_Comm_rank(MPI_COMM_WORLD, &info.rank);
	MPI_Barrier(MPI_COMM_WORLD);
	
	if (info.noProcs <= 1) { MPI_Finalize(); }

	App* app = new App(info.rank, info.noProcs);

	if (info.noProcs > 1) {	MPI_Finalize(); }
	system("PAUSE");
	delete app;

	return 1;
}
