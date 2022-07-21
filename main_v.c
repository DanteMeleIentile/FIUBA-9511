#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>

#include "polilinea.h"
#include "lista.h"
#include "figura.h"
#include "lectura.h"
#include "fisicas.h"
#include "config.h"
#include "disparo.h"
#include "nave.h"
#include "planeta.h"
#include "nivel.h"
#include "torreta.h"
#include "caracteres.h"
#include "combustible.h"
#include "reactor.h"


int main() {


//----------------------------------------------------------------------------------------------------------------------
//CREACIÓN DE ESTRUCTURA DE LECTURA


    FILE *f1 = fopen("figuras.bin", "rb");
    if(f1 == NULL) {
        fprintf(stderr, "No pudo abrirse figuras.bin\n");
        return 1;
    }

//Creamos un puntero que apunta a un vector "vector_figuras" de una (1) figura_t

    figura_t **vector_figuras = malloc(sizeof(figura_t*));
    if(vector_figuras == NULL){
        fprintf(stderr, "Error de memoria");
        fclose(f1);
        return 1;
    }

    char nombre[20];
    bool infinito;
    figura_tipo_t tipo;
    size_t cant_polilineas;

    size_t cant = 0;
//Comenzamos a leer el archivo para sacar las figuras que tiene adentro
    for(size_t i = 0; leer_encabezado_figura(f1, nombre, &tipo, &infinito, &cant_polilineas); i++){
        if(i >= 1){
            figura_t **aux = realloc(vector_figuras, (i + 1) * sizeof(figura_t*)); //Agrega una componente a "vector_figuras" hasta que no pueda leer mas figuras
            if(aux == NULL){
                for(size_t j = 0; j < (i+1); j++){
                    figura_destruir(vector_figuras[j]);
                }
                free(vector_figuras);

                fprintf(stderr, "Error de memoria");
                fclose(f1);
                return 1;
            }
            vector_figuras = aux;
        }
        vector_figuras[i] = figura_crear(nombre, tipo, infinito, cant_polilineas); //Iguala cada componente a la figura leida del archivo
        if(vector_figuras[i] == NULL){
            if(i >= 1){
                for(size_t j = 0; j < (i+1); j++){
                    figura_destruir(vector_figuras[j]);
                }
                free(vector_figuras);
                fclose(f1);
                return 1;
            }
            free(vector_figuras);
            fclose(f1);
            return 1;
        }

        polilinea_t **vector_polilineas = malloc(sizeof(polilinea_t*) * cant_polilineas); //Creamos un puntero que apunta a un vector "vector_polilineas" de "cant_polilineas" polilinea_t
        if(vector_polilineas == NULL){
            fprintf(stderr, "Error de memoria");
            for(size_t j = 0; j < (i+1); j++){
                figura_destruir(vector_figuras[j]);
            }
            free(vector_figuras);
            fclose(f1);
            return 1;
        }

        for(size_t j = 0; j < cant_polilineas; j++){
            vector_polilineas[j] = leer_polilinea(f1); //Iguala cada componente de las polilineas de cada figura leida del archivo
            if(vector_polilineas[j] == NULL){
                if(j >= 1){
                    for(size_t l = 0; l < j; l++){
                        polilinea_destruir(vector_polilineas[l]);
                    }
                }
                free(vector_polilineas);

                for(size_t k = 0; k < (i+1); k++){
                    figura_destruir(vector_figuras[j]);
                }
                free(vector_figuras);

                fclose(f1);
                return 1;
            }
        }

        figura_setear_polilinea(vector_figuras[i], vector_polilineas);

        if(!figura_setear_polilinea(vector_figuras[i], vector_polilineas)){
            fprintf(stderr, "Error de memoria.");

            for(size_t j = 0; j < cant_polilineas; j++){
                polilinea_destruir(vector_polilineas[j]);
            }
            free(vector_polilineas);

            for(size_t k = 0; k < i; k++){
                figura_destruir(vector_figuras[k]);
            }
            free(vector_figuras);

            return 1; // ERROR 
        }

        cant++;
    }

    const size_t cant_figuras = cant;

    fclose(f1);
//Terminamos de leer el archivo 

//Creación de entidades (Referencias a las figuras del vector_figuras para no buscarlas nuevamente por cada dt)

    //EN DE MAIN

    for(size_t i = 0; i < cant_figuras; i++){
        figura_destruir(vector_figuras[i]);
    }
    free(vector_figuras);

    return 0;
}

