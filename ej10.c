#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool vacia(char cadena_ingresada[]){
    if (cadena_ingresada[0] == '\0'){
        return true;
    }
    return false;
}

int main (void){
    char cadena_ingresada[100];
    //char cadena_ingresada[100] = {"hola"};

    printf ("\nLa cadena ingresada está vacia: %d\n", vacia(cadena_ingresada));
    return 0;
}
