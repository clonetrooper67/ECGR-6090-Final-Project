#include "hw_defines.h"

void fireModule(){
    uint8_t * m1base = (uint8_t *)M1ADDR;
    uint8_t * m2base = (uint8_t *)M2ADDR;
    uint8_t * m3base = (uint8_t *)M3ADDR;
    TYPE    * m1     = (TYPE    *)m1base;
    TYPE    * m2     = (TYPE    *)m2base;
    TYPE    * m3     = (TYPE    *)m3base;
    int l_col, i_col;
    TYPE sum;
    #pragma clang loop unroll(full)
    for(int i=0;i<row_size;i++) {
        i_col = i * col_size;
        for(int j=0;j<col_size;j++) {
          if(!(i-K/2<0 || j-K/2<0 || i+K/2>=ROW || j+K/2 >= COL)){
          sum = 0;
          for(int l = -K/2; l < K/2; l++){
            for(int h = -K/2; h < K/2; h++){
              sum += m1[(i+l) * col_size + j + h] * m2[(l+K/2) * col_size + j + h+K/2];
            }
          }
          m3[i_col + j] = sum;
        }
      }
    }
}
