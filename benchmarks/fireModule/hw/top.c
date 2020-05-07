#include "hw_defines.h"

void top(uint64_t i_addr,
		 uint64_t k_addr,
		 uint64_t r_addr) {

	//Define Device MMRs
	volatile uint8_t  * GEMMFlags  = (uint8_t *)GEMM;
	volatile uint8_t  * DmaFlags   = (uint8_t  *)(DMA);
	volatile uint64_t * DmaRdAddr  = (uint64_t *)(DMA+1);
	volatile uint64_t * DmaWrAddr  = (uint64_t *)(DMA+9);
	volatile uint32_t * DmaCopyLen = (uint32_t *)(DMA+17);

	//Transfer Input Matrices
	//Transfer M1
	*DmaRdAddr  = i_addr;
	*DmaWrAddr  = IADDR;
	*DmaCopyLen = mat_size;
	*DmaFlags   = DEV_INIT;
	//Poll DMA for finish
	while ((*DmaFlags & DEV_INTR) != DEV_INTR);
	//Transfer M2
	*DmaRdAddr  = k_addr;
	*DmaWrAddr  = KADDR;
	*DmaCopyLen = k_size;
	*DmaFlags   = DEV_INIT;
	//Poll DMA for finish
	while ((*DmaFlags & DEV_INTR) != DEV_INTR);

	//Start the accelerated function
	*GEMMFlags = DEV_INIT;
	//Poll function for finish
	while ((*GEMMFlags & DEV_INTR) != DEV_INTR);

	//Transfer M3
	*DmaRdAddr  = RADDR;
	*DmaWrAddr  = r_addr;
	*DmaCopyLen = mat_size;
	*DmaFlags   = DEV_INIT;
	//Poll DMA for finish
	while ((*DmaFlags & DEV_INTR) != DEV_INTR);
	return;
}
