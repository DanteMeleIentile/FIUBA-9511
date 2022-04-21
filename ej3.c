#include <stdio.h>
#include <math.h>
//DIMENTSION -1

/* double distancia_punto_a_polilinea(const float polilinea[][2], size_t n, float px, float py);{

} */

/* void resta_vectores (double resta[], double v1[], double v2[], int n){
    for (int i = 0; i < n; i++){
        resta[i] = v2[i] - v1[i];
    }
} */

/* void resta_vectores (double resta[2], double v1[], double v2[], int n){
    for (int i = 0; i < n; i++){
        resta[i] = v2[i] - v1[i];
    }
} */

double prod_interno (double v1[], double v2[]){
    double prod_x = v1[0] * v2[0];
    double prod_y = v1[1] * v2[1];
    return prod_x + prod_y;
}

int main (void){
    //float polilinea[][2] = {{0, 1}, {1, 3}, {1, 5}};
    //double puntos[][2] = {{1, 1}, {5, 3}};
    double v1[] = {1, 1};
    double v2[] = {5, 3};
    //double resta[2];

   // int n = sizeof(polilinea)/sizeof (polilinea[0]); //debe dar 3=3
    //resta_vectores (resta, v1, v2, 2);
    //printf("%f, %f\n", resta[0], resta[1]);
    printf("%f\n", prod_interno(v1, v2));
}

double norma (double v1[], double v2[]){
    double resta_x = v1[0] - v2[0];
    double resta_y = v1[1] - v2[1];
    return sqrt(pow(resta_x) + pow(resta_));
}

