#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
	int my_rank, npes;
	MPI_Status status;

	// init
	MPI_Init(&argc, (char***)&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &npes);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	struct timeval time_start, time_end;
	float t_temp; // save flaot time
    gettimeofday(&time_start, NULL);

	srand(my_rank);

	// Parameters
    int total_times = 50;
	int test_size = 100;

    // count how many task be assigned to one core
    int test_times = (int)(total_times / npes);
    test_times = total_times % npes ? test_times + 1 : test_times;
    printf("Rank: %d, Size: %d\n", my_rank, test_times);

	int i, j;
	float temp[test_times];
    for (i = 0;i < test_times;++i) {
        temp[i] = 0;
        for (j = 0; j < test_size; j++) {
        	temp[i] += (float)(rand()) / RAND_MAX;
        }
    	temp[i] /= (float)test_size;
    }

	// printf("%d %f\n", my_rank, temp[0]);

	if (my_rank == 0) {
		float results[total_times];

		MPI_Gather(temp, test_times, MPI_FLOAT, results, test_times, MPI_FLOAT, 0, MPI_COMM_WORLD);

		for (i = 0; i < total_times; i++) {
			printf("%d %f\n", i, results[i]);
		}

		t_temp = updateTimer(&time_start, &time_end);
		printf("Cost: %.4f secs.\n", t_temp);
	} else {
		MPI_Gather(temp, test_times, MPI_FLOAT, NULL, 0, MPI_FLOAT, 0, MPI_COMM_WORLD);
	}

	return 0;
}
