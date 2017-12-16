#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define ASSERTEX_LEVEL 0
#include<assertex.h>
#include"Header.h"
const int MB = 1024 * 1024;
int main(int argc, char *argv[]){
    void* WorkingMem = malloc(1024 * MB);
    const int ElemNum = 1024 * MB / sizeof(unsigned long long);
    long long dt = p213_simul(WorkingMem, ElemNum);
    printf("dt = %lli ms\n", dt);
    return 0;
}