#include <math.h>

#include "fisicas.h"

double computar_velocidad(double vi, double a, double dt){
    return (vi + a * dt);
}

double computar_posicion(double pi, double vi, double dt){
    return (pi + vi * dt);
}
/*
//RAD ES EL ANGULO DE LA VELOCIDAD APLICADA EN EL CUERPO
//V ES EL MODULO DE LA VELOCIDAD APLICADA EN EL CUERPO
//A ES EL MODULO DE LA ACELERACION APLICADA EN EL CUERPO
void movimiento(figura_t *figura, float rad, float v, double a){
    for(size_t i = 0; i < figura->cant_polilineas; i++){
        trasladar(figura->polilineas[i]->puntos, figura->polilineas[i]->n, v * cos(rad), v*sin(rad));
    }
}
*/
