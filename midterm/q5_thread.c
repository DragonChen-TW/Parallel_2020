#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

int test_times = 50;
int test_size = 100;

float results[50];

float updateTimer(struct timeval *time_start, struct timeval *time_end) {
    float timeuse;

    gettimeofday(time_end, NULL);
    timeuse = 1000000*(time_end->tv_sec - time_start->tv_sec)
        + time_end->tv_usec - time_start->tv_usec;
    timeuse /= 1000000;

    *time_start = *time_end;
    return timeuse;
}
void *count(void *arg) {
	int now = *(int*)arg;
	int i;
	float temp = 0;

	for (i = 0; i < test_size; i++) {
		temp += (float)(rand()) / RAND_MAX;
	}
	temp /= (float)test_size;

	printf("%f\n", temp);

	results[now] = temp;
	return NULL;
}
int main(int argc, char const *argv[]) {
	// init
	srand(1340);

	struct timeval time_start, time_end;
	float t_temp; // save flaot time
    gettimeofday(&time_start, NULL);

	// Parameters
	int i;
	pthread_t task_ids[test_times];

	putchar('c');
	for (i = 0; i < test_times; i++) {
		// start all threads running and save p_id into task_ids
		pthread_create(&(task_ids[i]), NULL, (void *)count, (void *)&i);
	}
	for (i = 0; i < test_times; i++) {
		// waiting all tasks return
		pthread_join(task_ids[i], NULL);
	}

	// for (i = 0; i < test_times; i++) {
	// 	printf("%d %f\n", i, results[i]);
	// }

	t_temp = updateTimer(&time_start, &time_end);
	printf("Cost: %f secs.\n", t_temp);

	return 0;
}
