/*
 * Problem 11: Largest Product in a Grid
 * What is the greatest product of four adjacent numbers in
 * the 20 x 20 grid (up, down, left, right, diagonal)
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../calculate.h"
#include "../array_generator.h"

int main(int argc, char * argv[]){

    time_t start = clock();

    // ensure there is a correct number of args
    if(argc != 3){
        printf("Too many or too little arguments.\n");
        return 1;
    }

    // get size from param2
    int size = strtol(argv[2], NULL, 10);

    // create useful arrays
    int ** numbers = allocate_grid(argv[1], size);
    long *** answer = allocate_array_3d(size);

    // check array
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            calculate(numbers, size, answer[i][j], i, j);
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

    // print largest value
    printf("For this %d x %d grid the largest product of four adjacent numbers is:\n    %li", size, size, sum);
    printf("\nThe factors of this number are:\n    %d X %d X %d X %d\n", a, b, c, d);
    printf("Time it took this process to run:\n    %lf\n", ((double)(end - start) / CLOCKS_PER_SEC));

    // free the malloc'ed memory
    free(numbers);
    free(answer);

    return 0;
}
