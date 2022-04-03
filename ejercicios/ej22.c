/* EJERCICIO 22
Escribir una función es_primo que dado un número entero devuelva true si el mismo es primo y false en caso contrario.*/

#include <math.h>
#include <stdio.h>

int n, m=0;


int es_primo(int n){
    for(int i = 1; i<=n; i++){
        m = n / i;
        m = m + m;
    }
    if (m == 2){
        return 1;
    } else {
        return 2;
    }
}

int main(){
    printf("EJERCICIO 21 - GUIA 1\n");
    printf("es primo %d", es_primo(8));
    return 0;
}