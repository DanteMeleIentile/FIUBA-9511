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

/*
** Devuelve la figura del reactor dado.
*/
figura_t *reactor_get_figura(reactor_t *reactor);

/*
** Devuelve la coordenada "x".
*/
float reactor_get_pos_x(reactor_t *reactor);

/*
** Devuelve la coordenada "y".
*/
float reactor_get_pos_y(reactor_t *reactor);

/*
**Imprime con una "escala" determinada. El centro desde el cual se escalará esta determinado por las coordenadas "escala_x; escala_y". La traslación dada a la hora de dibujar estará determinada por "tras_x; tras_y". 
** PRE: El reactor fue creado y posee una figura.
*/
void reactor_imprimir(SDL_Renderer *renderer, const reactor_t *reactor, float escala, float escala_x, float escala_y, float tras_x, float tras_y);

/*
** Libera la memoria el reactor dado;
*/
void reactor_destruir(reactor_t *reactor);

#endif //REACTOR_H