#include <math.h>

#include "fisicas.h"

void posicionar(figura_t *figura, bool posicionado, float x, float y){
    if(posicionado != true){
        for(size_t k = 0; k < figura->cant_polilineas; k++){
            trasladar(figura->polilineas[k]->puntos, figura->polilineas[k]->n, x, y);
        }
    }
}

double computar_velocidad(double *v, double *rad, double a, double dt){ 
    return *v + a * dt;
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