#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <mpi.h>

#define N 600000

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

	int times = 10;

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

    if (my_rank == 1) {
        temp = updateTimer(&time_start, &time_end);
        printf("Startup time use %f secs.\n", temp);
    }

    int size;
    for (size = 100000; size <= 600000; size += 100000) {
        temp = updateTimer(&time_start, &time_end);
    	if (my_rank == 1) {
            printf("====================\n");
    		printf("Send size %d vector %d times\n", size, times);

    	}
    	// MAIN BLOCK
    	if (my_rank == 0) {
    		int i;
    		for (i = 0; i < times; i++) {
    			MPI_Send(&vector, size, MPI_FLOAT, 1, 0, MPI_COMM_WORLD);
    			MPI_Recv(&vector, size, MPI_FLOAT, 1, 1, MPI_COMM_WORLD, &status);
    		}
    	} else {
    		int i;
    		for (i = 0; i < times; i++) {
    			MPI_Recv(&vector, size, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, &status);
    			MPI_Send(&vector, size, MPI_FLOAT, 0, 1, MPI_COMM_WORLD);
    		}
    	}


    	if (my_rank == 1) {
            temp = updateTimer(&time_start, &time_end);
        	printf("Length: %d Compute %d times\nTota: %f secs \t Avg: %f secs.\n",
                size, times, temp, temp / times);
        }
    }

	MPI_Finalize();

	return 0;
}

void randomVector(float vector[N]){
    for (int i = 0; i < N; i++) {
        vector[i] = rand();
    }
}
