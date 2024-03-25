#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "calculate.h"
#include "array_generator.h"
#include "parallel_helper.h"

void * calculate_step(void * input){

    for(int j = 0; j < (((parallel_args *) input)->array_info->size); j++)
        calculate(((parallel_args *) input)->array_info, ((parallel_args *) input)->i, j);

    free((parallel_args *) input);

    pthread_exit(NULL);

    return NULL;
}

void * determine(void * input){

    long * answer = ((parallel_args *) input)->array_info->answer;
    int i = ((parallel_args *) input)->i;
    int size = ((parallel_args *) input)->array_info->size;

    // determine biggest value total
    int index = 0;
    for(int j = 0; j < size; j++)
        if(answer[i * size * 5 + j * 5 + 0] > answer[i * size * 5 + index * 5 + 0])
            index = j;

    // assign value
    answer[i * size * 5] = answer[i * size * 5 + index * 5 + 0];
    answer[i * size * 5 + 1] = answer[i * size * 5 + index * 5 + 1];
    answer[i * size * 5 + 2] = answer[i * size * 5 + index * 5 + 2];
    answer[i * size * 5 + 3] = answer[i * size * 5 + index * 5 + 3];
    answer[i * size * 5 + 4] = answer[i * size * 5 + index * 5 + 4];

    free((parallel_args *) input);

    pthread_exit(NULL);

    return NULL;
}
