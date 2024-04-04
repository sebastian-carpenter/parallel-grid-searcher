#ifndef PARALLEL_HELPER_H
#define PARALLEL_HELPER_H

#include <pthread.h>

#include "array_generator.h"

/* --- data structures --- */

typedef struct parallel_args {
    array_information * array_info;
    int i;
} parallel_args;

/* --- functions --- */

// function call for a thread to begin calculating a row
// input: parallel_args as void *
// output: NULL
void * calculate_step(void *);

#endif
