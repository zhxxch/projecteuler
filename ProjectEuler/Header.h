#pragma once
#ifdef __cplusplus
extern "C" {
#endif
    void p213_init(void);
    void p213_simul(const int EdgeLen, const int Round,
        const int NumSimul, void* FleaMem, double NumEmpty[]);
    double avg_empty(double NumEmpty[], const int Num);
#ifdef __cplusplus
}
#endif