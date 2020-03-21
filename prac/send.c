#include <stdio.h>
#include <mpi.h>

int main(int argc, char const *argv[]) {
	int npes, my_rank;
	int a[10], b[10];

	MPI_Init(&argc, (char***)&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &npes);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if (my_rank == 0) {
		a[0] = 0, b[0] = 1;
		MPI_Send(a, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
	} else {
		MPI_Status status;
		a[0] = 2, b[0] = 3;
		MPI_Recv(a, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
	}

	printf("From processor %d / %d, a=%d b=%d\n",
		my_rank, npes, a[0], b[0]);

	MPI_Finalize();

	return 0;
}
