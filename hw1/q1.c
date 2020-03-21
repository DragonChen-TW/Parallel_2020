#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define N 100000

// utils
void randomVector(float vector[N]);

// compute
float count1way(float v1[N], float v2[N]);
float count2way(float v1[N], float v2[N]);
float count4way(float v1[N], float v2[N]);
float count8way(float v1[N], float v2[N]);
float count16way(float v1[N], float v2[N]);
// float count32way(float v1[N], float v2[N]);

float updateTimer(struct timeval *time_start, struct timeval *time_end) {
    float timeuse;

    gettimeofday(time_end, NULL);
    timeuse = 1000000*(time_end->tv_sec - time_start->tv_sec)
        + time_end->tv_usec - time_start->tv_usec;
    timeuse /= 1000000;

    *time_start = *time_end;
    return timeuse;
}

int main(void) {
    float v1[N], v2[N];
    int times = 1;

    srand(1340);
    randomVector(v1);
    randomVector(v2);

    printf("Start computing...\n");
    printf("(%d lenght vector, Each way compute %d times to get avg time.)\n",
        N, times);

    struct timeval time_start, time_end;
    gettimeofday(&time_start, NULL);

    // MAIN BLOCK
    float temp;
    temp = 0;
    for (int i = 0; i < times; i++) {
        count1way(v1, v2);
        temp += updateTimer(&time_start, &time_end);
    }
    printf("1-way Using %f secs.\n", temp / times);

    temp = 0;
    for (int i = 0; i < times; i++) {
        count2way(v1, v2);
        temp += updateTimer(&time_start, &time_end);
    }
    printf("2-way Using %f secs.\n", temp / times);

    temp = 0;
    for (int i = 0; i < times; i++) {
        count4way(v1, v2);
        temp += updateTimer(&time_start, &time_end);
    }
    printf("4-way Using %f secs.\n", temp / times);

    temp = 0;
    for (int i = 0; i < times; i++) {
        count8way(v1, v2);
        temp += updateTimer(&time_start, &time_end);
    }
    printf("8-way Using %f secs.\n", temp / times);

    temp = 0;
    for (int i = 0; i < times; i++) {
        count16way(v1, v2);
        temp += updateTimer(&time_start, &time_end);
    }
    printf("16way Using %f secs.\n", temp / times);

    // temp = 0;
    // for (int i = 0; i < times; i++) {
    //     count32way(v1, v2);
    //     temp += updateTimer(&time_start, &time_end);
    // }
    // printf("8-way Using %f secs.\n", temp / times);

    return 0;
}

void randomVector(float vector[N]){
    for (int i = 0; i < N; i++) {
        vector[i] = rand();
    }
}

float count1way(float v1[N], float v2[N]){
    float ans = 0;
    for (int i = 0; i < N; i++) {
        ans += v1[i] * v2[i];
    }
    return ans;
}
float count2way(float v1[N], float v2[N]){
    float ans = 0;
    for (int i = 0; i < N; i += 2) {
        ans += v1[i] * v2[i];
        ans += v1[i + 1] * v2[i + 1];
    }
    return ans;
}
float count4way(float v1[N], float v2[N]){
    float ans = 0;
    for (int i = 0; i < N; i += 4) {
        ans += v1[i] * v2[i];
        ans += v1[i + 1] * v2[i + 1];
        ans += v1[i + 2] * v2[i + 2];
        ans += v1[i + 3] * v2[i + 3];
    }
    return ans;
}
float count8way(float v1[N], float v2[N]){
    float ans = 0;
    for (int i = 0; i < N; i += 8) {
        ans += v1[i] * v2[i];
        ans += v1[i + 1] * v2[i + 1];
        ans += v1[i + 2] * v2[i + 2];
        ans += v1[i + 3] * v2[i + 3];
        ans += v1[i + 4] * v2[i + 4];
        ans += v1[i + 5] * v2[i + 5];
        ans += v1[i + 6] * v2[i + 6];
        ans += v1[i + 7] * v2[i + 7];
    }
    return ans;
}
float count16way(float v1[N], float v2[N]){
    float ans = 0;
    for (int i = 0; i < N; i += 16) {
        ans += v1[i] * v2[i];
        ans += v1[i + 1] * v2[i + 1];
        ans += v1[i + 2] * v2[i + 2];
        ans += v1[i + 3] * v2[i + 3];
        ans += v1[i + 4] * v2[i + 4];
        ans += v1[i + 5] * v2[i + 5];
        ans += v1[i + 6] * v2[i + 6];
        ans += v1[i + 7] * v2[i + 7];
        ans += v1[i + 8] * v2[i + 8];
        ans += v1[i + 9] * v2[i + 9];
        ans += v1[i + 10] * v2[i + 10];
        ans += v1[i + 11] * v2[i + 11];
        ans += v1[i + 12] * v2[i + 12];
        ans += v1[i + 13] * v2[i + 13];
        ans += v1[i + 14] * v2[i + 14];
        ans += v1[i + 15] * v2[i + 15];
    }
    return ans;
}
