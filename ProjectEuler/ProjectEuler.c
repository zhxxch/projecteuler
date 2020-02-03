#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define ASSERTEX_LEVEL 0
#include<assertex.h>
#include"Header.h"
#include<time.h>
int main(int argc, char *argv[]){
    const int NumSimuls = 1000;
    const int EdgeLen = 30;
    const int NumMoves = 50;
    double *NumEmpty = malloc(sizeof(double)*NumSimuls);
    void* WorkingMem = malloc(
        sizeof(float)*(EdgeLen*2 * EdgeLen*2 + NumMoves));
    clock_t t0 = clock();
    p213_simul(EdgeLen, NumMoves, NumSimuls, WorkingMem, NumEmpty);
    clock_t t1 = clock();
    double Avg = avg_empty(NumEmpty, NumSimuls);
    printf("Avg. = %f\n", Avg);
    printf("dt = %i\n", t1-t0);
    return 0;
}