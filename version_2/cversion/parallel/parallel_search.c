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

    int size, multiplier, NTHREADS, num_structs;

    //  --- important mutex for syncing answer ---
    pthread_mutex_t mutex_answer = PTHREAD_MUTEX_INITIALIZER;

    // reading in argument information
    // NOTE: multiplier pseudo-increases the size of the data set,
    size = strtol(argv[2], NULL, 10);
    multiplier = strtol(argv[3], NULL, 10);
    NTHREADS = strtol(argv[4], NULL, 10);

    // determine num_structs
    num_structs = 4;
    if(NTHREADS < 4)
        num_structs = NTHREADS;

    array_information array_info[num_structs];

    time_t array_start = time(NULL);

    // create useful arrays
    long * answer = malloc(sizeof(long) * 5);
    if(allocate_structs(argv[1], array_info, num_structs, answer, &mutex_answer, NTHREADS, size) == 1)
        return 1;

    time_t array_end = time(NULL);

    pthread_t threads[NTHREADS];


    /* --- peform calculations on data set --- */

 
    for(int k = 0; k < multiplier; k++){

        // perform computations
        for(int i = 0; i < NTHREADS; i++){
            parallel_args * calculate_args = malloc(sizeof(parallel_args));
            *calculate_args = (parallel_args){.array_info = &array_info[i % num_structs], .i = i};

            pthread_create(&threads[i], NULL, calculate_step, (void *) calculate_args);
        }
        
        // join threads
        for(int i = 0; i < NTHREADS; i++)
            if(pthread_join(threads[i], NULL) != 0)
                printf("Something died\n");
    }


    /* --- print answers --- */


    long sum;
    int a, b, c, d;

    sum = answer[0];
    a = answer[1];
    b = answer[2];
    c = answer[3];
    d = answer[4];

    time_t end = clock();
    time_t end2 = time(NULL);

    // print largest value
    printf("For this %d x %d grid the largest product of four adjacent numbers is:\n    %li", size, size, sum);
    printf("\nThe factors of this number are:\n    %d X %d X %d X %d\n", a, b, c, d);
    printf("Time it took this process to run:\n    %lf\n", ((double)(end - start) / CLOCKS_PER_SEC));
    printf("Time it took this program to run:\n    %li\n", (end2 - start2));
    printf("Time it took to allocate arrays:\n    %li\n", (array_end - array_start));

    // free the malloc'ed memory
    for(int i = 0; i < num_structs; i++)
        free((array_info + i)->numbers);
    free(answer);

    // destroy mutex
    pthread_mutex_destroy(&mutex_answer);

    return 0;
}
