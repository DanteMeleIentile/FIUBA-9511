
#include "color.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>



struct polilinea;
typedef struct polilinea polilinea_t;

struct polilinea {
    int x;
};

polilinea_t *polilinea_crear_vacia(size_t n) {
    printf("POLILINEA N=%zd\n", n);
    static polilinea_t x;
    return &x;
}

void polilinea_destruir(polilinea_t *polilinea) {}

bool polilinea_setear_punto(polilinea_t *polilinea, size_t pos, float x, float y) {
    printf("POLILINEA[%zd] = (%.2f, %.2f)\n", pos, x, y);
    return true;
}

bool polilinea_setear_color(polilinea_t *polilinea, color_t color) {
    uint8_t r, g, b;
    color_a_rgb(color, &r, &g, &b);
    printf("POLILINEA COLOR: (%d, %d, %d)\n", r, g, b);
    return true;
}