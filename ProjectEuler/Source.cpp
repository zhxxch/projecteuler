/* Simulate */
#include"Header.h"
#include<array>
#include<cmath>
#include<algorithm>
#include<random>
#include<chrono>
#include<zxnoise.h>
#include<immintrin.h>
inline void speck128u128(uint64_t Ct[2],
    const uint64_t Pt[2], const uint64_t Key[2]){
    __m128i CtKeySr = _mm_loadu_si128((const __m128i*)Pt);
    __m128i CtKeySl = _mm_loadu_si128((const __m128i*)Key);
    __m128i CtKeyHi = _mm_unpackhi_epi64(CtKeySr, CtKeySl);
    __m128i CtKeyLo = _mm_unpacklo_epi64(CtKeySr, CtKeySl);
    __m128i RoundKey = _mm_set_epi64x(0, 0);
    __m128i RoundKeyStep = _mm_set_epi64x(1, 0);
    for(int i = 0; i < 32; i++){
        RoundKey = _mm_unpackhi_epi64(CtKeyLo, RoundKey);
        CtKeySr = _mm_srli_epi64(CtKeyHi, 8);
        CtKeySl = _mm_slli_epi64(CtKeyHi, 56);
        CtKeyHi = _mm_xor_si128(CtKeySr, CtKeySl);
        CtKeyHi = _mm_add_epi64(CtKeyHi, CtKeyLo);
        CtKeyHi = _mm_xor_si128(CtKeyHi, RoundKey);
        CtKeySr = _mm_srli_epi64(CtKeyLo, 61);
        CtKeySl = _mm_slli_epi64(CtKeyLo, 3);
        CtKeyLo = _mm_xor_si128(CtKeySr, CtKeySl);
        CtKeyLo = _mm_xor_si128(CtKeyLo, CtKeyHi);
        RoundKey = _mm_add_epi64(RoundKey, RoundKeyStep);
    }
    CtKeySr = _mm_unpacklo_epi64(CtKeyLo, CtKeyHi);
    _mm_storeu_si128((__m128i*)Ct, CtKeySr);
}
inline void speck4x128u128(uint64_t Ct[8],
    const uint64_t Pt[8], const uint64_t Key[32]){
    __m256i CtSr = _mm256_loadu_si256((const __m256i*)Pt);
    __m256i CtSl = _mm256_loadu_si256((const __m256i*)(Pt+4));
    __m256i CtHi = _mm256_unpackhi_epi64(CtSr, CtSl);
    __m256i CtLo = _mm256_unpacklo_epi64(CtSr, CtSl);
    for(int i = 0; i < 32; i++){
        CtSr = _mm256_srli_epi64(CtHi, 8);
        CtSl = _mm256_slli_epi64(CtHi, 56);
        CtHi = _mm256_xor_si256(CtSr, CtSl);
        CtHi = _mm256_add_epi64(CtHi, CtLo);
        CtHi = _mm256_xor_si256(CtHi,
            _mm256_set1_epi64x(Key[i]));
        CtSr = _mm256_srli_epi64(CtLo, 61);
        CtSl = _mm256_slli_epi64(CtLo, 3);
        CtLo = _mm256_xor_si256(CtSr, CtSl);
        CtLo = _mm256_xor_si256(CtLo, CtHi);
    }
    CtSr = _mm256_unpacklo_epi64(CtLo, CtHi);
    CtSl = _mm256_unpackhi_epi64(CtLo, CtHi);
    _mm256_storeu_si256((__m256i*)Ct, CtSr);
    _mm256_storeu_si256((__m256i*)(Ct+4), CtSr);
}
inline void speck128key32(uint64_t RoundKeys[32], const uint64_t Key[2]){
    uint64_t KW[2] = {Key[0], Key[1]};
    for(uint64_t i = 0; i < 32; i++){
        RoundKeys[i] = KW[0];
        KW[1] = (((KW[1] >> 8) ^ (KW[1] << 56)) + KW[0]) ^ i;
        KW[0] = ((KW[0] << 3) ^ (KW[0] >> 61)) ^ KW[1];
    }
}
void speckNx128u128(uint64_t Out[], const uint64_t In[],
    const uint64_t Key[2], const int Num){
    for(int i = 0; i < Num; i += 2){
        speck128u128(Out + i, Key);
    }
}
void speckNx4x128u128(uint64_t Out[], const uint64_t In[],
    const uint64_t Key[32], const int Num){
    for(int i = 0; i < Num; i += 8){
        speck4x128u128(Out + i, In+i, Key);
    }
}
using heure = std::chrono::high_resolution_clock;
using ms = std::chrono::milliseconds;
long long p213_simul(unsigned long long *Mem, const int Num){
    uint64_t Key[2] = {0x0706050403020100ull, 0x0f0e0d0c0b0a0908ull};
    uint64_t Pt[2] = {0x7469206564616d20ull, 0x6c61766975716520ull};
    Mem[0] = 0x7469206564616d20ull;
    Mem[1] = 0x6c61766975716520ull;
    uint64_t RoundKeys[32];
    speck128key32(RoundKeys, Key);
    heure::time_point t0 = heure::now();
    speckNx4x128u128(Mem, Mem, RoundKeys, Num);
    heure::time_point t1 = heure::now();
    printf("Ct: %llx %llx\n", Mem[0], Mem[1]);
    return std::chrono::duration_cast<ms>(t1 - t0).count();
}