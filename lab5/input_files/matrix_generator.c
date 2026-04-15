#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void matadd1(int N, int M1[N][N], int M2[N][N], int M3[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            M3[i][j] = M2[i][j] + M1[i][j];
}

void matadd2(int N, int M1[N][N], int M2[N][N], int M3[N][N]) {
    for (int j = 0; j < N; j++) 
        for (int i = 0; i < N; i++)
            M3[i][j] = M2[i][j] + M1[i][j];
}

int main(void) {
    long long int n;
    printf("Enter n: ");
    if (scanf("%lld", &n) != 1) return 1;

    int (*matrix1)[n] = malloc(sizeof(int[n][n]));
    int (*matrix2)[n] = malloc(sizeof(int[n][n]));
    int (*matrix3)[n] = malloc(sizeof(int[n][n]));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix1[i][j] = rand() % 100;
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix2[i][j] = rand() % 100;
        }
    }
    struct timeval start, end;

    gettimeofday(&start, NULL);
    matadd1(n, matrix1, matrix2, matrix3);
    gettimeofday(&end, NULL);
    
    long double seconds = end.tv_sec - start.tv_sec;
    long double micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
    printf("Row-wise sum: %Lf microseconds\n", micros);

    gettimeofday(&start, NULL);
    matadd2(n, matrix1, matrix2, matrix3);
    gettimeofday(&end, NULL);
    
    micros = (((end.tv_sec - start.tv_sec) * 1000000) + end.tv_usec) - (start.tv_usec);
    printf("Column-wise sum: %Lf microseconds\n", micros);

    free(matrix1); free(matrix2); free(matrix3);
    return 0;
}