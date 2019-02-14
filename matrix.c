#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

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

void showArray(sqmx array){
    for(int i=0;i<array.N;++i){
        for(int j=0;j<array.N;++j){
            printf("% 5lf ", array.data[array.N*i+j]);
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
    for(int i = 0; i < a.N; ++i)
    {
        for(int j = 0; j < a.N-1; ++j)
        {
            fprintf(fp, "%lf ", a.data[i]);
        }
        fprintf(fp, "%lf\n", a.data[i]);
    }
}

void calcLU(sqmx A, sqmx *L, sqmx *U){
    const int N = A.N;
    // const int N = L->N = U->N = A.N;
    // L->data = (dtype*)calloc(N*N, dsize);
    // U->data = (dtype*)calloc(N*N, dsize);
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
