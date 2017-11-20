#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define ASSERTEX_LEVEL 0
#include<assertex.h>
#include"Header.h"
const int MB = 1024 * 1024;
int main(int argc, char *argv[]){
    void* WorkingMem = malloc(1024 * MB);
    long long dt = p213_simul(WorkingMem, 1024 * MB / sizeof(unsigned long long));
    printf("dt = %lli\n", dt);
    return 0;
}