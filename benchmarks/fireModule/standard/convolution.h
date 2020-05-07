#include <stdio.h>

#define N 10
#define M 10
#define L 2

#define K 3
#define KERNEL1 1

// for 1x1 Kernels
void conv1(int a[N][M][L], int c[N][M][L]);
// for KxK Kernels
void convK(int a[N][M][L], int kernel2D[K][K], int c[N][M][L]);
// Prints a Matrix
void printMatrix(int a[N][M][L], char output[]);
