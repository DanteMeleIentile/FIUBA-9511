#include "polilinea.h"
#include "color.h"
#include <stdlib.h>


#define DIM 2

#define CANT 0xFC00 //1111 1100




polilinea_t *polilinea_crear_vacia(size_t n){
    polilinea_t *polilinea = malloc(sizeof(polilinea_t));

    if(polilinea == NULL){
        return NULL;
    }

    polilinea->puntos = malloc(sizeof(float) * DIM * n);

    if(polilinea->puntos == NULL){
        free(polilinea);
        return NULL;
    }

    polilinea->n = n;

    return polilinea;
}

bool polilinea_setear_punto(polilinea_t *polilinea, size_t pos, float x, float y) {
    printf("POLILINEA[%zd] = (%.2f, %.2f)\n", pos, x, y);
    return true;
}

bool polilinea_setear_color(polilinea_t *polilinea, color_t color) {
    uint8_t r, g, b;
    color_a_rgb(color, &r, &g, &b);
    printf("POLILINEA COLOR: (%d, %d, %d)\n", r, g, b);
    return true;
}

void polilinea_destruir(polilinea_t *polilinea){}

polilinea_t *leer_polilinea(FILE *f){

    uint16_t encabezado;
    if(fread(&encabezado, sizeof(uint16_t), 1, f) != 1){
        return NULL;
    } 

    //color_t color = encabezado >> 13;
    uint16_t cant = encabezado & (~CANT);

    polilinea_t *p = polilinea_crear_vacia(cant);

    /* if(!polilinea_setear_color(p, color)){
        polilinea_destruir(p);
        return NULL;
    }  */

    float pol[cant][2];

    if(fread(pol, sizeof(float) * cant * 2, 1, f) != 1){
        polilinea_destruir(p);
        return NULL;
    }

    for(size_t i = 0; i < cant; i++){
        polilinea_setear_punto(p, i, pol[i][0], pol[i][1]);
    }

    return p;
}