#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

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
	// init
	srand(1340);

	struct timeval time_start, time_end;
	float t_temp; // save flaot time
    gettimeofday(&time_start, NULL);

	// Parameters
	int test_times = 50;
	int test_size = 100;

	int i, j;
	float temp[test_times];
	for (i = 0; i < test_times; i++) {
		temp[i] = 0;
		for (j = 0; j < test_size; j++) {
			temp[i] += (float)(rand()) / RAND_MAX;
		}
		temp[i] /= (float)test_size;
	}

	// Show Results
	for (i = 0; i < test_times; i++) {
		printf("%d %f\n", i, temp[i]);
	}

	t_temp = updateTimer(&time_start, &time_end);
	printf("Cost: %f secs.\n", t_temp);

	return 0;
}
