#include <stdio.h>
#include <stdlib.h>

#include "array_generator.h"

/* --- allocation --- */

int allocate_grid(char * file_name, array_information * array_info){

    int size = array_info->size;
    
    // allocate 2D array as a 1D array
    array_info->numbers = malloc(sizeof(int) * size * size);

    FILE * fptr = fopen(file_name, "r");

    // assign values to array
    if(fptr != NULL){
        for(int i = 0; i < size; i++)
            for(int j = 0; j < size; j++)
                fscanf(fptr, "%d", (array_info->numbers + i * size + j));
    }
    // file is not valid
    else{
        printf("Unable to open file\n");

        free(array_info->numbers);
        fclose(fptr);

        return 1;
    }

    fclose(fptr);

    return 0;
}

void allocate_array_3d(array_information * array_info){

    int size = array_info->size;

    // allocate 3D array as a 1D array
    array_info->answer = malloc(sizeof(long) * size * size * 5);
}
