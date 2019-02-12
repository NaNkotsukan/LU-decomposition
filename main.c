#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

typedef double dtype;
const int dsize = sizeof(dtype);

void showArray(dtype *array, int N){
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            printf("% 5lf ", array[N*i+j]);
        }
        printf("\n");
    }
    printf("\n");
}


void dot(dtype *a, dtype *b, dtype *c, int N){
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            dtype hoge = 0;
            for(int k = 0; k < N; ++k)
            {
                hoge+=a[i*N+k]*b[k*N+j];
            }
            c[i*N+j]=hoge;
        }
    }
}

int main(int argc, char const *argv[])
{
    int N;
    scanf("%d", &N);
    dtype* A = (dtype*)calloc(N*N, dsize);
    dtype* L = (dtype*)calloc(N*N, dsize);
    dtype* U = (dtype*)calloc(N*N, dsize);

    if(A==NULL||L==NULL||U==NULL){
        printf("memory error\n");
        return 0;
    }

    double t;
    for(int i = 0; i < N*N ; ++i){
        scanf("%lf", &t);
        A[i] = (dtype)t;
    }

    for(int i = 0; i < N*N; i += N + 1){
    }
    memcpy(U, A, dsize*N);
    L[0] = (dtype)1;

    for(int i = 1; i < N; ++i)
    {
        L[i*(N+1)] = (dtype)1;

        for(int j = 0; j < N; ++j)
        {
            if(j < i){
                dtype l = (dtype)0;
                for(int k = 0; k < j; k++)
                {
                    l+=L[i*N+k]*U[k*N+j];
                }
                L[i*N+j] = (A[i*N+j]-l)/U[j*(N+1)];
            }
            else
            {
                dtype u = (dtype)0;
                for(int k = 0; k < i; k++)
                {
                    u+=L[i*N+k]*U[k*N+j];
                }
                U[i*N+j] = (A[i*N+j]-u);
            }

        }
        
    }

    dtype* L_inverse = (dtype*)calloc(N*N, dsize);
    dtype* U_inverse = (dtype*)calloc(N*N, dsize);

    
    for(int i = 0; i < N; ++i)
    {
        L_inverse[i*(N+1)] = 1;
        for(int j = 0; j < i; ++j)
        {
            dtype l = (dtype)0;
            for(int k = j; k < i; ++k){
                l+=L[i*N+k]*L_inverse[k*N+j];
            }
            L_inverse[i*N+j] = -l;
        }
    }
    
    for(int i = 0; i < N; ++i)
    {
        U_inverse[i*(N+1)] = 1/U[i*(N+1)];
        for(int j = i+1; j < N; ++j)
        {
            dtype u = (dtype)0;
            for(int k = i; k < j; ++k){
                u+=U_inverse[i*N+k]*U[k*N+j];
            }
            U_inverse[i*N+j] = -u/U[j*(N+1)];
        }
    }


    showArray(A, N);
    showArray(L, N);
    showArray(U, N);
    showArray(U_inverse, N);

    
    dtype* test = (dtype*)calloc(N*N, dsize);
    dot(U_inverse, L_inverse, test, N);
    showArray(test, N);
    
    return 0;
}