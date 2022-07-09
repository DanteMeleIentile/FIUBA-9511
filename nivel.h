#ifndef NIVEL_H
#define NIVEL_H

#include "figura.h"
#include "lista.h"

//VER ENCAPSULAMIENTO

struct nivel;

typedef struct nivel nivel_t;

nivel_t *nivel_crear(size_t cant_torretas, figura_t *torreta);

#endif