#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"Header.h"
#define FORCE_CHECK
#include<check.h>
int main(int argc, char *argv[]){
    if(argc < 2){
        puts("R Missing.");
        return 0;
    }
    CHECK(dots_in_circle(8) == 5)(" = %lli\n", dots_in_circle(5));
    CHECK(dots_in_circle(12) == 12)(" = %lli\n", dots_in_circle(12));
    CHECK(dots_in_circle(16) == 21)(" = %lli\n", dots_in_circle(16));
    printf("Ans = %lli\n", N(atoll(argv[1])));
    return 0;
}