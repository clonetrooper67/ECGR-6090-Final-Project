#include <stdio.h>
#include <stdlib.h>

#define COL 10
#define ROW 10
#define DEPTH 2

#define INDX(i,j,k) (ROW*DEPTH*i + DEPTH*j + k)

int main(int argc, char** argv){

        int i, j, k;

        int * a = (int *)malloc(COL * ROW * DEPTH * sizeof(int));
        int * b = (int *)malloc(COL * ROW * DEPTH * sizeof(int));
        int * c = (int *)malloc(COL * ROW * DEPTH * sizeof(int));

        for(k = 0; k < DEPTH; k++){
          for (i = 0; i < ROW; i++){
            for (j = 0; j < COL; j++){
                a[INDX(i,j,k)] = i*j*k + 12;
                // b[i*n + j] = i*j + 13;
                // c[i*n + j] = 0;
            }
          }
        }

         /* perform MM */
         // for (i = 0; i < n; i++){
         //   for (j = 0; j < n; j++){
         //     c[i*n + j] = 0;
         //     for (k = 0; k < n; k++){
         //       c[i*n + j] += a[i*n + j]*b[i*n + j];
         //     }
         //   }
         // }

        // for (i = 0; i < n; i++) {
        //   for (j = 0; j < n; j++) {
        //     printf("%d\t", a[i*n + j]);
        //   }
        //   printf("\n");
        // }
        //
        // printf("\n");
        //
        // for (i = 0; i < n; i++) {
        //   for (j = 0; j < n; j++) {
        //     printf("%d\t", *(c + i*n + j));
        //   }
        //   printf("\n");
        // }

        for(k = 0; k < DEPTH; k++){
          printf("%s %d \n", "output", k);
          for (i = 0; i < ROW; i++) {
            for (j = 0; j < COL; j++) {
              printf("%d\t", a[INDX(i,j,k)]);
            }
            printf("\n");
          }
          printf("\n");
        }

        printf("\n");

        return 0;
}
