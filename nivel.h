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
** Traslada el nivel en X "dx" y en Y "dy"
*/
void nivel_trasladar(nivel_t *nivel, float dx, float dy);


/*
** Imprime el nivel.
*/
void nivel_imprimir(SDL_Renderer *renderer, nivel_t *nivel, float escala);

double nivel_get_pos_x(nivel_t *nivel);
double nivel_get_pos_y(nivel_t *nivel);


bool nivel_act_figura(nivel_t *nivel, figura_t *figura);




// Crear nivel
// Posicionar entidad
// Posiciona figura del nivel


#endif