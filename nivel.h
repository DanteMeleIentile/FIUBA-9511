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
** Devuelve un nivel clonado en memoria nueva. Caso contrario, devuelve NULL
*/
nivel_t *nivel_clonar(const nivel_t *nivel);


/*
**Imprime un "nivel" con una "escala" determinada. El centro desde el cual se escalará esta determinado por las coordenadas "escala_x; escala_y". La traslación dada a la hora de dibujar estará determinada por "tras_x; tras_y".
** Si "infinito" es verdadero, se imprimirá una copia de la figura del nivel a izquierda y a derecha ubicada según la coordenada máxima y mínima de la misma en el eje x. Esta funcionalidad tiene el objetivo de dar la ilusión de niveles infinitos. 
**PRE: El nivel fue creado y posee una figura.
**POST: NINGÚN parámetro del nivel se modifica luego de imprimirlo en pantalla
*/
void nivel_imprimir(SDL_Renderer *renderer, nivel_t *nivel, float escala, float escala_x, float escala_y, float tras_x, float tras_y, bool infinito);

#endif