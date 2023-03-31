#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(void)
{
    int i, j, x, y, rows, cols, inner, a, total, count = 0;
    double start_time, end_time;
    srand(time(NULL));
    rows = 1000;
    cols = 1500;
    inner = 1500;
    y = 1000;
    int** mat1=(int**)malloc(rows*sizeof(int*));
    for (i=0;i<rows;i++)
        mat1[i]=(int*)malloc(cols*sizeof(int));
    int** mat2=(int**)malloc(inner*sizeof(int*));
    for (i=0;i<inner;i++)
        mat2[i]=(int*)malloc(y*sizeof(int));
    int** result=(int**)malloc(rows*sizeof(int*));
    for (i=0;i<rows;i++)
        result[i]=(int*)malloc(y*sizeof(int));

    for (i=0;i<rows;i++) {
        for (j=0;j<cols;j++) {
            a=rand()%101;
            mat1[i][j]=a;
        }
    }

    for (i=0;i<inner;i++) {
        for (j=0;j<y;j++) {
            a=rand()%101;
            mat2[i][j]=a;   
        }
    }
    printf("Computing...\n");
    start_time=omp_get_wtime();
    omp_set_num_threads(4);
#pragma omp parallel for private(i,j,x,total)
    for (i=0;i<rows;i++) {
        for (j=0;j<y;j++) {
            for (x=0;x<inner;x++) {
                total = total+mat1[i][x]*mat2[x][j];
            }
            result[i][j] = total;
            total = 0;
        }
    }
    end_time=omp_get_wtime();
    printf("Time taken: %f seconds\n", end_time - start_time);
    return 0;
}
