#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "calculate.h"
#include "array_generator.h"
#include "parallel_helper.h"

void * calculate_step(void * input){

    parallel_args * arg = (parallel_args *) input;

    array_information * array_info = arg->array_info;

    int stride = array_info->NTHREADS;
    int size = array_info->size;
    int i = arg->i;
    long largest_answer[5];

    // largest_answer needs to start with a small value
    largest_answer[0] = 0;
    do{
        for(int j = 0; j < size; j++)
            calculate(array_info, i, j, largest_answer);
        // the other threads will calculate the other rows
        i += stride;
    }while(i < size);

    // update the main answer array, if necessary

    pthread_mutex_lock(array_info->mutex_answer);

    if(largest_answer[0] > array_info->answer[0]){
        array_info->answer[0] = largest_answer[0];
        array_info->answer[1] = largest_answer[1];
        array_info->answer[2] = largest_answer[2];
        array_info->answer[3] = largest_answer[3];
        array_info->answer[4] = largest_answer[4];
    }

    pthread_mutex_unlock(array_info->mutex_answer);

    free(arg);

    pthread_exit(NULL);

    return NULL;
}
