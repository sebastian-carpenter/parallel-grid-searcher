#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array_generator.h"

/* --- allocation --- */

int allocate_structs(char * file_name, array_information * array_info, int num_arrays, long * answers, int size){

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

    array_info->answers = answers;
    array_info->size = size;

    // fill remaining arrays
    while(num_arrays > 1){
        array_info++;
        num_arrays--;
        // numbers
        array_info->numbers = malloc(sizeof(int) * size * size);
        memcpy(array_info->numbers, numbers, sizeof(int) * size * size);
        // others
        array_info->answers = answers;
        array_info->size = size;
    }

    return 0;
}
