#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define N 512

// utils
void randomMatrix(float matrix[N][N]);

// compute
void count1way(float m1[N][N], float m2[N][N]);
void count2way(float m1[N][N], float m2[N][N]);
void count4way(float m1[N][N], float m2[N][N]);
void count8way(float m1[N][N], float m2[N][N]);
void count16way(float m1[N][N], float m2[N][N]);
void count32way(float m1[N][N], float m2[N][N]);

float updateTimer(struct timeval *time_start, struct timeval *time_end) {
    float timeuse;

    gettimeofday(time_end, NULL);
    timeuse = 1000000*(time_end->tv_sec-time_start->tv_sec)+time_end->tv_usec-time_start->tv_usec;
    timeuse /= 1000000;

    *time_start = *time_end;
    return timeuse;
}

int main(void) {
    float m1[N][N], m2[N][N];

    srand(1340);
    randomMatrix(m1);
    randomMatrix(m2);

    int times = 5;
    int operations = N * N * N;
    printf("Start computing...\n");
    printf("(%d lenght matrix, Each way compute %d times to get avg time.)\n", N, times);

    struct timeval time_start, time_end;
    gettimeofday(&time_start, NULL);

    // MAIN BLOCK
    float temp;
    temp = 0;
    for (int i = 0; i < times; i++) {
        count1way(m1, m2);
        temp += updateTimer(&time_start, &time_end);
    }
    printf("1-way Using %f secs.\t(M)FLOPS: %.2f\n",
        temp / times, operations / (temp / times) / 1000000);

    temp = 0;
    for (int i = 0; i < times; i++) {
        count2way(m1, m2);
        temp += updateTimer(&time_start, &time_end);
    }
    printf("2-way Using %f secs.\t(M)FLOPS: %.2f\n",
        temp / times, operations / (temp / times) / 1000000);

    temp = 0;
    for (int i = 0; i < times; i++) {
        count4way(m1, m2);
        temp += updateTimer(&time_start, &time_end);
    }
    printf("4-way Using %f secs.\t(M)FLOPS: %.2f\n",
        temp / times, operations / (temp / times) / 1000000);

    temp = 0;
    for (int i = 0; i < times; i++) {
        count8way(m1, m2);
        temp += updateTimer(&time_start, &time_end);
    }
    printf("8-way Using %f secs.\t(M)FLOPS: %.2f\n",
        temp / times, operations / (temp / times) / 1000000);

    temp = 0;
    for (int i = 0; i < times; i++) {
        count16way(m1, m2);
        temp += updateTimer(&time_start, &time_end);
    }
    printf("16way Using %f secs.\t(M)FLOPS: %.2f\n",
        temp / times, operations / (temp / times) / 1000000);

    temp = 0;
    for (int i = 0; i < times; i++) {
        count32way(m1, m2);
        temp += updateTimer(&time_start, &time_end);
    }
    printf("32way Using %f secs.\t(M)FLOPS: %.2f\n",
        temp / times, operations / (temp / times) / 1000000);

    return 0;
}

void randomMatrix(float matrix[N][N]){
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand();
        }
    }
}

void count1way(float m1[N][N], float m2[N][N]){
    float ans[N][N];
    int block_len = N;
    int way = 1;
    for (int t = 0; t < way * way; t++) { // 1x1 block
        for (int i = 0; i < block_len; i++) {
            for (int j = 0; j < block_len; j++) {
                int ii = i + block_len * (int)(t / way),
                    jj = j + block_len * (int)(t % way);

                ans[ii][jj] = 0;
                for (int k = 0; k < N; k++) {
                    ans[ii][jj] = m1[ii][k] * m2[k][jj];
                }
            }
        }
    }
}
void count2way(float m1[N][N], float m2[N][N]){
    float ans[N][N];
    int way = 2;
    int block_len = (int)(N / way);
    for (int t = 0; t < way * way; t++) { // 2x2 block
        for (int i = 0; i < block_len; i++) {
            for (int j = 0; j < block_len; j++) {
                int ii = i + block_len * (int)(t / way),
                    jj = j + block_len * (int)(t % way);

                ans[ii][jj] = 0;
                for (int k = 0; k < N; k++) {
                    ans[ii][jj] = m1[ii][k] * m2[k][jj];
                }
            }
        }
    }
}
void count4way(float m1[N][N], float m2[N][N]){
    float ans[N][N];
    int way = 4;
    int block_len = (int)(N / way);
    for (int t = 0; t < way * way; t++) { // 4x4 block
        for (int i = 0; i < block_len; i++) {
            for (int j = 0; j < block_len; j++) {
                int ii = i + block_len * (int)(t / way),
                    jj = j + block_len * (int)(t % way);

                ans[ii][jj] = 0;
                for (int k = 0; k < N; k++) {
                    ans[ii][jj] = m1[ii][k] * m2[k][jj];
                }
            }
        }
    }
}
void count8way(float m1[N][N], float m2[N][N]){
    float ans[N][N];
    int way = 8;
    int block_len = (int)(N / way);
    for (int t = 0; t < way * way; t++) { // 8x8 block
        for (int i = 0; i < block_len; i++) {
            for (int j = 0; j < block_len; j++) {
                int ii = i + block_len * (int)(t / way),
                    jj = j + block_len * (int)(t % way);

                ans[ii][jj] = 0;
                for (int k = 0; k < N; k++) {
                    ans[ii][jj] = m1[ii][k] * m2[k][jj];
                }
            }
        }
    }
}

void count16way(float m1[N][N], float m2[N][N]){
    float ans[N][N];
    int way = 16;
    int block_len = (int)(N / way);
    for (int t = 0; t < way * way; t++) { // 8x8 block
        for (int i = 0; i < block_len; i++) {
            for (int j = 0; j < block_len; j++) {
                int ii = i + block_len * (int)(t / way),
                    jj = j + block_len * (int)(t % way);

                ans[ii][jj] = 0;
                for (int k = 0; k < N; k++) {
                    ans[ii][jj] = m1[ii][k] * m2[k][jj];
                }
            }
        }
    }
}

void count32way(float m1[N][N], float m2[N][N]){
    float ans[N][N];
    int way = 32;
    int block_len = (int)(N / way);
    for (int t = 0; t < way * way; t++) { // 8x8 block
        for (int i = 0; i < block_len; i++) {
            for (int j = 0; j < block_len; j++) {
                int ii = i + block_len * (int)(t / way),
                    jj = j + block_len * (int)(t % way);

                ans[ii][jj] = 0;
                for (int k = 0; k < N; k++) {
                    ans[ii][jj] = m1[ii][k] * m2[k][jj];
                }
            }
        }
    }
}
