#include <stdlib.h>

#include "fisicas.h"
#include "figura.h"
#include "disparo.h"

#define X 0
#define Y 1

struct disparo{
    figura_t *fig;
    double pos[2];
    double vel[2];
    double angulo;
    double tiempo;
    bool friendly;
};

disparo_t *disparo_crear(double pos_x, double pos_y, double vel_x, double vel_y, double angulo, bool friendly){
    disparo_t *disparo = malloc(sizeof(disparo_t)*1);
    if(disparo == NULL) return NULL;

    disparo->pos[X] = pos_x;
    disparo->pos[Y] = pos_y;

    disparo->vel[X] = vel_x;
    disparo->vel[Y] = vel_y;

    disparo->angulo = angulo;
    disparo->tiempo = 0;
    disparo->friendly = friendly;
    disparo->fig = NULL;
    return disparo;
}

void disparo_avanzar(disparo_t *disparo, double dt){
    disparo->pos[X] = computar_posicion(disparo->pos[X], disparo->vel[X], dt);
    disparo->pos[Y] = computar_posicion(disparo->pos[Y], disparo->vel[Y], dt);
}

bool disparo_act_figura(disparo_t *disparo, const figura_t *figura){
    if(disparo->fig != NULL) figura_destruir(disparo->fig);
    disparo->fig = figura_clonar(figura);

    if(disparo->fig == NULL){
        free(disparo);
        return false;
    }
    if(disparo->angulo != 0){
        figura_rotar(disparo->fig, disparo->angulo);
    }

    if(!(disparo->pos[X] == 0 && disparo->pos[Y] == 0)){
        figura_trasladar(disparo->fig, disparo->pos[X], disparo->pos[Y]);
    }
    return true;
}

void disparo_destruir(disparo_t *disparo){
    if(disparo == NULL) return;
    if(disparo->fig != NULL) figura_destruir(disparo->fig);
    free(disparo);
}

double disparo_get_tiempo(disparo_t *disparo){
    return disparo->tiempo;
}

double disparo_get_pos_x(disparo_t *disparo){
    return disparo->pos[X];
}

double disparo_get_pos_y(disparo_t *disparo){
    return disparo->pos[Y];
}

bool disparo_friendly(disparo_t *disparo){
    return disparo->friendly;
}

double distancia_a_disparo(disparo_t *disparo, double pos_x, double pos_y){
    return distancia_entre_puntos(pos_x, pos_x, disparo->pos[X], disparo->pos[Y]);
}

void disparo_aumentar_tiempo(disparo_t *disparo, double t){
    disparo->tiempo += t;
}

void disparo_imprimir(SDL_Renderer *renderer, const disparo_t *disparo, float escala, float escala_x, float escala_y, float tras_x, float tras_y){
    figura_imprimir(renderer, disparo->fig, escala, escala_x, escala_y, tras_x, tras_y);
}
