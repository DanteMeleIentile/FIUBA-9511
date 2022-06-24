#include "color.h"

color_t color_crear(bool r, bool g, bool b){
    return r*0x80+g*0x40+b*0x20;
}

void color_a_rgb(color_t c, uint8_t *r, uint8_t *g, uint8_t *b){
    //Bits posibles de color_t = 0000 0111
    
    if((c%2)) {
        *b = 255;
    } else { 
        *b = 0; 
    }

    if((c >> 1)%2) {
        *g = 255;
    } else { 
        *g = 0; 
    }

    if((c >> 2)%2) {
        *r = 255;
    } else { 
        *r = 0; 
    }
}