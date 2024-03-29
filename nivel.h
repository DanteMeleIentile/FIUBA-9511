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
** Crea un nivel_t en memoria nueva con sus parametros inicializados. En caso de error de memoria, devuelve NULL. 
** PRE: id no puede ser menor a 0
** Obs: Crea una lista enlazada para los combustibles y las torretas.
** Es posible crear niveles sin figuras (figura == NULL)
*/
nivel_t *nivel_crear(const figura_t *figura, size_t id);

/*
** Devuelve la figura del nivel dado.
*/
figura_t *nivel_get_figura(const nivel_t *nivel);

/*
** Devuelve un extremo en "x" del nivel
** Si "mayor" es true, devuelve el extremo mayor, sino el menor
** Si el nivel no tiene figura, devuelve 0
*/
float nivel_get_extremo_x(const nivel_t *nivel, bool mayor);

/*
** Devuelve un extremo en "x" del nivel
** Si "mayor" es true, devuelve el extremo mayor, sino el menor
** Si el nivel no tiene figura, devuelve 0
*/
float nivel_get_extremo_y(const nivel_t *nivel, bool mayor);

/*
** Devuelve la lista enlazada de torretas.
*/
lista_t *nivel_get_lista_torretas(const nivel_t *nivel);

/*
** Devuelve la lista enlazada de combustibles.
*/
lista_t *nivel_get_lista_combustibles(const nivel_t *nivel);

/*
** Devuelve el bonus del nivel.
*/
int nivel_get_bonus(const nivel_t *nivel);

/*
** Devuelve si true si el nivel es infinito y false si no lo es.
*/
bool nivel_get_infinito(const nivel_t *nivel);

/*
** Devuelve el id del nivel.
*/
size_t nivel_get_id(const nivel_t *nivel);

/*
** Setea el bonus del nivel.
*/
void nivel_set_bonus(nivel_t *nivel, int n);

/*
**Imprime un "nivel" con una "escala" determinada. El centro desde el cual se escalará esta determinado por las coordenadas "escala_x; escala_y". La traslación dada a la hora de dibujar estará determinada por "tras_x; tras_y".
** Si el nivel es infinito, se imprimirá una copia de la figura del nivel a izquierda y a derecha ubicada según la coordenada máxima y mínima de la misma en el eje x. Esta funcionalidad tiene el objetivo de dar la ilusión de niveles infinitos. 
** PRE: El nivel fue creado y posee una figura.
*/
void nivel_imprimir(SDL_Renderer *renderer, const nivel_t *nivel, float escala, float escala_x, float escala_y, float tras_x, float tras_y);

/*
** Libera la memoria del nivel.
*/
void nivel_destruir(nivel_t *nivel);

#endif //NIVEL_H