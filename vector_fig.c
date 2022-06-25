#include "polilinea.h"
#include "figura.h"
#include "lectura.h"

#include <stdio.h>
#include <stdlib.h>



// OBJETIVO: IMPRIMIR EN UN TXT EL CONTENIDO DE BINARIO

int main(void) {
    FILE *f = fopen(figuras.bin, "rb");
    if(f == NULL) {
        fprintf(stderr, "No pudo abrirse \"%s\"\n", argv[1]);
        return 1;
    }

    figura_t *vector_figuras = malloc(sizeof(figura_t));
    //VER CASO DE FALLA

    char nombre[20];
    bool infinito;
    figura_tipo_t tipo;
    size_t cant_polilineas;

    if(!leer_encabezado_figura(f, nombre, tipo, infinito, cant_polilineas))
        break; // SE TERMINO EL ARCHIVO

    vector_figuras[i] = figura_crear(nombre, tipo, infinito, cant_polilineas);

    figura_t *vector_polilineas = malloc(sizeof(polilinea_t) * cant_polilineas);

    //for CANT POLI VECES
    vector_polilineas[j] = leer_polilinea(f);

    if(!figura_setear_polilinea(vector_figuras[i], vector_polilineas[j]) == NULL)
        break; // ERROR 


    fclose(f);

    return 0;
}