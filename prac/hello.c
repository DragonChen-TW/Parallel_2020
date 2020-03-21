#include <stdio.h>
#include <mpi.h>

int main(int argc, char const *argv[]) {
	int npes, myrank;

	MPI_Init(&argc, (char***)&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &npes);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	printf("From process: %d out of %d, Hello World!\n", myrank, npes);

	return 0;
}
