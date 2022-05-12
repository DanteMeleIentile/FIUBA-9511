#include <stdio.h>

#define N 4

void compl_v_0(int *v, size_t n){
    for (int i = 0; i < n; i++){
        *(v + i) = 0;
    }
}

void suma_componentes(int *v, size_t n, int *r){
    int temp = 0;
    for (int i = 0; i < n; i++){
        temp = temp + *(v + i);
    }
    *r = temp;
}


void varianza(int *v, size_t n, int *r){
    int temp = 0;
    for (int i = 0; i < n; i++){
        temp = temp + *(v + i);
    }
    *r = temp / N;
    printf ("media = %d\n", *r);
    for (int i = 0; i < n; i++){
        if (*r < *(v + i)){
            *r = *(v + i);
        }
    }
    *r = *r - temp / N;
}


int main (void){
    int v[N] = {1, 2, 3, 10};

    /* compl_v_0(&v[0], N);
    for (int i = 0; i < N; i++){
        printf("%d, ", v[i]);
    }
    printf("\n"); */


    /* int r = 0;
    suma_componentes(&v[0], N, &r);
    printf("r vale: %d\n", r); */

    int r = 0;
    varianza(&v[0], N, &r);
    printf("la variaza vale: %d\n", r);
    
    return 0;
}