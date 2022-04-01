#include <math.h>
#include <stdio.h>

int main(){
    double a;
    int b;
    double r;
    printf("EJERCICIO 1 - GUIA 1\n");
    printf("Coloque valor de primer variable: \n");
    scanf("%lf", &a);

    printf("Coloque valor de segunda variable: \n");
    scanf("%i", &b);

    r= sqrt(a);

    printf("El resultado es: %lf \n", r);
    return 0;
}