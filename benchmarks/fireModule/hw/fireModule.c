#include "hw_defines.h"

void fireModule(){
  uint8_t * m1base = (uint8_t * )IADDR;
  uint8_t * kbase = (uint8_t * )KADDR;
  uint8_t * m3base = (uint8_t * )RADDR;
  TYPE    * input     = (TYPE    * )m1base;
  TYPE    * kernel     = (TYPE    * )kbase;
  TYPE    * result     = (TYPE    * )m3base;

  TYPE sum;
  int s = 0;

    
  for(int k = 0; k < dep_size; k++){
    // #pragma clang loop unroll(full)
    for(int i = 0;i < row_size;i+=STRIDE) {
        // #pragma clang loop unroll(full)
        // #pragma clang loop unroll_count(4)
      for(int j = 0;j < col_size; j+=STRIDE) {
        if(!(i-KSIZE/2<0 || j-KSIZE/2<0 || i+KSIZE/2>=IROW || j+KSIZE/2 >= ICOL)){
          // #pragma clang loop unroll(full)
          for(int w = 0; w < KDEPTH; w++){
            sum = 0;
            for(int l = -KSIZE/2; l < KSIZE/2; l++){
              for(int h = -KSIZE/2; h < KSIZE/2; h++){
                sum += input[INDX3D(i+l, j+h, k)] * kernel[KINDX3D(l+KSIZE/2, h+KSIZE/2, w)];
              }
            }
            result[STRIDEINDX3D(i, j, k*KSIZE+w)] = sum;
          }
        }
      }
    }
  }
}
