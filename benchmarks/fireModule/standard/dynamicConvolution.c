#include "dynamicConvolution.h"

int main(int argc, char** argv){
        int i, j, k, l, h;

        int * a = (int *)malloc(N * M * L * sizeof(int));
        int * result1 = (int *)malloc(N * M * L * sizeof(int));
        int * resultK = (int *)malloc(N * M * L * sizeof(int));

        int * kernel2D = (int *)malloc(K * K * sizeof(int));

        // Setup Matrices
        for (i = 0; i < N; i++){
          for (j = 0; j < M; j++){
            for(k = 0; k < L; k++){
              a[INDX3D(i,j,k)] = i*j*k + 12;
              result1[INDX3D(i,j,k)] = 1;
              resultK[INDX3D(i,j,k)] = 1;
              printf("%d\t", a[INDX3D(i,j,k)]);
              printf("%d\t", result1[INDX3D(i,j,k)]);
              printf("%d\t", resultK[INDX3D(i,j,k)]);
            }
          }
        }

        // Setup Kernel
        for (i = 0; i < K; i++){
          for (j = 0; j< K; j++){
            kernel2D[INDX2D(i,j)] = 0;
          }
        }

        // Set an identity kernel
        kernel2D[INDX2D(K/2,K/2)] = 1;

        convK(a, kernel2D, resultK);
        conv1(a,result1);
        // Print the matrices
        printMatrix(a, "Initial Matrix");
        printMatrix(result1, "1x1 Result Matrix");
        printMatrix(resultK, "KxK Result Matrix");

        return 0;
}

// For 1 x 1 Convolutions
void conv1(int *a, int *c){
  int i, j, k;
  for(int k = 0; k < L; k++){
    for (i = 0; i < N; i++){
      for (j = 0; j < M; j++){
        c[INDX3D(i,j,k)] = a[INDX3D(i,j,k)]*KERNEL1;
      }
    }
  }
}

// For K x K Convolutions
void convK(int *a, int *kernel2D, int *c){
  int i, j, k, l, h;
  for(k = 0; k < L; k++){
    for (i = 0; i < N; i++){
      for (j = 0; j < M; j++){
        if(!(i-K/2<0 || j-K/2<0 || i+K/2>=N || j+K/2 >= M)){
          for (l = -K/2; l < K/2; l++){
            for(h = -K/2; h < K/2; h++){
              c[INDX3D(i,j,k)] += a[INDX3D(i+l,j+h,k)]*kernel2D[INDX2D(l+K/2, h+K/2)];
            }
          }
        }
      }
    }
  }
}

// Prints a 3D Matrix
void printMatrix(int a[SIZE], char output[]){
  int i,j,k;

  for(k = 0; k < L; k++){
    printf("%s %d \n", output, k);
    for (i = 0; i < N; i++) {
      for (j = 0; j < M; j++) {
        printf("%d\t", a[INDX3D(i,j,k)]);
      }
      printf("\n");
    }
    printf("\n");
  }
}
