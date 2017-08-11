/*
 *
                        +

                     +  +  +

                  +  +  +  +  +

               +  +  +  +  +  +  +

            +  +  +  +  +  +  +  +  +

         +  +  +  +  +  +  +  +  +  +  +

      +  +  +  +  +  +  +  +  +  +  +  +  +

   +  +  +  +  +  +  +  +  +  +  +  +  +  +  +

+  +  +  +  +  +  +  +  +  +  +  +  +  +  +  +  +

   +  +  +  +  +  +  +  +  +  +  +  +  +  +  +

      +  +  +  +  +  +  +  +  +  +  +  +  +

         +  +  +  +  +  +  +  +  +  +  +

            +  +  +  +  +  +  +  +  +

               +  +  +  +  +  +  +

                  +  +  +  +  +

                     +  +  +

                        +
 */

/* ProjectEuler
   Problem No 210
    __ |  \   /   __|
      /     /    |
    ___|  _/ _\ \___|  */

#include<math.h>
#include<Eigen/Dense>
#include<stdlib.h>
#define FORCE_CHECK
#include<check.h>
#include"Header.h"

long long dist_y_centre(const long long X, const double CiR2, const double Central){
    const double A = Central - X;
    const double B2 = CiR2 - A*A;
    const double B = sqrt(B2);
    return (static_cast<long long>(ceil(B)) - 1);
}
long long dots_in_circle(const long long r){

    const long long InnerSquareR = r / 4;
    const double CiR2 = r*r / 32.0;//(sqrt(2)*r/8)^2
    const double Central = InnerSquareR / 2.0;
    const long long DotsInCiROnOC = InnerSquareR + 1;
    const long long DotsInnerSquare = (InnerSquareR + 1)*(InnerSquareR + 1) - 4;
    const long long LeftX = static_cast<long long>(-floor((sqrt(2) - 1)*(Central)));
    const long long RightX = InnerSquareR - LeftX;
    long long DotsInCiRegion = 0;
    for(long long X = LeftX; X <= RightX; X++){
        DotsInCiRegion += dist_y_centre(X, CiR2, Central);
    }
    //long long DotsOnCentralLine = 0;
    //const long long DotsToCentral = dist_y_centre(Central, CiR2, Central) - (InnerSquareR / 2 - 1);
    const long long DotsOnCentralH = (Central - static_cast<long long>(Central) == 0) ? (RightX - LeftX + 1) : 0;
    return DotsInCiRegion * 2 + DotsOnCentralH;
}
long long N(const long long r){
    const long long Dots = r*r + (r + 1)*(r + 1);
    const long long DotsOnOC = r + 1;
    const long long DotsInOC = r / 4 + 1;
    const long long DotsInCircleInOC = r / 4 - 1;
    const long long DotsInside = (r / 4)*((2 * r + 1)) + (r + 1);
    long long DotsInCircle = dots_in_circle(r);
    DotsInCircle = DotsInCircle > 0 ? DotsInCircle : 0;
    //CHECK(DotsInCircle == 5)(" = %lli\n", DotsInCircle);
    return Dots - DotsInside - DotsOnOC + DotsInOC + DotsInCircle - DotsInCircleInOC;
}

