#include <stdio.h>
#include <string.h>


#define TAMANO 100

int main (void){
    char texto_ingresado[TAMANO];

    fgets(texto_ingresado, TAMANO, stdin);

    for (int i = 0; i < strlen(texto_ingresado); i++){
        if (texto_ingresado[i] != '\n'){
            printf ("%d\t %c\t %d\n", i, texto_ingresado[i], texto_ingresado[i]);
        } else
            printf ("%d\t \t %d\n", i, texto_ingresado[i]);
    }

    return 0;
}