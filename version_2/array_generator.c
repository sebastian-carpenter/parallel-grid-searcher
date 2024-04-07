#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "array_generator.h"

/* --- allocation --- */

int allocate_structs(char * file_name, array_information * array_info, int num_arrays, long * answer, pthread_mutex_t * mutex_answer, int NTHREADS, int size){

    // allocate 2D array as a 1D array
    array_info->numbers = malloc(sizeof(int) * size * size);
    int * numbers = array_info->numbers;

    FILE * fptr = fopen(file_name, "r");

    // assign values to array
    if(fptr != NULL){
        for(int i = 0; i < size; i++)
            for(int j = 0; j < size; j++)
                fscanf(fptr, "%d", (numbers + i * size + j));
    }
    // file is not valid
    else{
        printf("Unable to open file\n");

        free(array_info->numbers);
        fclose(fptr);

        return 1;
    }

    fclose(fptr);

    // fill in remaining spots of struct
    array_info->answer = answer;
    array_info->mutex_answer = mutex_answer;
    array_info->NTHREADS = NTHREADS;
    array_info->size = size;

    // fill remaining struct instances
    while(num_arrays > 1){
        array_info++;
        num_arrays--;
        // numbers
        array_info->numbers = malloc(sizeof(int) * size * size);
        memcpy(array_info->numbers, numbers, sizeof(int) * size * size);
        // others
        array_info->answer = answer;
        array_info->mutex_answer = mutex_answer;
        array_info->NTHREADS = NTHREADS;
        array_info->size = size;
    }

    // it is very important to do this, leaving a garbage
    // value will probably ruin your results
    answer[0] = 0;

    return 0;
}
