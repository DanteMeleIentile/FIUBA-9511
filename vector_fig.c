#include "polilinea.h"
#include "figura.h"
#include "lectura.h"

#include <stdio.h>
#include <stdlib.h>



// OBJETIVO: IMPRIMIR EN UN TXT EL CONTENIDO DE BINARIO

int main(void) {
    FILE *f = fopen("figuras.bin", "rb");
    if(f == NULL) {
        fprintf(stderr, "No pudo abrirse figuras.bin\n");
        return 1;
    }
/*
** Creamos un puntero que apunta a un vector "vector_figuras" de una (1) figura_t
*/

    figura_t **vector_figuras = malloc(sizeof(figura_t*));
    if(vector_figuras == NULL){
        fprintf(stderr, "Error de memoria");
        return 1;
    }
    
    //VER CASO DE FALLA

    char nombre[20];
    bool infinito;
    figura_tipo_t tipo;
    size_t cant_polilineas;

    size_t cant_figuras;
/*
** 
*/

    for(size_t i = 0; !leer_encabezado_figura(f, nombre, &tipo, &infinito, &cant_polilineas); i++){
        if(i != 0)
            realloc(vector_figuras, (i + 1) * sizeof(figura_t*)); //Agrega una componente a "vector_figuras" hasta que no pueda leer mas figuras

        vector_figuras[i] = figura_crear(nombre, tipo, infinito, cant_polilineas); //Iguala cada componente a la figura leida del archivo

        polilinea_t **vector_polilineas = malloc(sizeof(polilinea_t*) * cant_polilineas); //Creamos un puntero que apunta a un vector "vector_polilineas" de "cant_polilineas"z polilinea_t

        if(vector_polilineas == NULL){
            fprintf(stderr, "Error de memoria");
            return 1;
        }

        for(size_t j = 0; j < cant_polilineas; j++){
            vector_polilineas[j] = leer_polilinea(f); //Iguala cada componente de las polilineas de cada figura leida del archivo
            if(!figura_setear_polilinea(vector_figuras[i], vector_polilineas[j]) == NULL)
                break; // ERROR 
        }

        cant_figuras = i + 1; //EVALUAR
    }
  
    fclose(f);

    return 0;
}