#include <stdlib.h>

#include "fisicas.h"
#include "figura.h"
#include "disparo.h"
#include "config.h"


#define TIEMPO_MAX 1000
#define X 0
#define Y 1

/*
** Setea el angulo del disparo
*/
static void disparo_setear_angulo(disparo_t *disparo, double angulo){

    while(angulo > 2 * PI)
        angulo -= (2 * PI);

    while(angulo < 0)
        angulo += (2 * PI);

    disparo->angulo = angulo;

    figura_rotar(disparo->fig, disparo->angulo);
}

/*
** Actualiza la posicion del disparo según su velocidad
*/
static void disparo_avanzar(disparo_t *disparo, double dt){
    disparo->pos[X] = computar_posicion(disparo->pos[X], disparo->vel[X], dt);
    disparo->pos[Y] = computar_posicion(disparo->pos[Y], disparo->vel[Y], dt);
    figura_trasladar(disparo->fig, disparo->pos[X],disparo->pos[Y]);
}

disparo_t *disparo_crear(figura_t *figura, double pos[2], double vel[2], double angulo, double dt){

    disparo_t *disparo = malloc(sizeof(disparo_t)*1);
    if(disparo == NULL) return NULL;
    disparo->fig = figura_clonar(figura); // VALIDAR FIGURA_CLONAR

    if(disparo->fig == NULL){
        free(disparo);
        return NULL;
    }

    disparo->pos[X] = pos[X];
    disparo->pos[Y] = pos[Y];

    disparo->vel[X] = vel[X];
    disparo->vel[Y] = vel[Y];

    disparo_setear_angulo(disparo, angulo);
    disparo_avanzar(disparo, dt);

    return disparo;
}

void disparo_destruir(disparo_t *disparo){
    figura_destruir(disparo->fig);
    free(disparo);
}

double disparo_get_tiempo(disparo_t *disparo){
    return disparo->tiempo;
}

void disparo_sumar_tiempo(disparo_t *disparo, double t){
    disparo->tiempo += t;
}

void disparo_imprimir(SDL_Renderer *renderer, disparo_t *disparo, double escala){
    figura_imprimir(renderer, disparo->fig, escala, disparo->pos[X], disparo->pos[Y]);
}
