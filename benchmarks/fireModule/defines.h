#ifndef __DEFINES_H__
#define __DEFINES_H__

// #define CHECK

// Input Feature Map Dimensions
#define TYPE uint8_t
#define IROW 55
#define ICOL 55
#define IDEP 1

// Filter Dimensions
#define KSIZE 3
#define KDEPTH 1
#define STRIDE 1

// Output Fmap Dimensions
#define OROW IROW/STRIDE
#define OCOL ICOL/STRIDE
#define ODEP IDEP*KDEPTH

// Pointer Math Suckz
#define INDX3D(i,j,k) (IROW*ICOL*(k) + ICOL*(j) + i)
#define STRIDEINDX3D(i,j,k) (IROW/STRIDE*ICOL/STRIDE*(k) + ICOL/STRIDE*(j/STRIDE) + i/STRIDE)
#define KINDX3D(i,j,k) (KSIZE*KSIZE*(k) + KSIZE*(i) + j)

#endif
