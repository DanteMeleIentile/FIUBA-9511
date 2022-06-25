#ifndef FIGURA_H
#define FIGURA_H

#include "polilinea.h"


typedef enum {
    ICONO = 0,
    NIVEL = 1,
    SPRITE = 2,
    PLANETA = 3,
    BASE = 4,
    COMBUSTIBLE = 5,
    TORRETA = 6,
    REACTOR = 7,
} figura_tipo_t;

typedef struct {
    char nombre[20];
    figura_tipo_t tipo;
    bool infinito;
    size_t cantidad_polilineas;
    polilinea_t *polilineas;
} figura_t;

const char* figura_tipo_a_cadena(figura_tipo_t figura);

#endif