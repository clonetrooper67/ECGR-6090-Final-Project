#include <stdlib.h>
#include <stdio.h>

#define N 10
#define M 10
#define K 3

void conv1D(int a[N][M], int c[N][M]);
void conv2D(int a[N][M], int kernel[K][K], int c[N][M]);
void printMatrices(int a[N][M], int c[N][M]);

int main(int argc, char** argv){
        int i, j, l, h;

        // clock_t t;

        int a[N][M];

        int kernel [K][K];

        int c[N][M];

        // Setup Matrices

        for (i = 0; i < N; i++){
          for (j = 0; j < M; j++){
            a[i][j] = rand()%1024;
            c[i][j] = 0;
          }
        }

        // Setup Kernel

        for (i = 0; i < K; i++){
          for (j = 0; j< K; j++){
            kernel[i][j] = 0;
          }
        }

        // kernel[0][0] = 1;
        kernel[K/2][K/2] = 1;
        // t = clock() - t;
        conv2D(a, kernel, c);

        printMatrices(a,c);

        return 0;
}

void conv1D(int a[N][M], int c[N][M]){

}

void conv2D(int a[N][M], int kernel[K][K], int c[N][M]){
  int i, j, l, h;
  for (i = 0; i < N; i++){
    for (j = 0; j < M; j++){

      c[i][j] = 0;

      if(!(i-K/2<0 || j-K/2<0 || i+K/2>=N || j+K/2 >= M)){
        for (l = -K/2; l < K/2; l++){
          for(h = -K/2; h < K/2; h++){
             c[i][j] += a[i+l][j+h]*kernel[l+K/2][h+K/2];
           }
         }
       }
     }
   }
 }

void printMatrices(int a[N][M], int c[N][M]){
  int i,j;

  for (i = 0; i < N; i++) {
    for (j = 0; j < M; j++) {
      printf("%d\t", a[i][j]);
    }
    printf("\n");
  }

  printf("\n");

  for (i = 0; i < N; i++) {
    for (j = 0; j < M; j++) {
      printf("%d\t", c[i][j]);
    }
    printf("\n");
  }

  printf("\n");
}
