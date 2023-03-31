#include <stdio.h>
#include <stdlib.h>
#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 4

int a = 1000;
int b = 1500;
int c = 1500;
int d = 1000;
int** matrix1;
int** matrix2;
int** result;

void* matrix_multiply(void* arg)
{
    int thread_id = *(int*)arg;
    int block_size = a / NUM_THREADS;
    int start = thread_id * block_size;
    int end = (thread_id == NUM_THREADS - 1) ? a : (thread_id + 1) * block_size;

    for (int i = start; i < end; i++) {
        for (int j = 0; j < d; j++) {
            int total = 0;
            for (int k = 0; k < c; k++) {
                total = total + matrix1[i][k] * matrix2[k][j];
            }
            result[i][j] = total;
        }
    }

    pthread_exit(NULL);
}

int main(void)
{
    matrix1 = (int**)malloc(a * sizeof(int*));
    for (int i = 0; i < a; i++)
        matrix1[i] = (int*)malloc(b * sizeof(int));
    matrix2 = (int**)malloc(c * sizeof(int*));
    for (int i = 0; i < c; i++)
        matrix2[i] = (int*)malloc(d * sizeof(int));
    result = (int**)malloc(a * sizeof(int*));
    for (int i = 0; i < a; i++)
        result[i] = (int*)malloc(d * sizeof(int));

    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            int value = rand() % 101;
            matrix1[i][j] = value;
        }
    }

    for (int i = 0; i < c; i++) {
        for (int j = 0; j < d; j++) {
            int value = rand() % 101;
            matrix2[i][j] = value;
        }
    }

    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    clock_t start = clock();
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, matrix_multiply, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    clock_t end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", elapsed_time);
    return 0;
}
