/*
 * Problem 11: Largest Product in a Grid
 * What is the greatest product of four adjacent numbers in
 * the 20 x 20 grid (up, down, left, right, diagonal)
 */

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


    /* --- peform calculations on data set --- */


    // check array and determine biggest value
    int indexi, indexj;
    indexi = indexj = 0;

    for(int k = 0; k < multiplier; k++){
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                calculate(&array_info, i, j);

                // update indicies if new answer is bigger
                if(array_info.answer[i * size * 5 + j * 5] > array_info.answer[indexi * size * 5 + indexj * 5]){
                    indexi = i;
                    indexj = j;
                }
            }
        }
    }


    /* --- print answers --- */


    long sum;
    int a, b, c, d;

    sum = array_info.answer[indexi * size * 5 + indexj * 5 + 0];
    a = array_info.answer[indexi * size * 5 + indexj * 5 + 1];
    b = array_info.answer[indexi * size * 5 + indexj * 5 + 2];
    c = array_info.answer[indexi * size * 5 + indexj * 5 + 3];
    d = array_info.answer[indexi * size * 5 + indexj * 5 + 4];

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
