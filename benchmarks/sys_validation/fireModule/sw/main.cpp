#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "bench.h"
#include "../../../common/m5ops.h"

vec_struct ges;

volatile uint8_t  * top   = (uint8_t  *)0x2f000000;
volatile uint32_t * val_a = (uint32_t *)0x2f000001;
volatile uint32_t * val_b = (uint32_t *)0x2f000009;
volatile uint32_t * val_c = (uint32_t *)0x2f000011;

int main(void) {
	m5_reset_stats();
  uint32_t base = 0x80c00000;
	TYPE *v1 = (TYPE *)base;
	TYPE *v2 = (TYPE *)(base+8*LEN);
	TYPE *v3 = (TYPE *)(base+16*LEN);
	TYPE *check = (TYPE *)(base+24*LEN);
	int vec_len = LEN;
  volatile int count = 0;
	stage = 0;

    ges.a = v1;
    ges.b = v2;
    ges.c = v3;
    ges.vec_len = vec_len;

    printf("Generating data\n");
    genData(&ges);
    printf("Data generated\n");

    *val_a = (uint32_t)(void *)v1;
    *val_b = (uint32_t)(void *)v2;
    *val_c = (uint32_t)(void *)v3;
    // printf("%d\n", *top);
    *top = 0x01;
    while (stage < 1) count++;

    printf("Job complete\n");
#ifdef CHECK
    printf("Checking result\n");
    printf("Running bench on CPU\n");

		bool fail = false;
		int i;
		for(i=0;i<LEN;i++) {
			check[i] = v1[i] + v2[i];
		}

		printf("Comparing CPU run to accelerated run\n");
    for(i=0; i<LEN; i++) {
        if(v3[i] != check[i]) {
            printf("Expected:%f Actual:%f\n", check[i], v3[i]);
            fail = true;
            break;
        }
    }
    if(fail)
        printf("Check Failed\n");
    else
        printf("Check Passed\n");
#endif
	m5_dump_stats();
	m5_exit();
}
