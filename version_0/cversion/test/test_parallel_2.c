/*
 * Problem 11: Largest Product in a Grid
 * What is the greatest product of four adjacent numbers in
 * the 20 x 20 grid (up, down, left, right, diagonal)
 */

#include <stdio.h>
#include <stdlib.h>
#include "../array_generator.h"
#include <time.h>
#include <pthread.h>

#define NTHREADS 4

struct args {
    int ** numbers;
    int size;
    int i;
    int j;
    int tid;
};

void * calculate_step(void * input){
    int i = ((struct args *) input)->i;
    int j = ((struct args *) input)->j;
    int tid = ((struct args *) input)->tid;

    printf("row %d number %d from %d\n", i, ((struct args *) input)->numbers[i][j], tid);

    free((struct args *) input);

    pthread_exit(NULL);

    return NULL;
}

int main(int argc, char * argv[]){

    time_t start = clock();

    // ensure there is a correct number of args
    if(argc != 4){
        printf("Too many or too little arguments.\n");
        return 1;
    }

    int size, multiplier;
    int ** numbers;

    pthread_t threads[NTHREADS];
    //struct args * calculate_args = (struct args *) malloc(sizeof(struct args));

    // get size from param2
    size = strtol(argv[2], NULL, 10);

    // get multiplier from param3
    // multiplier pseudo-increases the size of the data set
    multiplier = strtol(argv[3], NULL, 10);

    // create useful array
    numbers = allocate_grid(argv[1], size);

    int modThread;
    // spawn threads to check array
    for(int k = 0; k < multiplier; k++){
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                struct args * calculate_args = (struct args *) malloc(sizeof(struct args));
                calculate_args->numbers = numbers;
                calculate_args->size = size;

                modThread = j % NTHREADS;

                printf("Spooling thread %d\n", modThread);

                calculate_args->i = i;
                calculate_args->j = j;
                calculate_args->tid = modThread;

                pthread_create(&threads[modThread], NULL, calculate_step, (void *) calculate_args);
            }
        }
    }

    /*// wait for the threads to finish
    for(int i = 0; i < NTHREADS; i++)
        pthread_join(threads[i], NULL);*/

    time_t end = clock();

    // print time to run
    printf("Time it took this process to run:\n    %lf\n", ((double)(end - start) / CLOCKS_PER_SEC));

    // free the malloc'ed memory
    free(numbers);
    //free(calculate_args);

    return 0;
}
