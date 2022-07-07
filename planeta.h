#ifndef PLANETA_H
#define PLANETA_H

#include "figura.h"

typedef struct{
    float x, y;
}planeta_t;

planeta_t posicionar_planeta(SDL_Renderer *renderer, const figura_t *figura, float x, float y);

#endif