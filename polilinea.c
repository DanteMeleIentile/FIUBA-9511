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


polilinea_t *polilinea_crear_vacia(size_t n){
    polilinea_t *polilinea = malloc(sizeof(polilinea_t));

    if(polilinea == NULL){
        return NULL;
    }

    polilinea->puntos = malloc(sizeof(float) * DIMENSION * n);

    if(polilinea->puntos == NULL){
        free(polilinea);
        return NULL;
    }

    polilinea->n = n;

    return polilinea;
}


polilinea_t *polilinea_crear(const float puntos[][2], size_t n, color_t c){

    polilinea_t *polilinea = polilinea_crear_vacia(n);

    if(polilinea == NULL){
        return NULL;
    }

    polilinea_setear_color(polilinea, c);

    memcpy(polilinea->puntos, puntos, (polilinea->n)*sizeof(float)*DIMENSION);

    return polilinea;
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

bool polilinea_setear_color(polilinea_t *polilinea, color_t color) {
    uint8_t r, g, b;
    color_a_rgb(color, &r, &g, &b);
        polilinea->r = r;
        polilinea->g = g;
        polilinea->b = b;
    return true;
}


polilinea_t *polilinea_clonar(const polilinea_t *polilinea){
    color_t c = color_crear_valor(polilinea->r, polilinea->g, polilinea->b);
    return polilinea_crear((const float(*)[DIMENSION])(polilinea->puntos), polilinea->n, c);
}

void trasladar(float polilinea[][2], size_t n, float dx, float dy) {
    for(int i = 0; i < n; i+=1){
        polilinea[i][X] += dx;
        polilinea[i][Y] += dy;
    }
}

void rotar(float polilinea[][2], size_t n, double rad) {
    double accx;
    double accy;

    for(int i = 0; i < n; i++){
        accx = polilinea[i][X];
        accy = polilinea[i][Y];
        polilinea[i][X] = accx * cos(rad) - accy * sin(rad);
        polilinea[i][Y] = accx * sin(rad) + accy * cos(rad);
    }
}

void polilinea_printf(polilinea_t *polilinea){
    printf("EL COLOR ES %d  %d  %d\n", polilinea->r, polilinea->g, polilinea->b);
    printf("CANT PUNTOS %zd\n", polilinea->n);
    for(size_t i = 0; i < polilinea->n; i++){
        printf("POLILINEA %zd ( %.7f , %.7f )\n", polilinea->n, polilinea->puntos[i][X], polilinea->puntos[i][Y]);
    }
}
