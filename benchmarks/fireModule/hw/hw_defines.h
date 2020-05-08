//Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include "../defines.h"

#define DEV_INIT	0x01
#define DEV_INTR	0x04

//Specify row/column sizes
#define row_size 	IROW
#define col_size 	ICOL
#define dep_size	IDEP

#define mat_size	row_size*col_size*dep_size*sizeof(TYPE)

#define output_mat_size	OROW*OCOL*ODEP*sizeof(TYPE)

#define k_size KSIZE*KSIZE*KDEPTH*sizeof(TYPE)

// Device MMR addresses
#define TOP			0x2f000000
#define CONV		0x2f000019
#define DMA			0x2ff00000

// Specify the scratchpad addresses for variables
#define SPM			0x2f100000
#define KADDR		SPM + (k_size * 0)
#define IADDR		SPM + k_size + (mat_size * 0)
#define RADDR		SPM + k_size + (mat_size * 0) + (output_mat_size * 0)
