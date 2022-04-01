#include <math.h>
#include <stdio.h>

float fahrenheit(float a){
    float c;
    c = 0; //Conversión a grados Celcuis
    c = (a - 32) * (1.8);
    
    return c;
}
int main(){
    printf("EJERCICIO 2 y 3 - GUIA 1\n");
    printf("El resultado es: %f \n", fahrenheit(2));
    return 0;
}
