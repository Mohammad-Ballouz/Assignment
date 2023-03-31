#include<stdio.h>
#include<stdlib.h>
#include <time.h>

int main(void)
{
    int i, j, x, y, rowsA, colsA, rowsB, colsB, val, sum = 0;
    rowsA = 1000;
    colsA = 1500;
    rowsB = 1500;
    colsB = 1000;
    int** matrixA = (int**)malloc(rowsA*sizeof(int*));
    for (i = 0; i < rowsA; i++)
        matrixA[i] = (int*)malloc(colsA*sizeof(int));
    int** matrixB = (int**)malloc(rowsB*sizeof(int*));
    for (i = 0; i < rowsB; i++)
        matrixB[i] = (int*)malloc(colsB*sizeof(int));
    int** result = (int**)malloc(rowsA*sizeof(int*));
    for (i = 0; i < rowsA; i++)
        result[i] = (int*)malloc(colsB*sizeof(int));

    for (i = 0; i < rowsA; i++) {
        for (j = 0; j < colsA; j++) {
            val = rand()%101;
            matrixA[i][j] = val;
        }
    }

    for (i = 0; i < rowsB; i++) {
        for (j = 0; j < colsB; j++) {
            val = rand()%101;
            matrixB[i][j] = val;
        }
    }

    printf("Computing...\n");
    clock_t start = clock();
    for (i = 0; i < rowsA; i++) {
        for (j = 0; j < colsB; j++) {
            for (x = 0; x < rowsB; x++) {
                sum = sum + matrixA[i][x]*matrixB[x][j];
            }
            result[i][j] = sum;
            sum = 0;
        }
    }
    clock_t end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", elapsed_time);
    return 0;
}
