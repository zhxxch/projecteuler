/* Simulate */
#include"Header.h"
#include<array>
#include<cmath>
#include<algorithm>
#include<random>
#include<chrono>
#include<zxnoise.h>
#include<emmintrin.h>
inline void speck128u128sse(uint64_t Ct[2],
    const uint64_t Pt[2],
    const uint64_t Key[2]){
    __m128i CtKeySr = _mm_loadu_si128((const __m128i*)Pt);
    __m128i CtKeySl = _mm_loadu_si128((const __m128i*)Key);
    __m128i CtKeyHi128 = _mm_unpackhi_epi64(CtKeySr, CtKeySl);
    __m128i CtKeyLo128 = _mm_unpacklo_epi64(CtKeySr, CtKeySl);
    __m128i RoundKey128 = _mm_set_epi64x(0, 0);
    __m128i RoundKeyP1128 = _mm_set_epi64x(1, 0);
    for(int i = 0; i < 32; i++){
        RoundKey128 = _mm_unpackhi_epi64(CtKeyLo128, RoundKey128);
        CtKeySr = _mm_srli_epi64(CtKeyHi128, 8);
        CtKeySl = _mm_slli_epi64(CtKeyHi128, 56);
        CtKeyHi128 = _mm_xor_si128(CtKeySr, CtKeySl);
        CtKeyHi128 = _mm_add_epi64(CtKeyHi128, CtKeyLo128);
        CtKeyHi128 = _mm_xor_si128(CtKeyHi128, RoundKey128);
        CtKeySr = _mm_srli_epi64(CtKeyLo128, 61);
        CtKeySl = _mm_slli_epi64(CtKeyLo128, 3);
        CtKeyLo128 = _mm_xor_si128(CtKeySr, CtKeySl);
        CtKeyLo128 = _mm_xor_si128(CtKeyLo128, CtKeyHi128);
        RoundKey128 = _mm_add_epi64(RoundKey128, RoundKeyP1128);
    }
    CtKeySr = _mm_unpacklo_epi64(CtKeyLo128, CtKeyHi128);
    _mm_storeu_si128((__m128i*)Ct, CtKeySr);
}
void speckNx128u128(uint64_t Out[], const uint64_t In[],
    const uint64_t Key[2], const int Num){
    for(int i = 0; i < Num; i += 2){
        speck128u128sse(Out + i, In + i, Key);
    }
}
using heure = std::chrono::high_resolution_clock;
using ms = std::chrono::milliseconds;
long long p213_simul(unsigned long long *Mem, const int Num){
    uint64_t Key[2] = {0x0706050403020100ull, 0x0f0e0d0c0b0a0908ull};
    uint64_t Pt[2] = {0x7469206564616d20ull, 0x6c61766975716520ull};
    uint64_t Ct[2];
    speckNx128u128(Ct, Pt, Key, 2);
    heure::time_point t0 = heure::now();
    speckNx128u128(Mem, Mem, Key, Num);
    heure::time_point t1 = heure::now();
    printf("Ct: %llx %llx\n", Ct[0], Ct[1]);
    return std::chrono::duration_cast<ms>(t1 - t0).count();
}