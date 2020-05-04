#include "hw_defines.h"

void vectorAdd(){
    uint8_t * v1base = (uint8_t *)V1ADDR;
    uint8_t * v2base = (uint8_t *)V2ADDR;
    uint8_t * v3base = (uint8_t *)V3ADDR;
    TYPE    * v1     = (TYPE    *)v1base;
    TYPE    * v2     = (TYPE    *)v2base;
    TYPE    * v3     = (TYPE    *)v3base;
    #pragma clang loop unroll(full)
    for(int i=0;i<vec_len;i++) {
      v3[i] = v1[i] + v2[i];
    }
}
