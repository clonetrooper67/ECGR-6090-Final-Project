#include "hw_defines.h"

void fireModule(){
  uint8_t * m1base = (uint8_t * )IADDR;
  uint8_t * kbase = (uint8_t * )KADDR;
  uint8_t * m3base = (uint8_t * )RADDR;
  TYPE    * input     = (TYPE    * )m1base;
  TYPE    * kernel     = (TYPE    * )kbase;
  TYPE    * result     = (TYPE    * )m3base;

  TYPE sum;

    // #pragma clang loop unroll(full)
  for(int k = 0; k < dep_size; k++){
    for(int i = 0;i < row_size;i++) {
        // #pragma clang loop unroll(full)
        // #pragma clang loop unroll_count(4)
      for(int j = 0;j < col_size; j++) {
        if(!(i-K/2<0 || j-K/2<0 || i+K/2>=ROW || j+K/2 >= COL)){
          sum = 0;
          for(int l = -K/2; l < K/2; l++){
            for(int h = -K/2; h < K/2; h++){
              // sum += input[INDX3D(i+l, j+h, k)] * kernel[KINDX2D(l+K/2, h+K/2)];
              sum += input[INDX3D(i, j, k)] * kernel[KINDX2D(i, j)];

            }
          }
          result[INDX3D(i, j, k)] = sum;
        }
      }
    }
  }
}
