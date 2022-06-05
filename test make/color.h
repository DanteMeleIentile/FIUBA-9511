#ifndef COLOR_H
#define COLOR_H


#include <stdbool.h>
#include <stdint.h>


typedef uint8_t color_t;

color_t color_crear(bool r, bool g, bool b);
void color_a_rgb(color_t c, uint8_t *r, uint8_t *g, uint8_t *b);


#endif