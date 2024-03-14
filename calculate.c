#include <stdio.h>

#include "calculate.h"
#include "array_generator.h"

void calculate(array_information * array_info, int i, int j){

    int size = array_info->size;
    int LIMIT = size - 3;

    int * numbers = array_info->numbers;
    long * answer = &array_info->answer[i * size * 5 + j * 5];

    // this activates when no calculations are necessary for this branch
    if(i >= LIMIT && j >= LIMIT){
        answer[0] = 0;
        answer[1] = 0;
        answer[2] = 0;
        answer[3] = 0;
        answer[4] = 0;
        return;
        // incidentally, failure to return will result in a seg fault
    }

    long tempSum;
    long diag1, diag2, vert, horz;
    tempSum = diag1 = diag2 = vert = horz = 0;

    // diagonal
    if(i < LIMIT && j < LIMIT){
        // top left to bottom right
        diag1 = numbers[i * size + j];
        diag1 *= numbers[(i + 1) * size + (j + 1)];
        diag1 *= numbers[(i + 2) * size + (j + 2)];
        diag1 *= numbers[(i + 3) * size + (j + 3)];
        // bottom left to top right
        diag2 = numbers[(i + 3) * size + j];
        diag2 *= numbers[(i + 2) * size + (j + 1)];
        diag2 *= numbers[(i + 1) * size + (j + 2)];
        diag2 *= numbers[i * size + (j + 3)];
    }
    // left, right
    if(j < LIMIT){
        horz = numbers[i * size + j];
        horz *= numbers[i * size + (j + 1)];
        horz *= numbers[i * size + (j + 2)];
        horz *= numbers[i * size + (j + 3)];
    }
    // up, down
    if (i < LIMIT){
        vert = numbers[i * size + j];
        vert *= numbers[(i + 1) * size + j];
        vert *= numbers[(i + 2) * size + j];
        vert *= numbers[(i + 3) * size + j];
    }

    // find biggest
    tempSum = diag1;

    if(tempSum < diag2)
        tempSum = diag2;

    if(tempSum < horz)
        tempSum = horz;

    if(tempSum < vert)
        tempSum = vert;

    answer[0] = tempSum;

    // if tempSum ends up as 0 a seg fault will occur, this deals with it
    if(tempSum == 0){
        answer[1] = 0;
        answer[2] = 0;
        answer[3] = 0;
        answer[4] = 0;
        return;
    }

    // assign associated factors
    if(tempSum == diag1){
        answer[1] = numbers[i * size + j];
        answer[2] = numbers[(i + 1) * size + (j + 1)];
        answer[3] = numbers[(i + 2) * size + (j + 2)];
        answer[4] = numbers[(i + 3) * size + (j + 3)];
    }
    else if(tempSum == diag2){
        answer[1] = numbers[(i + 3) * size + j];
        answer[2] = numbers[(i + 2) * size + (j + 1)];
        answer[3] = numbers[(i + 1) * size + (j + 2)];
        answer[4] = numbers[i * size + (j + 3)];
    }
    else if(tempSum == horz){
        answer[1] = numbers[i * size + j];
        answer[2] = numbers[i * size + (j + 1)];
        answer[3] = numbers[i * size + (j + 2)];
        answer[4] = numbers[i * size + (j + 3)];
    }
    else if(tempSum == vert){
        answer[1] = numbers[i * size + j];
        answer[2] = numbers[(i + 1) * size + j];
        answer[3] = numbers[(i + 2) * size + j];
        answer[4] = numbers[(i + 3) * size + j];
    }
}
