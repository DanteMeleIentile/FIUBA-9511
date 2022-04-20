#include <stdio.h>
#include <math.h>


#define DIMENSION 2

float A[DIMENSION] = {2, 1};
float B[DIMENSION] = {1, 2};
float P[DIMENSION] = {2, 2};


void resta_vectores(float R[], float P1[], float P2[]){
    float R[0] = P1[0]-P2[0];
    float R[1] = P1[1]-P2[1];
}


/* int producto_resta(float A[], float B[], float P[]){
    return resta_vectores(P, A) * resta_vectores(B, A)
} */


int main(void){
    float A[2] = {72, 1};
    float B[2] = {1, 2};
    float R[DIMENSION];

    resta_vectores(R, A, B);
    printf ("la resta es: %f\n", R[0]);
    printf ("la resta es: %f\n", R[1]);
    return 0;
}