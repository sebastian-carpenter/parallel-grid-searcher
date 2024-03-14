#include <stdio.h>
#include <stdlib.h>

void free_me_2d(int ** d2_array){
    free(d2_array);
}

void free_me_3d(long *** d3_array){
    free(d3_array);
}
