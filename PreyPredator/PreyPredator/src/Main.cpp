#include <cstdlib>
#include <cstdio>
#include "App.h"
#include <string>

int main(int argc, char *argv[]) {
	// InfoMPI info;
	
	MPI_Init(&argc, &argv);
	/*
	int rankID, proc;
	MPI_Comm_size(MPI_COMM_WORLD, &proc);
	MPI_Comm_rank(MPI_COMM_WORLD, &rankID);
	printf("\nRank %d - %c \n", &argc, &argv);
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
	*/
	
	int rankID = 0, proc = 1;
	MPI_Comm_size(MPI_COMM_WORLD, &proc);
	MPI_Comm_rank(MPI_COMM_WORLD, &rankID);

	


	App* app = new App(rankID, proc);
	delete app;
	
	// MPI_Barrier(MPI_COMM_WORLD);
	// You also need this when your program is about to exit
	
	system("PAUSE");
	MPI_Finalize();
	return 0;
}
