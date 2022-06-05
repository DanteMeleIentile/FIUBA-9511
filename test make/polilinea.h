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
typedef struct polilinea polilinea_t;

/*
** Crea una polilinea de n sin inicializar las coordenadas
*/
polilinea_t *polilinea_crear_vacia(size_t n);

/*
** Destruye una polilinea creada mediante "polilinea_crear_vacia". Devuelve NULL en caso de falla.
*/
void polilinea_destruir(polilinea_t *polilinea);

/*
** De ser posible, asigna un punto de coordenadas "x" e "y" en la posición "pos" de la polilinea "polilinea". Caso contrario devuelve false;
*/
bool polilinea_setear_punto(polilinea_t *polilinea, size_t pos, float x, float y);

/*
** De ser posible, asigna un color "color" a la polilinea "polilinea". Caso contrario devuelve false;
*/bool polilinea_setear_color(polilinea_t *polilinea, color_t color);

#endif