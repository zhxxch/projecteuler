/* Simulate */
#include"Header.h"
#include<array>
#include<cmath>
#include<mkl.h>
#include<algorithm>
#include<vector>
typedef std::array<int, 2> Zvec2;
typedef std::array<int, 2> Z_unit_vec2;

Zvec2 flea_one_move(Z_unit_vec2 move_constraint, const float Rand){
    Zvec2 Move = {0,0};
    if(move_constraint[0] == false){
        if(move_constraint[1] == false){
            Move[0] = Rand < 0.25 ? -1 : 1;
            Move[0] = Rand < 0.5 ? Move[0] : 0;
            Move[1] = Rand >= 0.75 ? 1 : -1;
            Move[1] = Rand >= 0.5 ? Move[1] : 0;
        } else{
            Move[0] = Rand < 1.0f / 3.0f ? -1 : 1;
            Move[0] = Rand < 2.0f / 3.0f ? Move[0] : 0;
            Move[1] = Rand >= 2.0f / 3.0f ? move_constraint[1] : 0;
        }
    } else{
        if(move_constraint[1] == false){
            Move[0] = Rand < 1.0f / 3.0f ? move_constraint[0] : 0;
            Move[1] = Rand >= 2.0f / 3.0f ? 1 : -1;
            Move[1] = Rand >= 1.0f / 3.0f ? Move[1] : 0;
        } else{
            Move[0] = Rand < 0.5f ? move_constraint[0] : 0;
            Move[1] = Rand >= 0.5f ? move_constraint[1] : 0;
        }
    }
    return Move;
}
Zvec2 flea_moving(
    const Zvec2 InitPosit,
    const float RandomFracs[],
    const int EdgeLen,
    const int MovesCount){
    if(MovesCount == 0)return InitPosit;
    Z_unit_vec2 MoveConstraint;
    MoveConstraint[0] = InitPosit[0] == 0 ? 1 : 0;
    MoveConstraint[0] = InitPosit[0] == (EdgeLen - 1) ? -1 : 0;
    MoveConstraint[1] = InitPosit[1] == 0 ? 1 : 0;
    MoveConstraint[1] = InitPosit[1] == (EdgeLen - 1) ? -1 : 0;
    Zvec2 Movement = flea_one_move(MoveConstraint, *RandomFracs);
    return flea_moving({InitPosit[0] + Movement[0], InitPosit[1] + Movement[1]},
        RandomFracs + 1, EdgeLen, MovesCount - 1);
}
#include<assertex.h>
void flea_init_pos(const int EdgeLen, Zvec2 Posit[]){
    for(int _1 = 0; _1 < EdgeLen; _1++){
        for(int _2 = 0; _2 < EdgeLen; _2++){
            Posit[_1*EdgeLen + _2] = {_1, _2};
        }
    }
}
int count_empty_cell(const int EdgeLen, Zvec2 FleaPosits[]){
    std::sort(FleaPosits, FleaPosits + EdgeLen*EdgeLen,
        [](const Zvec2 a, const Zvec2 b){
        return a[0] == b[0] ? (a[0] - b[0]) : (a[1] - b[1]);
    });
    std::vector<Zvec2> UniqueFleaPosit;
    UniqueFleaPosit.reserve(EdgeLen*EdgeLen);
    std::vector<Zvec2>::iterator ZvecArrIt
        = std::unique_copy(FleaPosits, FleaPosits + EdgeLen*EdgeLen,
            UniqueFleaPosit.begin(), [](const Zvec2 a, const Zvec2 b){
        return a == b;
    });
    return EdgeLen*EdgeLen
        - static_cast<int>(std::distance(UniqueFleaPosit.begin(), ZvecArrIt));
}
VSLStreamStatePtr VslStream;
void p213_init(void){
    if(vslNewStream(&VslStream, VSL_BRNG_NONDETERM, 99)
        != VSL_STATUS_OK){
        exit(999);
    } else return;
}
void p213_simul(const int EdgeLen, const int Round,
    const int NumSimul, void* FleaMem, double NumEmpty[]){
    if(NumSimul == 0)return;
    Zvec2 *FleaPosits = static_cast<Zvec2*>(FleaMem);
    float *RandomMem = reinterpret_cast<float*>(
        FleaPosits + EdgeLen*EdgeLen);
    flea_init_pos(EdgeLen, FleaPosits);
    const int NumRandomFracs = Round;
    for(int Flea_n = 0; Flea_n < EdgeLen*EdgeLen; Flea_n++){
        vsRngUniform(VSL_RNG_METHOD_UNIFORM_STD, VslStream,
            NumRandomFracs, RandomMem, 0.0f, 1.0f);
        FleaPosits[Flea_n]
            = flea_moving(
                FleaPosits[Flea_n], RandomMem, EdgeLen, Round);
    }
    *NumEmpty = count_empty_cell(EdgeLen, FleaPosits);
    return p213_simul(EdgeLen, Round, NumSimul - 1, FleaMem, NumEmpty + 1);
}
double avg_empty(double NumEmpty[], const int Num){
    return cblas_dasum(Num, NumEmpty, 1) / Num;
}