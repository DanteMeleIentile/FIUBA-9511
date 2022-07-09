#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>


#include "nave.h"
#include "figura.h"
#include "config.h"
#include "fisicas.h"


#define X 0
#define Y 1


static double DEG_A_RAD(double grados){
    return grados * PI / 180;
}

nave_t *nave_crear(void){
    //Evaluar necesidad de memoría dinámica
    nave_t *nave = malloc(sizeof(nave_t));
    if(nave == NULL) return NULL;

    nave->angulo = DEG_A_RAD(0);

    nave->pos[X] = 0;
    nave->pos[Y] = 0;

    nave->vel[X] = 0;
    nave->vel[Y] = 0;

    return nave;
}

double nave_get_pos_x(nave_t *nave){
    return nave->pos[X];
}

double nave_get_pos_y(nave_t *nave){
    return nave->pos[Y];
}

double nave_get_angulo(nave_t *nave){
    return nave->angulo;
}

void nave_setear_posicion(nave_t *nave, double x, double y){
    nave->pos[X] = x;
    nave->pos[Y] = y;
}

void nave_act_figura(nave_t *nave, figura_t *figura, figura_t *figura2){
    nave->fig = figura_clonar(figura);
    nave->fig_chorro = figura_clonar(figura2);

    figura_rototrasladar(nave->fig, nave->pos[X], nave->pos[Y], nave->angulo);
    figura_rototrasladar(nave->fig_chorro, nave->pos[X], nave->pos[Y], nave->angulo);
}

void nave_rotar(nave_t *nave, double angulo){
    figura_trasladar(nave->fig, -nave->pos[X], -nave->pos[Y]);
    figura_trasladar(nave->fig_chorro, -nave->pos[X], -nave->pos[Y]);

    figura_rotar(nave->fig, angulo);
    figura_rotar(nave->fig_chorro, angulo);

    figura_trasladar(nave->fig, nave->pos[X], nave->pos[Y]);
    figura_trasladar(nave->fig_chorro, nave->pos[X], nave->pos[Y]);

    nave->angulo += angulo;

    while(nave->angulo > 2 * PI)
        nave->angulo = nave->angulo- (2 * PI);

    while(nave->angulo < 0)
        nave->angulo = nave->angulo + (2 * PI);
}

static void nave_aceleracion(nave_t *nave, double aceleracion, double rad, double dt){
    nave->vel[X] = computar_velocidad(nave->vel[X], aceleracion * cos(rad), dt);
    nave->vel[Y] = computar_velocidad(nave->vel[Y], aceleracion * sin(rad), dt);
}

static void nave_velocidad(nave_t *nave, double dt){
    nave->pos[X] = computar_posicion(nave->pos[X], nave->vel[X], dt);
    nave->pos[Y] = computar_posicion(nave->pos[Y], nave->vel[Y], dt);
}

void nave_avanzar(nave_t *nave, double aceleracion, double dt){
    nave_aceleracion(nave, aceleracion, nave->angulo, dt);
    nave_velocidad(nave, dt);
}

void nave_acercar(nave_t *nave, double aceleracion, double centro_x, double centro_y, double dt){
    double angulo = 0;
    if(nave->pos[X] > centro_x && nave->pos[Y] < centro_y){
        angulo = atan((-nave->pos[Y] - centro_y)/(nave->pos[X] - centro_x)) + PI;
    } else if(nave->pos[X] > centro_x && nave->pos[Y] > centro_y){
        angulo = atan((nave->pos[Y] - centro_y)/(nave->pos[X] - centro_x)) + PI;
    } else {
        angulo = atan((nave->pos[Y] - centro_y)/(nave->pos[X] - centro_x));
    }
    nave_aceleracion(nave, aceleracion, angulo, dt);
    nave_velocidad(nave, dt);
}

void nave_invertir_vel_x(nave_t *nave){
    nave->vel[X] = -nave->vel[X];
}

void nave_invertir_vel_y(nave_t *nave){
    nave->vel[Y] = -nave->vel[Y];
}

void nave_imprimir(SDL_Renderer *renderer, nave_t *nave, double escala, bool chorro){
    if(chorro){
        figura_imprimir(renderer, nave->fig_chorro, escala, nave->pos[X], nave->pos[Y]);
    }else{
        figura_imprimir(renderer, nave->fig, escala, nave->pos[X], nave->pos[Y]);
    }
}