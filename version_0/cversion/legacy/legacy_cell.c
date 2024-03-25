/*
 * Problem 11: Largest Product in a Grid
 * What is the greatest product of four adjacent numbers in
 * the 20 x 20 grid (up, down, left, right, diagonal)
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../calculate.h"
#include "../../array_generator.h"
#include <pthread.h>

//#define NTHREADS 4

struct args {
    int ** numbers;
    int size;
    long *** answer;
    int i;
    int j;
};

void * calculate_step(void * input){
    int i, j;
    i = ((struct args *) input)->i;
    j = ((struct args *) input)->j;

    calculate(((struct args *) input)->numbers, ((struct args *) input)->size, ((struct args *) input)->answer[i][j], i, j);

    free((struct args *) input);

    pthread_exit(NULL);

    return NULL;
}

int main(int argc, char * argv[]){

    time_t start = clock();
    time_t start2 = time(NULL);

    // ensure there is a correct number of args
    if(argc != 5){
        printf("Too many or too little arguments.\n");
        return 1;
    }

    int NTHREADS = strtol(argv[4], NULL, 10);

    int size, multiplier;
    int ** numbers;
    long *** answer;

    pthread_t threads[NTHREADS];

    // get size from param2
    size = strtol(argv[2], NULL, 10);

    // get multiplier from param3
    // multiplier pseudo-increases the size of the data set
    multiplier = strtol(argv[3], NULL, 10);

    time_t array_start = time(NULL);

    // create useful arrays
    numbers = allocate_grid(argv[1], size);
    answer = allocate_array_3d(size);

    time_t array_end = time(NULL);

    int modThread;
    // spawn threads to check array
    for(int k = 0; k < multiplier; k++){
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                struct args * calculate_args = (struct args *) malloc(sizeof(struct args));
                calculate_args->numbers = numbers;
                calculate_args->size = size;
                calculate_args->answer = answer;
                calculate_args->i = i;
                calculate_args->j = j;

                modThread = j % NTHREADS;

                pthread_create(&threads[modThread], NULL, calculate_step, (void *) calculate_args);
            }
        }
    }

    // determine biggest value
    long sum = 0;
    int a, b, c, d;

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(answer[i][j][0] > sum){
                sum = answer[i][j][0];
                a = answer[i][j][1];
                b = answer[i][j][2];
                c = answer[i][j][3];
                d = answer[i][j][4];
            }
        }
    }

    time_t end = clock();
    time_t end2 = time(NULL);

    // print largest value
    printf("For this %d x %d grid the largest product of four adjacent numbers is:\n    %li", size, size, sum);
    printf("\nThe factors of this number are:\n    %d X %d X %d X %d\n", a, b, c, d);
    printf("Time it took this process to run:\n    %lf\n", ((double)(end - start) / CLOCKS_PER_SEC));
    printf("Time it took this program to run:\n    %li\n", (end2 - start2));
    printf("Time it took to allocate arrays:\n    %li\n", (array_end - array_start));

    // free the malloc'ed memory
    free(numbers);
    free(answer);

    return 0;
}
