#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <mpi.h>

#define N 100000

// utils
void randomVector(float vector[N]);

float updateTimer(struct timeval *time_start, struct timeval *time_end) {
    float timeuse;

    gettimeofday(time_end, NULL);
    timeuse = 1000000*(time_end->tv_sec - time_start->tv_sec)
        + time_end->tv_usec - time_start->tv_usec;
    timeuse /= 1000000;

    *time_start = *time_end;
    return timeuse;
}

int main(int argc, char const *argv[]) {
	int npes, my_rank;
	MPI_Status status;
	float vector[N];

	int times = 100;

	// init
	struct timeval time_start, time_end;
	float temp; // save flaot time
    gettimeofday(&time_start, NULL);

	srand(1340);
    randomVector(vector);

	MPI_Init(&argc, (char***)&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &npes);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	// printf("init msg: %f %f %f\n", vector[1000], vector[1001], vector[1002]);

	temp = updateTimer(&time_start, &time_end);
	if (my_rank == 0) {
		printf("Startup time? use %f secs.\n", temp);
		printf("Send vector %d rounds\n", N);
	}

	// MAIN BLOCK
	if (my_rank == 0) {
		int i;
		for (i = 0; i < (int)(times / 2); i++) {
			MPI_Send(&vector, N, MPI_FLOAT, 1, i % 10, MPI_COMM_WORLD);
			MPI_Recv(&vector, N, MPI_FLOAT, 1, i % 10 + 10, MPI_COMM_WORLD, &status);
            printf("i=%d, rank0 recv\n", i);
			// printf("rank 1 recv msg: %f %f %f\n", vector[1000], vector[1001], vector[1002]);
		}
	} else {
		int i;
		for (i = 0; i < (int)(times / 2); i++) {
			MPI_Recv(&vector, N, MPI_FLOAT, 0, i % 10, MPI_COMM_WORLD, &status);
            printf("i=%d, rank1 recv\n", i);
			// printf("rank 1 recv msg: %f %f %f\n", vector[1000], vector[1001], vector[1002]);
			MPI_Send(&vector, N, MPI_FLOAT, 0, i % 10 + 10, MPI_COMM_WORLD);
		}
	}


	temp = updateTimer(&time_start, &time_end);
	printf("Compute %d times use %f secs.\n", times, temp);

	MPI_Finalize();

	return 0;
}

void randomVector(float vector[N]){
    for (int i = 0; i < N; i++) {
        vector[i] = rand();
    }
}
