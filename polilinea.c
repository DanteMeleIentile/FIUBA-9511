#include "polilinea.h"
#include "color.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>


#define DIMENSION 2
#define X 0
#define Y 1



/* Estructura de las polilineas */
typedef struct {
    float (*puntos)[2];
    size_t n;
} polilinea_t;


polilinea_t *polilinea_crear_vacia(size_t n){
    polilinea_t *p = malloc(sizeof(polilinea_t)); 
    if (p == NULL){
        return NULL;
    }

    p->n = n;
    p->puntos = malloc(n * sizeof(float) * DIMENSION);
    if (p->puntos == NULL){
        free(p);
        return NULL;
    }

    return p;
}


polilinea_t *polilinea_crear(const float puntos[][2], size_t n){
    polilinea_t *p = polilinea_crear_vacia(n);
    if (p == NULL){
        return NULL;
    }
    
    memcpy (*p->puntos, puntos, (n * sizeof(float) * DIMENSION));
    
    return p;
}


void polilinea_destruir(polilinea_t *polilinea){
    free(polilinea->puntos);
    free(polilinea);
}


bool polilinea_setear_punto(polilinea_t *polilinea, size_t pos, float x, float y){
    if (polilinea->n <= pos){  //Confío que la persona que utiliza la función garantiza 'polilinea->puntos != NULL'
        return false;
    }

    polilinea->puntos[pos][X] = x;
    polilinea->puntos[pos][Y] = y;
    return true;
}


polilinea_t *polilinea_clonar(const polilinea_t *polilinea){
    return polilinea_crear((const float(*)[DIMENSION])(polilinea->puntos), polilinea->n);
}