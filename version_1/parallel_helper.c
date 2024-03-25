#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "calculate.h"
#include "array_generator.h"
#include "parallel_helper.h"

void * calculate_step(void * input){

    parallel_args * arg = (parallel_args *) input;

    array_information * array_info = arg->array_info;

    int size = array_info->size;
    int i = arg->i;
    long * largestAnswer = array_info->answers + (i * 5);

    // largestAnswer needs to start with a small value
    *largestAnswer = 0;

    for(int j = 0; j < size; j++)
        calculate(array_info, i, j, largestAnswer);

    free(arg);

    pthread_exit(NULL);

    return NULL;
}
