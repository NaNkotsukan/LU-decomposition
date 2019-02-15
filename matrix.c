#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>

#include "matrix.h"

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
const int dsize = sizeof(dtype);


sqmx createMatrix(int N){
    sqmx a;
    a.N=N;
    a.data = (dtype*)calloc(N*N, dsize);
    return a;
}

void deleteMatrix(sqmx a){
    free(a.data);
}

void showArray(sqmx a){
    double before = DBL_MIN, after = DBL_MAX;
    char f[10];
    for(int i = 0; i < a.N*a.N; ++i)
    {
        before = max(before, fabs(a.data[i]));
        double t = fabs(a.data[i]);
        after = min(after, t==0 ? 1 : fabs(a.data[i]));
    }
    int fuga = (int)log10(before);
    int hoge = -(int)log10(after);
    snprintf(f, 12, "%%%d.%dlf", fuga+hoge+6, max(hoge+2, 2-fuga));
    printf(" N = %d\n", a.N);    
    for(int i = 0; i < a.N; ++i)
    {
        for(int j = 0; j < a.N; ++j)
        {
            
            printf(f, a.data[i*a.N+j]);
        }
        printf("\n");
    }
    printf("\n");
}

sqmx dot(sqmx a, sqmx b){
    sqmx c = createMatrix(a.N);
    for(int i=0;i<a.N;++i){
        for(int j=0;j<a.N;++j){
            dtype hoge = 0;
            for(int k = 0; k < a.N; ++k)
            {
                hoge+=a.data[i*a.N+k]*b.data[k*b.N+j];
            }
            c.data[i*c.N+j]=hoge;
        }
    }
    return c;
}

sqmx loadMatrix(char *filepass){
    FILE *fp = fopen( filepass, "r" );
    int N;
    fscanf(fp, "%d", &N);
    sqmx a = createMatrix(N);
    double hoge;
    for(int i=0;i<N*N;++i){
        fscanf(fp, "%lf", &hoge);
        a.data[i] = hoge;
    }
    return a;
}

void saveMatrix(char *filepass, sqmx a){
    FILE *fp = fopen( filepass, "w" );
    fprintf(fp, "%d\n", a.N);  
    double before = DBL_MIN, after = DBL_MAX;
    char f[10];
    for(int i = 0; i < a.N*a.N; ++i)
    {
        before = max(before, fabs(a.data[i]));
        double t = fabs(a.data[i]);
        after = min(after, t==0 ? 1 : fabs(a.data[i]));
    }
    int fuga = (int)log10(before);
    int hoge = -(int)log10(after);
    snprintf(f, 12, "%%%d.%dlf", fuga+hoge+6, max(hoge+2, 2-fuga));
    for(int i = 0; i < a.N; ++i)
    {
        for(int j = 0; j < a.N; ++j)
        {
            
            fprintf(fp, f, a.data[i*a.N+j]);
        }
        fprintf(fp, "\n");
    }
}

void calcLU(sqmx A, sqmx *L, sqmx *U){
    const int N = A.N;
    *L = createMatrix(A.N);
    *U = createMatrix(A.N);

    memcpy(U->data, A.data, dsize*A.N);
    L->data[0] = (dtype)1;

    for(int i = 1; i < N; ++i)
    {
        L->data[i*(N+1)] = (dtype)1;

        for(int j = 0; j < N; ++j)
        {
            if(j < i){
                dtype l = (dtype)0;
                for(int k = 0; k < j; k++)
                {
                    l+=L->data[i*N+k]*U->data[k*N+j];
                }
                L->data[i*N+j] = (A.data[i*N+j]-l)/U->data[j*(N+1)];
            }
            else
            {
                dtype u = (dtype)0;
                for(int k = 0; k < i; k++)
                {
                    u+=L->data[i*N+k]*U->data[k*N+j];
                }
                U->data[i*N+j] = (A.data[i*N+j]-u);
            }

        }
        
    }

}

sqmx inverseL(sqmx L){
    sqmx L_inverse = createMatrix(L.N);
    for(int i = 0; i < L.N; ++i)
    {
        L_inverse.data[i*(L.N+1)] = 1;
        for(int j = 0; j < i; ++j)
        {
            dtype l = (dtype)0;
            for(int k = j; k < i; ++k){
                l+=L.data[i*L.N+k]*L_inverse.data[k*L.N+j];
            }
            L_inverse.data[i*L.N+j] = -l;
        }
    }
    return L_inverse;
}

sqmx inverseU(sqmx U){
    sqmx U_inverse = createMatrix(U.N);
    for(int i = 0; i < U.N; ++i)
    {
        U_inverse.data[i*(U.N+1)] = 1/U.data[i*(U.N+1)];
        for(int j = i+1; j < U.N; ++j)
        {
            dtype u = (dtype)0;
            for(int k = i; k < j; ++k){
                u+=U_inverse.data[i*U.N+k]*U.data[k*U.N+j];
            }
            U_inverse.data[i*U.N+j] = -u/U.data[j*(U.N+1)];
        }
    }
    return U_inverse;
}
