#pragma once
/* Problem 202 */
#include<math.h>
#include<stdlib.h>
#include<essixtence/check.h>
#include<essixtence/zxcrypto.h>

inline long long gcd(const long long R, const long long V){
    if(R*V == 0)return R+V;
    return (R>V ? gcd(R-V, V) : gcd(R, V-R));
}

inline int is_inner(long long R, long long V){
    return V*2 < R;
}
inline int is_c_vertex(long long R, long long V){
    return (R+V) % 3 == 0;
}
inline long long count_bounce(long long R, long long V){
    const long long RsideCount = V - 1;
    const long long VsideCound = R - 1;
    const long long RVsideCount = R - V - 1;
    return RsideCount + VsideCound + RVsideCount;
}
inline long long count_ConR(const long long R){
    const long long NearestV = (3 - R%3)%3;
    const long long MaxV = (R+1)/2-1;
    const long long Count = (MaxV-NearestV)/3+1;
    long long Discount = 0;
    long long V = 0;
#pragma omp parallel shared(Discount)
#pragma omp for reduction(+: Discount)
    for(V = NearestV; V<=MaxV; V+=3){
        if(gcd(R, V)>1)Discount += 1;
    }
    
    return 2*(Count - Discount);
}
inline long long bounce_R(const long long Bounce){
    return (Bounce+3)/2;
}