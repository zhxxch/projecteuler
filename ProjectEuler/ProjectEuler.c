#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define ASSERTEX_LEVEL 0
#include<assertex.h>
#include"Header.h"
const int MB = 1024 * 1024;
int main(int argc, char *argv[]){
    void* WorkingMem = malloc(8 * MB);
    const int ElemNum = 8 * MB / sizeof(unsigned long long);
    long long dt = p213_simul(WorkingMem, ElemNum);
    FILE *fd = fopen("speck10", "wb+");
    fwrite(WorkingMem, sizeof(unsigned long long), ElemNum, fd);
    fclose(fd);
    printf("dt = %lli\n", dt);
    return 0;
}