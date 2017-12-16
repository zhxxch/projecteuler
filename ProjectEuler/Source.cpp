/* Simulate */
#include"Header.h"
#include<array>
#include<cmath>
#include<algorithm>
#include<random>
#include<chrono>
#include<zxcrypto.h>
#include<zxnoise.h>


using heure = std::chrono::high_resolution_clock;
using ms = std::chrono::milliseconds;
long long p213_simul(unsigned long long *Mem, const int Num){
    uint64_t Key[2] = {0x0706050403020100ull, 0x0f0e0d0c0b0a0908ull};
    uint64_t Pt[2] = {0x7469206564616d20ull, 0x6c61766975716520ull};
    uint64_t RoundKeys[32];
    heure::time_point t0 = heure::now();
    unsigned long long r64;
    for(int i = 0; i < Num; i++){
        r64 = ru64_rdrand();
    }
    Mem[0] = r64;
    heure::time_point t1 = heure::now();
    return std::chrono::duration_cast<ms>(t1 - t0).count();
}