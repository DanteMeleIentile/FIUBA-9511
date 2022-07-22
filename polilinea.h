#ifndef POLILINEA_H
#define POLILINEA_H

#include "color.h"

#include <stddef.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

struct polilinea;

typedef struct polilinea polilinea_t;

/*
** Crea una polilinea de n sin inicializar las coordenadas
*/
polilinea_t *polilinea_crear_vacia(size_t n);

/*
**Crea una nueva polilínea según los n puntos recibidos. Devuelve la polilínea creada en memoria nueva o NULL en caso de falla.
*/
polilinea_t *polilinea_crear(const float puntos[][2], size_t n, color_t c);

/*
** Devuelve el extremo en "x" de la polilinea
** Si "mayor" es true, devuelve el extremo mayor, sino el menor
*/
float polilinea_get_extremo_x(const polilinea_t *polilinea, bool mayor);

/*
** Devuelve el extremo en "y" de la polilinea
** Si "mayor" es true, devuelve el extremo mayor, sino el menor
*/
float polilinea_get_extremo_y(const polilinea_t *polilinea, bool mayor);

/*
** Devuelve el color de la polilinea;
*/
color_t polilinea_get_color(const polilinea_t *polilinea);

/*
** De ser posible, asigna un punto de coordenadas "x" e "y" en la posición "pos" de la polilinea "polilinea". Caso contrario devuelve false;
*/
bool polilinea_setear_punto(polilinea_t *polilinea, size_t pos, float x, float y);

/*
**Devuelve una copia de una polilinea dada en memoria nueva.
*/
polilinea_t *polilinea_clonar(const polilinea_t *polilinea);

/*
** Setea el color de la polilinea al determinado por "color"
*/
bool polilinea_setear_color(polilinea_t *polilinea, color_t color);

/*
** Traslada la polilinea "polilinea" de longitud "n" en "x" dx unidades y en "y" dy unidades
*/
void polilinea_trasladar(polilinea_t *polilinea, float dx, float dy);

/*
** Rota la polilinea "polilinea" de longitud "n" un angulo "rad" en radianes
*/
void polilinea_rotar(polilinea_t *polilinea, double rad);

/*
** Devuelve la distancia menor entre el punto (px; py) y la polilinea dada.
*/
float distancia_punto_a_polilinea(polilinea_t *polilinea, float px, float py);

/*
**Imprime una polilinea con una "escala" determinada. El centro desde el cual se escalará esta determinado por las coordenadas "escala_x; escala_y". La traslación dada a la hora de dibujar estará determinada por "tras_x; tras_y".
** PRE: La polilinea fue creada.
*/
void polilinea_imprimir(SDL_Renderer *renderer, const polilinea_t *polilinea, float escala, float escala_x, float escala_y, float tras_x, float tras_y);

/*
** Libera la memoria de una polilinea dada.
*/
void polilinea_destruir(polilinea_t *polilinea);

#endif //POLILINEA_H