#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <mpi.h>

int main(int argc, char const *argv[]) {
	int npes, my_rank;
	MPI_Status status;

	// init
	struct timeval time_start, time_end;
	float temp; // save flaot time
    gettimeofday(&time_start, NULL);

	MPI_Init(&argc, (char***)&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &npes);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	// MAIN BLOCK
	

	MPI_Finalize();

	return 0;
}
