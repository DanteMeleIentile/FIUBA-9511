/* EJERCICIO 21
Escribir una función que dado un número entero lo imprima espejado. Por ejemplo: 9511 se imprime como 1159. Sugerencia: utilice los operadores módulo % y división /. */


#include <math.h>
#include <stdio.h>

int main(){
    printf("EJERCICIO 21 - GUIA 1\n");
    int n=123;
    int m;
    while (n != 0){
        m = n % 10;
        n = n/10;
        printf ("%d",m);
    }
    printf ("\n");
    return 0;
}