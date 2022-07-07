#ifndef PLANETA_H
#define PLANETA_H

#include "figura.h"

typedef struct{
    figura_t *figura;
    float x, y;
}planeta_t;

planeta_t planeta_crear(figura_t *figura, float x, float y);

void planeta_dibujar(SDL_Renderer *renderer, const planeta_t planeta);

#endif