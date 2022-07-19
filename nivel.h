#ifndef NIVEL_H
#define NIVEL_H

#include <stddef.h>
#include <SDL2/SDL.h>

#include "figura.h"
#include "lista.h"
#include "reactor.h"

struct nivel;
typedef struct nivel nivel_t;

/*
** Crea un nivel_t en memoria nueva con sus parametros inicializados. Caso contrario, devuelve NULL.
** PRE: se le da un puntero a reactor, puede ser NULL
*/
nivel_t *nivel_crear(figura_t *figura, reactor_t *reactor, int bonus);

/*
** Devuelve la figura del nivel dado.
*/
figura_t *nivel_get_figura(nivel_t *nivel);

/*
** Avisa al TDA nivel que este ya no posee un reactor.
*/
void nivel_reactor_destruir(nivel_t *nivel);

/*
** Devuelve la lista enlazada de torretas.
*/
lista_t *nivel_get_lista_torretas(nivel_t *nivel);

/*
** Devuelve la lista enlazada de combustibles.
*/
lista_t *nivel_get_lista_combustibles(nivel_t *nivel);

/*
** Devuelve el bonus del nivel.
*/
int nivel_get_bonus(nivel_t *nivel);

/*
** Devuelve si true si el nivel es infinito y false si no lo es.
*/
bool nivel_es_infinito(nivel_t *nivel);

/*
** Dado un nivel y una escala, imprime un nivel; si se creó con un reactor, se imprime el reactor junto con el nivel.
*/
void nivel_imprimir(SDL_Renderer *renderer, nivel_t *nivel, float escala);



double nivel_get_pos_x(nivel_t *nivel);

double nivel_get_pos_y(nivel_t *nivel);


bool nivel_act_figura(nivel_t *nivel, figura_t *figura);


#endif