#pragma once

typedef double dtype;
typedef struct squareMatrix
{
    int N;
    dtype* data;
}sqmx;

sqmx createMatrix(int);
void deleteMatrix(sqmx);
void showArray(sqmx a);
sqmx dot(sqmx, sqmx);
sqmx loadMatrix(char*);
void saveMatrix(char*, sqmx);
void calcLU(sqmx, sqmx*, sqmx*);
sqmx inverseL(sqmx);
sqmx inverseU(sqmx);
