#include <stdio.h>
#include <stdlib.h>

#define N 10
#define M 10
#define L 2

#define SIZE N*M*L

#define K 3
#define KERNEL1 1

#define INDX3D(i,j,k) (N*M*i + M*j + k)
#define INDX2D(i,j) (N*i + j)
// for 1x1 Kernels
void conv1(int *a, int *c);
// for KxK Kernels
void convK(int *a, int *kernel2D, int *c);
// Prints a Matrix
void printMatrix(int *a, char output[]);
