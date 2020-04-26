#include <stdio.h>
#include <stdlib.h>
// #include <time.h>
#include <sys/time.h>
#include <mpi.h>

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
	int my_rank;
	MPI_Status status;

	// init
	struct timeval time_start, time_end;
	float t_temp; // save flaot time
    gettimeofday(&time_start, NULL);

	MPI_Init(&argc, (char***)&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	srand(my_rank);

	// Parameters
	int test_times = 50;
	int test_size = 100;

	int i;
	float temp = 0;
	for (i = 0; i < test_size; i++) {
		temp += (float)(rand()) / RAND_MAX;
	}
	temp /= (float)test_size;

	if (my_rank == 0) {
		float results[test_times];

		MPI_Gather(&temp, 1, MPI_FLOAT, results, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

		for (i = 0; i < test_times; i++) {
			printf("%d %f\n", i, results[i]);
		}

		t_temp = updateTimer(&time_start, &time_end);
		printf("Cost: %.4f secs.\n", t_temp);
	} else {
		MPI_Gather(&temp, 1, MPI_FLOAT, NULL, 0, MPI_FLOAT, 0, MPI_COMM_WORLD);
	}

	return 0;
}
