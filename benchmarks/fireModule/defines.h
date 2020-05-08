#ifndef __DEFINES_H__
#define __DEFINES_H__

// #define CHECK

#define TYPE uint8_t
#define ROW 111
#define COL 111
#define DEP 2

#define K 3

// Pointer Math Suckz
#define INDX3D(i,j,k) (ROW*COL*(k) + COL*(j) + i)
#define INDX2D(i,j) (i + COL*(j))
#define KINDX2D(i,j) (K*(i) + j)

#endif
