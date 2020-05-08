#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "bench.h"
#include "../../common/m5ops.h"

conv_struct convs;

volatile uint8_t  * top   = (uint8_t  *)0x2f000000;
volatile uint32_t * val_a = (uint32_t *)0x2f000001;
volatile uint32_t * val_b = (uint32_t *)0x2f000009;
volatile uint32_t * val_c = (uint32_t *)0x2f000011;

int main(void) {
	m5_reset_stats();
  uint32_t base = 0x80c00000;
	TYPE *input = (TYPE *)base;
	TYPE *output = (TYPE *)(base+8*IROW*ICOL*IDEP);
	TYPE *check = (TYPE *)(base+16*OROW*OCOL*ODEP);
	TYPE *kernel = (TYPE *)(base+24*KSIZE*KSIZE);

	int input_row_size = IROW;
  int input_col_size = ICOL;
	int input_dep_size = IDEP;

	int output_row_size = OROW;
	int output_col_size = OCOL;
	int output_dep_size = ODEP;

	int k_size = KSIZE;
	int k_dep = KDEPTH;

  volatile int count = 0;
	stage = 0;

    convs.input = input;
    convs.kernel = kernel;
    convs.output = output;
    convs.input_row_size = input_row_size;
    convs.input_col_size = input_col_size;
		convs.input_dep_size = input_dep_size;
		convs.output_row_size = output_row_size;
		convs.output_col_size = output_col_size;
		convs.output_dep_size = output_dep_size;
		convs.k_size = k_size;
		convs.k_dep = k_dep;

    printf("Generating data\n");
    genData(&convs);
    printf("Data generated\n");

    *val_a = (uint32_t)(void *)input;
    *val_b = (uint32_t)(void *)kernel;
    *val_c = (uint32_t)(void *)output;
    // printf("%d\n", *top);
    *top = 0x01;
    while (stage < 1) count++;

    printf("Job complete\n");
#ifdef CHECK
#endif
	m5_dump_stats();
	m5_exit();
}
