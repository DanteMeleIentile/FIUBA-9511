#ifndef PLANETA_H
#define PLANETA_H

#include <SDL2/SDL.h>

#include "figura.h"

struct planeta;

typedef struct planeta planeta_t;

planeta_t *planeta_crear(figura_t *figura, float x, float y);

//GETTERS

float planeta_get_pos_x(planeta_t *planeta);

float planeta_get_pos_y(planeta_t *planeta);

//SETTERS

void planeta_set_pos(planeta_t *planeta, float x, float y);

void planeta_imprimir(SDL_Renderer *renderer, planeta_t *planeta, float escala, float escala_x, float escala_y, float tras_x, float tras_y);

double distancia_a_planeta(planeta_t *planeta, float pos_x, float pos_y);

void planeta_destruir(planeta_t *planeta);

#endif