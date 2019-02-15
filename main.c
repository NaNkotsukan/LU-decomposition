#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"


int main(int argc, char const *argv[])
{
    sqmx A, L, U, A_inverse, L_inverse, U_inverse;
    A = loadMatrix("A.txt");
    calcLU(A, &L, &U);
    L_inverse = inverseL(L);
    U_inverse = inverseU(U);
    A_inverse = dot(U_inverse, L_inverse);
    
    printf(" matrix A\n");
    showArray(A);
    printf(" matrix L\n");
    showArray(L);
    printf(" matrix U\n");
    showArray(U);
    printf(" matrix A inverse\n");
    showArray(A_inverse);
    printf(" matrix L inverse\n");
    showArray(L_inverse);
    printf(" matrix U inverse\n");
    showArray(U_inverse);
    printf(" matrix A*A^-1\n");
    showArray(dot(A, A_inverse));
    saveMatrix("A_inverse.txt", A_inverse);
    deleteMatrix(A);
    deleteMatrix(L);
    deleteMatrix(U);
    deleteMatrix(A_inverse);
    deleteMatrix(L_inverse);
    deleteMatrix(U_inverse);
    return 0;
}