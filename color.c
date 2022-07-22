#include <stdbool.h>
#include <stdint.h>

#include "color.h"

color_t color_crear(bool r, bool g, bool b){
    return ( (r << 2) | (g << 1) | (b) );
}

void color_a_rgb(color_t c, uint8_t *r, uint8_t *g, uint8_t *b){
    *r = ((c >> 2) & 1) * 255; 
    *g = ((c >> 1) & 1) * 255; 
    *b = (c & 1) * 255;
}