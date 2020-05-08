#ifndef __DEFINES_H__
#define __DEFINES_H__

// #define CHECK

#define TYPE uint8_t
#define ROW 55
#define COL 55
#define DEP 3

#define K 3
#define STR 2

#define ROWSTR ROW/STR
#define COLSTR COL/STR

// Pointer Math Suckz
#define INDX3D(i,j,k) (ROW*COL*(k) + COL*(j) + i)
#define STRINDX3D(i,j,k) (ROWSTR*COLSTR*(k) + COLSTR*(j/STR) + i/STR)
#define INDX2D(i,j) (i + COL*(j))
#define KINDX2D(i,j) (K*(i) + j)

#endif
