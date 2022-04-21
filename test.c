#include <stdio.h>
#include <math.h>

void resta_vectores (double resta[], double v1[][2], int n){
    for (int i = 0; i < n; i++){
        resta[i] = v1[i+1][] - v1[i][];
    }
}



int main (void){
    double vectores[][2] = {{1, 1}, {3, 5}};
    resta_vectores (resta, vectores, n) 
}

/* (1; 1)
(3; 5)
(2; 4) */