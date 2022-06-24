#ifndef FIGURA_H
#define FIGURA_H

#include <stdbool.h>
#include <stdio.h>

typedef enum figura_tipo_t {
    ICONO = 0,
    NIVEL = 1,
    SPRITE = 2,
} figura_tipo_t;

const char* figura_tipo_a_cadena(figura_tipo_t figura);

bool leer_encabezado_figura(FILE *f, char nombre[], figura_tipo_t *tipo, bool *infinito, size_t *cantidad_polilineas);

#endif