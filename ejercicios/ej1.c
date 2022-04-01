#include <math.h>
#include <stdio.h>

double calc_montofinal(double a, double b, double c){
    double r;
    r = 0; //Monto final a cobrar
    r = a * pow((1 + b/100), c);
    return (r);
}

int main(){
    printf("EJERCICIO 1 - GUIA 1\n");
    printf("El resultado es: %le\n", calc_montofinal(1, 2, 3));
    return 0;
}
