#pragma once
/* Problem 206 */
#include<math.h>
#include<stdlib.h>
#include<stdint.h>
#include<essixtence/check.h>
#include<essixtence/zxcrypto.h>

const long long target = 10203040506070809;
const long long upper_bound = 138902663;
const long long lower_bound = 101010101;

int test_sq(const long long sq){
    long long v[9];
    const long long d[9] = {1ll, 100ll, 10000ll, 1000000ll, 100000000ll, 10000000000ll, 1000000000000ll, 100000000000000ll, 10000000000000000ll};
    const long long hit[9] = {9,8,7,6,5,4,3,2,1};
    for(int i = 0; i< 9; i++){
        v[i] = sq/d[i];
        v[i] = v[i]%10;
    }
    for(int i = 0; i< 9; i++){
        if(v[i] != hit[i])return 0;
    }
    return 1;
}

long long find_sqrt(void){
    long long res = 0, curr_sqrt;
#pragma omp parallel shared(res)
#pragma omp for
    for(curr_sqrt = upper_bound; curr_sqrt > lower_bound; curr_sqrt--){
        if(test_sq(curr_sqrt*curr_sqrt)){
            res = curr_sqrt;
        }
    }
    return res;
}