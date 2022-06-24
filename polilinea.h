#ifndef POLILINEA_H
#define POLILINEA_H

#include <stdio.h>
#include "figura.h"

typedef struct {
    float (*puntos)[2];
    size_t n;
    //agregar color
} polilinea_t;

const char* figura_tipo_a_cadena(figura_tipo_t figura);

void polilinea_destruir(polilinea_t *polilinea);

polilinea_t *leer_polilinea(FILE *f);

#endif