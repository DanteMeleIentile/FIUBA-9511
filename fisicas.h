#ifndef FISICAS_H
#define FISICAS_H

#include <stdbool.h>
#include "polilinea.h"
#include "figura.h"

void posicionar(figura_t *figura, bool posicionado, float x, float y);

double computar_velocidad(double v, double a, double dt);

double computar_posicion(double pi, double vi, double dt);


//void movimiento(figura_t *figura, float rad, float v);

#endif