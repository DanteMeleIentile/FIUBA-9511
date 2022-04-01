//CORDENADAS DE VECTOR A NORMA

#include <math.h>
#include <stdio.h>

float norma_v(float x, float y, float z){
    float n; //norma de vector
    n = 0;
    n = sqrt(pow (x,2) + pow (y,2) + pow (z,2));
    return n;
}
int main(){
    printf("EJERCICIO 5 - GUIA 1\n");
    printf("El resultado es: %f \n", norma_v(2, 3, 4));
    return 0;
}