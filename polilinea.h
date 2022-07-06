#ifndef POLILINEA_H
#define POLILINEA_H

#include "color.h"

#include <stddef.h>
#include <stdbool.h>
/*
** La estructura que se define para las polilineas es de tipo:
**
** +--------+
** | PUNTOS | -> Puntos de la polilinea
** +--------+
** |   N    | -> Cantidad de puntos de la polilinea
** +--------+
*/
typedef struct {
    float (*puntos)[2];
    size_t n;
    uint8_t r,g,b; 
} polilinea_t;
/*
** Crea una polilinea de n sin inicializar las coordenadas
*/
polilinea_t *polilinea_crear_vacia(size_t n);

/*
Crea una nueva polilínea según los n puntos recibidos. Devuelve la polilínea creada en memoria nueva o NULL en caso de falla.
*/
polilinea_t *polilinea_crear(const float puntos[][2], size_t n, color_t c);

/*
** Destruye una polilinea creada mediante "polilinea_crear_vacia". Devuelve NULL en caso de falla.
*/
void polilinea_destruir(polilinea_t *polilinea);

/*
** De ser posible, asigna un punto de coordenadas "x" e "y" en la posición "pos" de la polilinea "polilinea". Caso contrario devuelve false;
*/
bool polilinea_setear_punto(polilinea_t *polilinea, size_t pos, float x, float y);


/*
Devuelve una copia de una polilinea dada en memoria nueva.
*/
polilinea_t *polilinea_clonar(const polilinea_t *polilinea);

/*
** Devuelve una copia de una polilinea dada en memoria nueva.
*/
polilinea_t *polilinea_crear_vector(const polilinea_t *polilinea);

/*
** SETEA EL COLOR DE LA POLILINEA (CAMBIAR)
*/
bool polilinea_setear_color(polilinea_t *polilinea, color_t color);

void trasladar(float polilinea[][2], size_t n, float dx, float dy);

void rotar(float polilinea[][2], size_t n, double rad);

void polilinea_printf(polilinea_t *polilinea);

#endif