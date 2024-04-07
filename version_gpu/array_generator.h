#ifndef ARRAY_GENERATOR_H
#define ARRAY_GENERATOR_H

#include <pthread.h>

/* --- data structures --- */

typedef struct array_information {
    // '2D' array size x size
    int * numbers;
    // '2D' array of size x 5
    long * answer;
    pthread_mutex_t * mutex_answer;
    int NTHREADS;
    int size;
} array_information;

/* --- allocation --- */

// make a variable sized 2D array storing values read in from a file: [rows][cols]
// copy the allocated array to all instances of array_information
// answers, mutex_answer, NTHREADS, and size are filled in alongside this operation
// output -> 1 if error in reading file, 0 otherwise
// input -> file name, struct array_information[num_arrays], number of structs, answer array, mutex, NTHREADS, size of grid
int allocate_structs(char *, array_information *, int, long *, pthread_mutex_t *, int, int);

#endif
