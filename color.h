#ifndef COLOR_H
#define COLOR_H

#include <stdbool.h>
#include <stdint.h>

/*
** Se almacenan los colores en 1 byte<
*/
typedef uint8_t color_t;

/*
** Crear un color_t según las componentes RGB "r", "g" y "b".
*/
color_t color_crear(bool r, bool g, bool b);

/*
** Obtiene de un color_t "c" sus componentes RGB "r", "g" y "b".
*/
void color_a_rgb(color_t c, uint8_t *r, uint8_t *g, uint8_t *b);


#endif