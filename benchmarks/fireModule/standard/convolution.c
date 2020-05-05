#include <stdlib.h>
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

int main(int argc, char** argv){
        int i, j, k, l, h;

        int a[N][M][L];

        int kernel2D [K][K];

        int result1[N][M][L];
        int resultK[N][M][L];

        // Setup Matrices
        for (i = 0; i < N; i++){
          for (j = 0; j < M; j++){
            for(k = 0; k < L; k++){
              a[i][j][k] = rand()%1024;
              result1[i][j][k] = 0;
              resultK[i][j][k] = 0;
            }
          }
        }

        // Setup Kernel
        for (i = 0; i < K; i++){
          for (j = 0; j< K; j++){
            kernel2D[i][j] = 0;
          }
        }

        // Set an identity kernel
        kernel2D[K/2][K/2] = 1;

        convK(a, kernel2D, resultK);
        conv1(a,result1);
        // Print the matrices
        printMatrix(a, "Initial Matrix");
        printMatrix(result1, "1x1 Result Matrix");
        printMatrix(resultK, "KxK Result Matrix");

        return 0;
}

// For 1 x 1 Convolutions
void conv1(int a[N][M][L], int c[N][M][L]){
  int i, j, k;
  for(int k = 0; k < L; k++){
    for (i = 0; i < N; i++){
      for (j = 0; j < M; j++){
        c[i][j][k] = a[i][j][k]*KERNEL1;
      }
    }
  }
}

// For K x K Convolutions
void convK(int a[N][M][L], int kernel2D[K][K], int c[N][M][L]){
  int i, j, k, l, h;
  for(k = 0; k < L; k++){
    for (i = 0; i < N; i++){
      for (j = 0; j < M; j++){
        if(!(i-K/2<0 || j-K/2<0 || i+K/2>=N || j+K/2 >= M)){
          for (l = -K/2; l < K/2; l++){
            for(h = -K/2; h < K/2; h++){
              c[i][j][k] += a[i+l][j+h][k]*kernel2D[l+K/2][h+K/2];
            }
          }
        }
      }
    }
  }
}

// Prints a 3D Matrix
void printMatrix(int a[N][M][L], char output[]){
  int i,j,k;

  for(k = 0; k < L; k++){
    printf("%s %d \n", output, k);
    for (i = 0; i < N; i++) {
      for (j = 0; j < M; j++) {
        printf("%d\t", a[i][j][k]);
      }
      printf("\n");
    }
    printf("\n");
  }
}
