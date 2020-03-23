#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

	int token = 0;
	// MAIN BLOCK
	if (my_rank == 0) { // start point
		token = 1;
		printf("From processor: %d out of %d\n", my_rank, npes);

		int i;
		for (i = 0; i < 100000; i++) { } // delay to wait buffer

		MPI_Send(&token, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Recv(&token, 1, MPI_INT, (my_rank - 1 + npes) % npes, 0, MPI_COMM_WORLD, &status);
	} else {
		MPI_Recv(&token, 1, MPI_INT, (my_rank - 1 + npes) % npes, 0, MPI_COMM_WORLD, &status);

		printf("From processor: %d out of %d\n", my_rank, npes);

		int i;
		for (i = 0; i < 100000; i++) { } // delay to wait buffer

		MPI_Send(&token, 1, MPI_INT, (my_rank + 1 + npes) % npes, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();

	return 0;
}
