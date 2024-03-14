#ifndef CALCULATE_H
#define CALCULATE_H

#include "array_generator.h"

// at a cell test up/down, left/right, and both diagonals for the biggest
// product of four numbers, then store the product as well as its factors
// within the included struct parameter
//
// input: struct array_information, index i, index j
// output: void
void calculate(array_information *, int, int);

#endif
