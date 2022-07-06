#include <math.h>

#include "fisicas.h"

void posicionar(figura_t *figura, bool posicionado, float x, float y){
    if(posicionado != true){
        for(size_t k = 0; k < figura->cant_polilineas; k++){
            trasladar(figura->polilineas[k]->puntos, figura->polilineas[k]->n, x, y);
        }
    }
}

double computar_velocidad(double v, double a, double dt) {
    double vel = v + a * dt;  
    return vel;
}

void movimiento(figura_t *figura, float rad, float v){
    
}

void movimiento_p(float poli[][2], size_t n, float rad, float v){
    trasladar(poli, n, v * cos(rad), v*sin(rad));
}

