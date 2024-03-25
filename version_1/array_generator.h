#ifndef ARRAY_GENERATOR_H
#define ARRAY_GENERATOR_H

/* --- data structures --- */

typedef struct array_information {
    // '2D' array size x size
    int * numbers;
    // '2D' array of size x 5
    long * answers;
    int size;
} array_information;

/* --- allocation --- */

// make a variable sized 2D array storing values read in from a file: [rows][cols]
// copy the allocated array to the other spots available in array_information
// answers and size are also filled using the other parameters
// output -> 1 if error in reading file, 0 otherwise
// input -> file name, struct array_information[num_arrays], number of structs, answer array, size of grid
int allocate_structs(char *, array_information *, int, long *, int);

#endif
