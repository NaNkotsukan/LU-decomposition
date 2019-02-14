#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"


int main(int argc, char const *argv[])
{
    sqmx A = loadMatrix("A.csv");
    showArray(A);
    sqmx L, U;
    calcLU(A, &L, &U);
    showArray(L);
    showArray(U);
    sqmx L_inverse = inverseL(L);
    sqmx U_inverse = inverseU(U);
    sqmx A_inverse = dot(U_inverse, L_inverse);
    showArray(A_inverse);
    showArray(dot(A, A_inverse));
    saveMatrix("L.csv", L);
    saveMatrix("U.csv", U);
    saveMatrix("L_inverse.csv", L_inverse);
    saveMatrix("U_inverse.csv", U_inverse);
    saveMatrix("A_inverse.csv", A_inverse);
    return 0;
}