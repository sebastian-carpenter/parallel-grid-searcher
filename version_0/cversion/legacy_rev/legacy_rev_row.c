/*
 * Problem 11: Largest Product in a Grid
 * What is the greatest product of four adjacent numbers in
 * the 20 x 20 grid (up, down, left, right, diagonal)
 */

/*
 * Parameters: grid file (.txt format), size of grid, multiplier, thread count
 *
 * Do not run this program with more threads than the size of the grid it will not work
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#include "../../parallel_helper.h"
#include "../../calculate.h"
#include "../../array_generator.h"

int main(int argc, char * argv[]){

    /* --- starting up --- */


    time_t start = clock();
    time_t start2 = time(NULL);

    // ensure the number of args is correct
    if(argc != 5){
        printf("Too many or too little arguments.\n");
        return 1;
    }

    int NTHREADS, size, multiplier;

    array_information array_info;

    // set the number of threads to use
    NTHREADS = strtol(argv[4], NULL, 10);

    // get size from param2
    size = strtol(argv[2], NULL, 10);
    array_info.size = size;

    // get multiplier from param3
    // NOTE: multiplier pseudo-increases the size of the data set
    multiplier = strtol(argv[3], NULL, 10);

    time_t array_start = time(NULL);
    
    // create useful arrays
    if(allocate_grid(argv[1], &array_info) == 1)
        return 1;
    allocate_array_3d(&array_info);

    time_t array_end = time(NULL);

    pthread_t threads[NTHREADS];


    /* --- peform calculations on data set --- */


    // perform computations on each row (parallel)
    int modThread = 0;

    // bootstart computations
    for(int i = 0; i < NTHREADS; i++){
        parallel_args * calculate_args = malloc(sizeof(parallel_args));
        *calculate_args = (parallel_args){.array_info = &array_info, .i = i};

        pthread_create(&threads[modThread], NULL, calculate_step, (void *) calculate_args);

        modThread++;
    }

    modThread = 0;

    for(int k = 0; k < multiplier; k++){
        for(int i = NTHREADS; i < size; i++){

            // join thread before spooling another task
            if(pthread_join(threads[modThread], NULL) != 0)
                printf("Something died\n");

            parallel_args * calculate_args = malloc(sizeof(parallel_args));
            *calculate_args = (parallel_args){.array_info = &array_info, .i = i};

            pthread_create(&threads[modThread], NULL, calculate_step, (void *) calculate_args);

            modThread++;

            // reset thread counter when cap reached
            if(modThread == NTHREADS)
                modThread = 0;
        }
    }


    /* --- consolidate answers --- */


    // locate biggest value in each row (parallel)
    for(int i = 0; i < size; i++){

        // join thread before spooling another task
        if(pthread_join(threads[modThread], NULL) != 0)
            printf("Something died\n");

        parallel_args * determine_args = malloc(sizeof(parallel_args));
        *determine_args = (parallel_args){.array_info = &array_info, .i = i};

        pthread_create(&threads[modThread], NULL, determine, (void *) determine_args);
        
        modThread++;

        // wait for threads to finish to prevent errors
        if(modThread == NTHREADS)
            modThread = 0;
    }

    // join threads before absolute maximum is determined
    for(int i = 0; i < NTHREADS; i++)
        if(pthread_join(threads[i], NULL) != 0)
            printf("Something died\n");

    // determine biggest value total (serial)
    // NOTE: answer array is changed when the values were compared in parallel above
    int index = 0;
    for(int i = 0; i < size; i++)
        if(array_info.answer[i * size * 5] > array_info.answer[index * size * 5])
            index = i;


    /* --- print answers --- */


    long sum;
    int a, b, c, d;

    sum = array_info.answer[index * size * 5 + 0];
    a = array_info.answer[index * size * 5 + 1];
    b = array_info.answer[index * size * 5 + 2];
    c = array_info.answer[index * size * 5 + 3];
    d = array_info.answer[index * size * 5 + 4];

    time_t end = clock();
    time_t end2 = time(NULL);

    // print largest value
    printf("For this %d x %d grid the largest product of four adjacent numbers is:\n    %li", size, size, sum);
    printf("\nThe factors of this number are:\n    %d X %d X %d X %d\n", a, b, c, d);
    printf("Time it took this process to run:\n    %lf\n", ((double)(end - start) / CLOCKS_PER_SEC));
    printf("Time it took this program to run:\n    %li\n", (end2 - start2));
    printf("Time it took to allocate arrays:\n    %li\n", (array_end - array_start));

    // free the malloc'ed memory
    free(array_info.numbers);
    free(array_info.answer);

    return 0;
}
