#include <stdlib.h>

#include "fisicas.h"
#include "figura.h"
#include "disparo.h"
#include "config.h"


#define X 0
#define Y 1

disparo_t *disparo_crear(double pos_x, double pos_y, double vel_x, double vel_y, double angulo){
    disparo_t *disparo = malloc(sizeof(disparo_t)*1);
    if(disparo == NULL) return NULL;

    disparo->pos[X] = pos_x;
    disparo->pos[Y] = pos_y;

    disparo->vel[X] = vel_x;
    disparo->vel[Y] = vel_y;
    
    disparo->tiempo = 0;
    
    return disparo;
}

void disparo_avanzar(disparo_t *disparo, double dt){
    disparo->pos[X] = computar_posicion(disparo->pos[X], disparo->vel[X], dt);
    disparo->pos[Y] = computar_posicion(disparo->pos[Y], disparo->vel[Y], dt);
}


bool disparo_act_figura(disparo_t *disparo, figura_t *figura){
    disparo->fig = figura_clonar(figura);
    if(disparo->fig == NULL){
        free(disparo);
        return false;
    }

    figura_rotar(disparo->fig, disparo->angulo);

    figura_trasladar(disparo->fig, disparo->pos[X], disparo->pos[Y]);

    return true;
}


void disparo_destruir(disparo_t *disparo){
    figura_destruir(disparo->fig);
    free(disparo);
}


double disparo_get_tiempo(disparo_t *disparo){
    return disparo->tiempo;
}


void disparo_aumentar_tiempo(disparo_t *disparo, double t){
    disparo->tiempo += t;
}


void disparo_imprimir(SDL_Renderer *renderer, disparo_t *disparo, double escala){
    figura_imprimir(renderer, disparo->fig, escala, disparo->pos[X], disparo->pos[Y]);
}
