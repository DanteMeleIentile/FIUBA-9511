#ifndef FISICAS_H
#define FISICAS_H

#include <stdbool.h>
#include "polilinea.h"
#include "figura.h"

void posicionar(figura_t *figura, bool posicionado, float x, float y);

double computar_velocidad(double v, double a, double dt);

void movimiento(figura_t *figura, float rad, float v);

void movimiento_p(float poli[][2], size_t n, float rad, float v);

#endif