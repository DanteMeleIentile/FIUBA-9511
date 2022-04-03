/* EJERCICIO 16
Escribir un programa que imprima por pantalla todas las fichas del dominó, sin repetir. */


#include <math.h>
#include <stdio.h>



/* int main(){
    int i;
    int p=0;
    char a='.'
    printf("EJERCICIO 16 - GUIA 1\n");
    for (i=0; i<=6; i++){
        p=0;
        for (p=0; p<=i; p++){
            printf("%d\t", p);
        }
    printf("\n");
        for (p=0; p<=i; p++){
            printf("%d\t", i);
        }
    printf("\n\n");
    }
    return 0;
} */


int main(){
    int i=0;
    int p=0;
    //char a='.';
    printf("EJERCICIO 16 - GUIA 1\n");
    for (i=0; i<=6; i++){
        p=0;
        for (p=0; p<=i; p++){
            printf("%d\t", p);
        }
    printf("\n");
        for (p=0; p<=i; p++){
            printf("%d\t", i);
        }
    printf("\n\n");
    }
    return 0;
}