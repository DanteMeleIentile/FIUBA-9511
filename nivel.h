#ifndef NIVEL_H
#define NIVEL_H

#include "figura.h"

//VER ENCAPSULAMIENTO

typedef struct {
    figura_t *torreta;
    size_t id;
    bool activo;
} torreta_t;

typedef struct {
    figura_t *bala;
    float velocidad;
    float tiempo;
} bala_t;

typedef struct {
    torreta_t *torretas;
    bala_t *balas;
} nivel_t;

nivel_t *cargar_nivel(size_t cant_torretas, figura_t *torreta, size_t cant_balas, figura_t *bala);

bool nivel(figura_t *torreta, figura_t *nivel, size_t nivel_actual);



#endif