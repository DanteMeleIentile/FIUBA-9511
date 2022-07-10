#ifndef NIVEL_H
#define NIVEL_H

#include <stddef.h>
#include <SDL2/SDL.h>

#include "figura.h"
#include "lista.h"


struct nivel;
typedef struct nivel nivel_t;

/*
** Crea un nivel_t en memoria nueva con sus parametros inicializados. Caso contrario, devuelve NULL.
*/
nivel_t *nivel_crear(figura_t *figura, size_t cant_torretas, size_t cant_combustible);

/*
** Devuelve el extremo en "x" del nivel
** Si "mayor" es true, devuelve el extremo mayor, sino el menor
*/
float nivel_get_extremo_x(nivel_t *nivel, bool mayor);


/*
** Devuelve el extremo en "x" del nivel
** Si "mayor" es true, devuelve el extremo mayor, sino el menor
*/
float nivel_get_extremo_y(nivel_t *nivel, bool mayor);


/*
** Dado un nivel y una escala, imprime un nivel escalado según pos_x y pos_y
*/
void nivel_imprimir(SDL_Renderer *renderer, nivel_t *nivel, float escala, float pos_x, float pos_y);


#endif