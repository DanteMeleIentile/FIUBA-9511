#include <stdio.h>
#include <math.h>
#define DIMENSION 2

void resta_vectores (int d, double resta[][d], double **v1, int n){
    for (int i = 0; i < n-1; i++){
        for (int j = 0; j < d; j++){
            resta[i][j] = v1[i+1][j] - v1[i][j];
            printf("%f, ", resta[i][j]);
        }
        printf("\n");
    }
}

int main (void){
    double vectores[][DIMENSION] = {{1, 1}, {3, 5}, {2, 2}, {4, 2}};
    int n = sizeof(vectores) / sizeof(vectores[0]);
    double resta[n-1][DIMENSION];
    resta_vectores (resta, (double**)vectores, n, DIMENSION); 
}