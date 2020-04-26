#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

int total_times = 50;
int test_size = 100;
int npes = 25; // threads number
// count how many task be assigned to one core
int test_times = 2;

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
	int i, j;
    float temp[test_times];

    for (i = 0;i < test_times;++i) {
        temp[i] = 0;
        for (j = 0; j < test_size; j++) {
        	temp[i] += (float)(rand()) / RAND_MAX;
        }
    	temp[i] /= (float)test_size;

        int k = now * test_times + i;
        if (k < total_times) {
            results[k] = temp[i];
        }
    }

	return NULL;
}
int main(int argc, char const *argv[]) {
	// init
	srand(1340);

	struct timeval time_start, time_end;
	float t_temp; // save flaot time
    gettimeofday(&time_start, NULL);

    test_times = (int)(total_times / npes);
    test_times = total_times % npes ? test_times + 1 : test_times;

	// Parameters
	int i;
	pthread_t task_ids[npes];

	putchar('c');
	for (i = 0; i < npes; i++) {
		// start all threads running and save p_id into task_ids
		pthread_create(&(task_ids[i]), NULL, (void *)count, (void *)&i);
	}
	for (i = 0; i < npes; i++) {
		// waiting all tasks return
		pthread_join(task_ids[i], NULL);
	}

	// for (i = 0; i < total_times; i++) {
	// 	printf("%d %f\n", i, results[i]);
	// }

	t_temp = updateTimer(&time_start, &time_end);
	printf("Cost: %f secs.\n", t_temp);

	return 0;
}
