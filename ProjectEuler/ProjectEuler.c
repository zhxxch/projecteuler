#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define ASSERTEX_LEVEL 0
#include<assertex.h>
#include"Header.h"

int main(int argc, char *argv[]){
    const int NumSimuls = 10000;
    const int EdgeLen = 30;
    const int NumMoves = 50;
    double *NumEmpty = malloc(sizeof(double)*NumSimuls);
    void* WorkingMem = malloc(
        sizeof(float)*(EdgeLen*2 * EdgeLen*2 + NumMoves));
    p213_simul(EdgeLen, NumMoves, NumSimuls, WorkingMem, NumEmpty);
    double Avg = avg_empty(NumEmpty, NumSimuls);
    printf("Avg. = %f\n", Avg);
    return 0;
}