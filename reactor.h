#ifndef REACTOR_H
#define REACTOR_H

#include <SDL2/SDL.h>

#include "figura.h"

struct reactor;
typedef struct reactor reactor_t;

/*
** Crea un reactor en memoria nueva con sus parametros inicializados. Caso contrario, devuelve NULL.
*/
reactor_t *reactor_crear(figura_t *figura, float x, float y, double angulo);

figura_t *reactor_get_figura(reactor_t *reactor);

float reactor_get_pos_x(reactor_t *reactor);

float reactor_get_pos_y(reactor_t *reactor);

void reactor_imprimir(SDL_Renderer *renderer, reactor_t *reactor, float escala);

/*
** Destruye el reactor dado;
*/
void reactor_destruir(reactor_t *reactor);

#endif