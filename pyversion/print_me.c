#include <stdio.h>

void print_me(long *** answer, int size){
    
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

    // print largest value
    printf("For this %d x %d grid the largest product of four adjacent numbers is:\n    %li", size, size, sum);
    printf("\nThe factors of this number are:\n    %d X %d X %d X %d\n", a, b, c, d);
}
