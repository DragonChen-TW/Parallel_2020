#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char const *argv[]) {
	int my_rank, npes;
	MPI_Status status;

	// init
	MPI_Init(&argc, (char***)&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &npes);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	srand(my_rank);

	// Parameters
	int total_test_times = 50;
	int test_size = 100;
	int test_times = total_test_times % npes ? (int)(total_times / npes) + 1 : (int)(total_times / npes);
	printf("size: %d\n", test_times);

	// int i, j;
	// float temp[test_times];
	// for (i = 0; i < test_times; i++) {
	// 	temp[i] = 0;
	// 	for (j = 0; j < test_size; j++) {
	// 		temp[i] += (float)(rand()) / RAND_MAX;
	// 	}
	// 	temp[i] /= (float)test_size;
	// }
	int i, j;
	int temp[test_times];
	for (i = 0;i < test_times;++i) {
		temp[i] = my_rank * my_rank;
	}

	// printf("%d %f\n", my_rank, temp[0]);

	if (my_rank == 0) {
		int results[total_test_times];

		MPI_Gather(temp, test_times, MPI_INT, results, test_times, MPI_INT, 0, MPI_COMM_WORLD);

		for (i = 0; i < total_test_times; i++) {
			printf("%d %d\n", i, results[i]);
		}
	} else {
		MPI_Gather(temp, test_times, MPI_INT, NULL, 0, MPI_INT, 0, MPI_COMM_WORLD);
	}

	return 0;
}
