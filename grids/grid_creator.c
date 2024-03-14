#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char * argv[]){

    // exclusive
    int MAX = 9750;

    if(argc != 3){
        printf("Too many or too few arguments.");
        return 1;
    }

    int size = strtol(argv[2], NULL, 10);
    int value;

    FILE * fptr = fopen(argv[1], "w");

    srand(time(NULL));
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size - 1; j++){
            value = rand() % MAX;
            fprintf(fptr, "%d ", value);
        }
        value = rand() % MAX;
        fprintf(fptr, "%d\n", value);
    }

    fclose(fptr);

    return 0;
}
