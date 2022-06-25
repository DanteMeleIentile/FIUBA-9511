#ifndef POLILINEA_H
#define POLILINEA_H


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
Crea una nueva polilínea según los n puntos recibidos. Devuelve la polilínea creada en memoria nueva o NULL en caso de falla.
*/
polilinea_t *polilinea_crear(const float puntos[][2], size_t n);

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

#endif