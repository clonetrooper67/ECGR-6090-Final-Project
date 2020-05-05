#include "../defines.h"

volatile int stage;

typedef struct {
    TYPE * a;
    TYPE * b;
    TYPE * c;
    int vec_len;
} vec_struct;

void genData(vec_struct * ges) {
    int r;

    for( r=0; r < ges->vec_len; r++ ) {
        ges->a[r] = 1;
        ges->b[r] = 1;
        ges->c[r] = 0;
    }
}
