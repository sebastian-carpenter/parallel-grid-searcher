#ifndef ARRAY_GENERATOR_H
#define ARRAY_GENERATOR_H

/* --- data structures --- */

typedef struct array_information {
    // '2D' array size x size
    int * numbers;
    // '3D' array size x size x 5
    long * answer;
    int size;
} array_information;

/* --- allocation --- */

// make a variable sized 2D array storing values read in from a file: [rows][cols]
// NOTE: this array is created in only one dimension of [size * size]
// output -> 1 if error in reading file, 0 otherwise
// input -> file name, struct array_information
int allocate_grid(char *, array_information *);

// make a variable sized 3D array to store answers: [rows][columns][sum, f1, f2, f3, f4]
// NOTE: this array is created in only one dimension of [size * size * 5]
// output -> void 
// input -> struct array_information
void allocate_array_3d(array_information *);

#endif
