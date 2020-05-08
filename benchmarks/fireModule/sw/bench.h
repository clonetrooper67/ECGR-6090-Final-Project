#include "../defines.h"

volatile int stage;

typedef struct {
  TYPE * input;
  TYPE * kernel;
  TYPE * output;
  int input_row_size;
  int input_col_size;
  int input_dep_size;

  int output_row_size;
  int output_col_size;
  int output_dep_size;

  int k_size;
  int k_dep;

} conv_struct;

void genData(conv_struct * convs) {
  int r, c, k, mult, sum;
  for(k = 0; k < convs->input_dep_size; k++){
    for( r=0; r < convs->input_row_size; r++ ) {
      for( c=0; c < convs->input_col_size; c++ ) {
        convs->input[INDX3D(r,c,k)] = INDX3D(r,c,k);
      }
    }
  }
  for(k = 0; k < convs->output_dep_size; k++){
    for( r=0; r < convs->output_row_size; r++ ) {
      for( c=0; c < convs->output_col_size; c++ ) {
        convs->output[INDX3D(r,c,k)] = INDX3D(r,c,k);
      }
    }
  }
  for(k = 0; k < convs->k_dep; k++){
    for( r=0; r < convs->k_size; r++ ) {
      for( c=0; c < convs->k_size; c++ ) {
        convs->kernel[KINDX3D(r,c,k)] = 0;
      }
    }
  }
  // Set the identity kernel
  for(k = 0; k < convs->k_dep; k++){
    convs->kernel[KINDX3D(KSIZE/2,KSIZE/2,k)] = 1;
  }
}
