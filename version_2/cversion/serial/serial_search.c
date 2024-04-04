/*
 * Parameters: grid file (.txt format), size of grid, multiplier
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../calculate.h"
#include "../../array_generator.h"

int main(int argc, char * argv[]){

    /* --- starting up --- */


    time_t start = clock();
    time_t start2 = time(NULL);

    // ensure the number of args is correct
    if(argc != 4){
        printf("Too many or too little arguments.\n");
        return 1;
    }

    int size, multiplier;
    array_information array_info;

    // get size from param2
    size = strtol(argv[2], NULL, 10);

    // get multiplier from param3
    // NOTE: multiplier pseudo-increases the size of the data set
    multiplier = strtol(argv[3], NULL, 10);

    time_t array_start = time(NULL);

    // create useful arrays
    long * answers = malloc(sizeof(long) * size * 5);
    if(allocate_structs(argv[1], &array_info, 1, answers, size) == 1)
        return 1;

    time_t array_end = time(NULL);


    /* --- peform calculations on data set --- */


    // check array and determine biggest value
    int index;
    long * temp_answers;

    for(int k = 0; k < multiplier; k++){
        index = 0;
        temp_answers = answers;
        *temp_answers = 0;

        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                calculate(&array_info, i, j, temp_answers);
            }
            // update index if new answer is bigger
            if(*temp_answers > array_info.answers[index * 5])
                index = i;

            temp_answers += 5;
            *temp_answers = 0;
        }
    }


    /* --- print answers --- */


    long sum;
    int a, b, c, d;

    sum = answers[(index * 5) + 0];
    a = answers[(index * 5) + 1];
    b = answers[(index * 5) + 2];
    c = answers[(index * 5) + 3];
    d = answers[(index * 5) + 4];

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
    free(answers);

    return 0;
}
