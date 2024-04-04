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

    int NTHREADS, size, multiplier, num_structs;

    // set the number of threads to use
    NTHREADS = strtol(argv[4], NULL, 10);

    // get size from param2
    size = strtol(argv[2], NULL, 10);

    // get multiplier from param3
    // NOTE: multiplier pseudo-increases the size of the data set
    multiplier = strtol(argv[3], NULL, 10);

    // determine num_structs
    num_structs = 4;
    if(NTHREADS < 4)
        num_structs = NTHREADS;

    array_information array_info[num_structs];

    time_t array_start = time(NULL);

    // create useful arrays
    long * answers = malloc(sizeof(long) * size * 5);
    if(allocate_structs(argv[1], array_info, num_structs, answers, size) == 1)
        return 1;

    time_t array_end = time(NULL);

    pthread_t threads[NTHREADS];


    /* --- peform calculations on data set --- */

 
    int mod_thread;
    for(int k = 0; k < multiplier; k++){

        // perform computations on each row (parallel)
        mod_thread = 0;

        // bootstart computations
        for(int i = 0; i < NTHREADS; i++){
            parallel_args * calculate_args = malloc(sizeof(parallel_args));
            *calculate_args = (parallel_args){.array_info = &array_info[i % num_structs], .i = i};

            pthread_create(&threads[mod_thread], NULL, calculate_step, (void *) calculate_args);

            mod_thread++;
        }

        mod_thread = 0;

        // perform rest of computations
        for(int i = NTHREADS; i < size; i++){

            // join thread before spooling another task
            if(pthread_join(threads[mod_thread], NULL) != 0)
                printf("Something died\n");

            parallel_args * calculate_args = malloc(sizeof(parallel_args));
            *calculate_args = (parallel_args){.array_info = &array_info[i % num_structs], .i = i};

            pthread_create(&threads[mod_thread], NULL, calculate_step, (void *) calculate_args);

            mod_thread++;

            // reset thread counter when cap reached
            if(mod_thread == NTHREADS)
                mod_thread = 0;
        }

        // join threads before absolute maximum is determined
        for(int i = 0; i < NTHREADS; i++)
            if(pthread_join(threads[i], NULL) != 0)
                printf("Something died\n");
    }


    /* --- consolidate answers --- */


    // determine biggest value total
    int index = 0;
    for(int i = 0; i < size; i++)
        if(answers[i * 5] > answers[index * 5])
            index = i;


    /* --- print answers --- */


    long sum;
    int a, b, c, d;

    sum = answers[index * 5 + 0];
    a = answers[index * 5 + 1];
    b = answers[index * 5 + 2];
    c = answers[index * 5 + 3];
    d = answers[index * 5 + 4];

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
    free(answers);

    return 0;
}
