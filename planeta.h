#ifndef PLANETA_H
#define PLANETA_H

#include <SDL2/SDL.h>

#include "figura.h"

struct planeta;

typedef struct planeta planeta_t;

/*
** Crea en memoria nueva un planeta, setea figura como su figura, sus posiciones en "x" e "y" según las dadas y su id.
*/
planeta_t *planeta_crear(figura_t *figura, float x, float y, size_t id);

/*
** Devuelve la posición en "x" del planeta dado.
*/
float planeta_get_pos_x(planeta_t *planeta);

/*
** Devuelve la posición en "y" del planeta dado.
*/
float planeta_get_pos_y(planeta_t *planeta);

/*
** Setea la posición del planeta en (x; y).
*/
void planeta_set_pos(planeta_t *planeta, float x, float y);

/*
** Devuelve la distancia entre la nave y la figura del planeta.
*/
float distancia_a_planeta(planeta_t *planeta, float pos_x, float pos_y);

/*
**Imprime un "planeta" con una "escala" determinada. El centro desde el cual se escalará esta determinado por las coordenadas "escala_x; escala_y". La traslación dada a la hora de dibujar estará determinada por "tras_x; tras_y".
** PRE: El planeta fue creado y posee una figura.
*/
void planeta_imprimir(SDL_Renderer *renderer, const planeta_t *planeta, float escala, float escala_x, float escala_y, float tras_x, float tras_y);

/*
** Libera la memoria del planeta dado.
*/
void planeta_destruir(planeta_t *planeta);

#endif