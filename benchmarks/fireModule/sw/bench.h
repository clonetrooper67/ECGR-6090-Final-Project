#include "../defines.h"

#define rcIndex     (r*ROW + c)

volatile int stage;

typedef struct {
    TYPE * a;
    TYPE * b;
    TYPE * c;
    int row_size;
    int col_size;
    int k_size;

} gemm_struct;

void genData(gemm_struct * ges) {
    int r, c, k, mult, sum;

    for( r=0; r < ges->row_size; r++ ) {
        for( c=0; c < ges->col_size; c++ ) {
            ges->a[rcIndex] = rcIndex;
            ges->b[rcIndex] = 0;
            ges->c[rcIndex] = 0;
        }
    }
    // Set the identity kernel
    ges->b[ges->k_size/2*ROW+ges->k_size/2] = 1;
}
