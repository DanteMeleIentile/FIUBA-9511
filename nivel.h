#ifndef NIVEL_H
#define NIVEL_H

#include <stddef.h>
#include <SDL2/SDL.h>


#include "figura.h"


struct nivel;
typedef struct nivel nivel_t;

/*
** Crea un nivel_t en memoria nueva con sus parametros inicializados. Caso contrario, devuelve NULL.
*/
nivel_t *nivel_crear(figura_t *figura, size_t cant_torretas, size_t cant_combustible);

/*
** Devuelve la coordenada del primer punto de la figura en "x"
*/
double nivel_x_min(nivel_t *nivel);

/*
** Imprime el nivel.
*/
void nivel_imprimir(SDL_Renderer *renderer, nivel_t *nivel, float escala);


// Crear nivel
// Posiciona figura del nivel
// Posiciona figura del nivel


#endif