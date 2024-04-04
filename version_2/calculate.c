#include <stdio.h>

#include "calculate.h"
#include "array_generator.h"

void calculate(array_information * array_info, int i, int j, long * largestAnswer){

    int size = array_info->size;
    int LIMIT = size - 3;

    // this activates when no calculations are necessary for this branch
    // incidentally, failure to return will result in a seg fault
    if(i >= LIMIT && j >= LIMIT)
        return;

    // get a pointer to the appropriate cell offset
    int * numbers = array_info->numbers + (i * size) + j;

    long tempSum, diag1, diag2, vert, horz;
    tempSum = diag1 = diag2 = vert = horz = -1;

    /* 
     * the 5 variables above need to be set to a value unobtainable by
     * the calculations which follow. If you do not set it to an impossible
     * value, or handle it before assigning values at the end, you will
     * end up with seg faults
     */

    // diagonal
    if(i < LIMIT && j < LIMIT){
        // top left to bottom right
        diag1 = numbers[0];
        diag1 *= numbers[size + 1];
        diag1 *= numbers[(2 * size) + 2];
        diag1 *= numbers[(3 * size) + 3];
        // bottom left to top right
        diag2 = numbers[(3 * size)];
        diag2 *= numbers[(2 * size) + 1];
        diag2 *= numbers[size + 2];
        diag2 *= numbers[3];
    }
    // left, right
    if(j < LIMIT){
        horz = numbers[0];
        horz *= numbers[1];
        horz *= numbers[2];
        horz *= numbers[3];
    }
    // up, down
    if (i < LIMIT){
        vert = numbers[0];
        vert *= numbers[size];
        vert *= numbers[(2 * size)];
        vert *= numbers[(3 * size)];
    }

    // find biggest
    tempSum = diag1;

    if(tempSum < diag2)
        tempSum = diag2;

    if(tempSum < horz)
        tempSum = horz;

    if(tempSum < vert)
        tempSum = vert;

    // if the new sum is less, then we don't care about this run
    if(tempSum < largestAnswer[0])
        return;

    largestAnswer[0] = tempSum;

    // assign associated factors
    if(tempSum == diag1){
        largestAnswer[1] = numbers[0];
        largestAnswer[2] = numbers[size + 1];
        largestAnswer[3] = numbers[(2 * size) + 2];
        largestAnswer[4] = numbers[(3 * size) + 3];
    }
    else if(tempSum == diag2){
        largestAnswer[1] = numbers[(3 * size)];
        largestAnswer[2] = numbers[(2 * size) + 1];
        largestAnswer[3] = numbers[size + 2];
        largestAnswer[4] = numbers[3];
    }
    else if(tempSum == horz){
        largestAnswer[1] = numbers[0];
        largestAnswer[2] = numbers[1];
        largestAnswer[3] = numbers[2];
        largestAnswer[4] = numbers[3];
    }
    else if(tempSum == vert){
        largestAnswer[1] = numbers[0];
        largestAnswer[2] = numbers[size];
        largestAnswer[3] = numbers[(2 * size)];
        largestAnswer[4] = numbers[(3 * size)];
    }
}
