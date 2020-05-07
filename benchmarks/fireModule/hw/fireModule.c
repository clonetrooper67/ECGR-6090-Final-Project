#include "hw_defines.h"

void fireModule(){
    uint8_t * m1base = (uint8_t *)M1ADDR;
    uint8_t * kbase = (uint8_t *)KADDR;
    uint8_t * m3base = (uint8_t *)M3ADDR;
    TYPE    * input     = (TYPE    *)m1base;
    TYPE    * kernel     = (TYPE    *)kbase;
    TYPE    * result     = (TYPE    *)m3base;

    int l_col, i_col;
    TYPE sum;

    // #pragma clang loop unroll(full)
    for(int i=0;i<row_size;i++) {
        i_col = i * col_size;
        // #pragma clang loop unroll(full)
        // #pragma clang loop unroll_count(2)
        for(int j=0;j<col_size;j++) {
          if(!(i-K/2<0 || j-K/2<0 || i+K/2>=ROW || j+K/2 >= COL)){
          sum = 0;
          for(int l = -K/2; l < K/2; l++){
            for(int h = -K/2; h < K/2; h++){
              sum += input[(i+l) * col_size + j + h] * kernel[(l+K/2) * col_size + j + h+K/2];
            }
          }
          result[i_col + j] = sum;
        }
      }
    }
}
