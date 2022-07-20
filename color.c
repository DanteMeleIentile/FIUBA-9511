#include "color.h"

#include <stdbool.h>
#include <stdint.h>

color_t color_crear(bool r, bool g, bool b){
    return ( (r << 2) | (g << 1) | (b) );
}

color_t color_crear_valor(uint8_t r, uint8_t g, uint8_t b){
    bool r1, g1, b1;
    if(r > 0){
        r1 = true;
    }else{
        r1 = false;
    }
    if(g > 0){
        g1 = true;
    }else{
        g1 = false;
    }
    if(b > 0){
        b1 = true;
    }else{
        b1 = false;
    }
    return ( (r1 << 2) | (g1 << 1) | (b1) );
}

void color_a_rgb(color_t c, uint8_t *r, uint8_t *g, uint8_t *b){
    *r = ((c >> 2) & 1) * 255; 
    *g = ((c >> 1) & 1) * 255; 
    *b = (c & 1) * 255;
}