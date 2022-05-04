#include <stdio.h>



void r_suma(int a, int b, long int * suma){
    *suma = a + b;
}

/*void producto(int multiplicando, int multiplicador, float * producto){
    *producto = multiplicador * multiplicando;
}

void division(int dividendo, int divisor, double *){
    *division = (double)dividendo / (double)divisor;
}

mod() */


int main (void){
    int a = 4;
    int b = 3;
    long int suma = 0;
    printf("el resultado de la suma es %ld\n", suma);
    r_suma(a, b, &suma);
    printf("el resultado de la suma es %ld\n", suma);


    return 0;
}