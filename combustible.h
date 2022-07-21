#ifndef COMBUSTIBLE_H
#define COMBUSTIBLE_H

#include <SDL2/SDL.h>
#include "figura.h"

struct combustible;

typedef struct combustible combustible_t;

/*
** Crea un combustible en la posicion dada.
*/
combustible_t *combustible_crear(const figura_t *figura, float pos_x, float pos_y, double angulo);

/*
** Devuelve la posicion en "x" del combustible.
*/
float combustible_get_pos_x(const combustible_t *combustible);

/*
** Devuelve la posicion en "y" del combustible.
*/
float combustible_get_pos_y(const combustible_t *combustible);

/*
** Libera la memoria del combustible dado.
*/
void combustible_destruir(combustible_t *combustible);

/*
** Dibuja el combustible en pantalla segun sus parametros.
*/
void combustible_imprimir(SDL_Renderer *renderer, const combustible_t *combustible, float escala, float escala_x, float escala_y, float tras_x, float tras_y);

#endif