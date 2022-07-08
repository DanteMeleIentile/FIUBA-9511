#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>


#include "nave.h"
#include "figura.h"
#include "config.h"
#include "fisicas.h"


#define X 0
#define Y 1


double DEG_A_RAD(double grados){
    return grados * PI / 180;
}


nave_t *nave_crear(void){
    //Evaluar necesidad de memoría dinámica
    nave_t *nave = malloc(sizeof(nave_t));
    if(nave == NULL) return NULL;

    nave->angulo = DEG_A_RAD(90);

    nave->pos[X] = 50;
    nave->pos[Y] = 50;

    nave->vel[X] = 0;
    nave->vel[Y] = 0;

    return nave;
}


void nave_act_figura(nave_t *nave, figura_t *figura, figura_t *figura2){
    nave->fig = figura_clonar(figura);
    nave->fig_chorro = figura_clonar(figura2);

    figura_rotar(nave->fig, nave->angulo);
    figura_rotar(nave->fig_chorro, nave->angulo);

    figura_trasladar(nave->fig, nave->pos[X], nave->pos[Y]);
    figura_trasladar(nave->fig_chorro, nave->pos[X], nave->pos[Y]);
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


void nave_avanzar(nave_t *nave, double aceleracion, double dt){
    nave->vel[X] = computar_velocidad(nave->vel[X], aceleracion * cos(nave->angulo), dt);
    nave->vel[Y] = computar_velocidad(nave->vel[Y], aceleracion * sin(nave->angulo), dt);

    nave->pos[X] = computar_posicion(nave->pos[X], nave->vel[X], dt);
    nave->pos[Y] = computar_posicion(nave->pos[Y], nave->vel[Y], dt);
    printf("FUNCION pos X= %f, pos Y= %f\n", nave->pos[X], nave->pos[Y]);
}



void nave_acercar(nave_t *nave, double aceleracion, double centro_x, double centro_y, double dt){
    nave->vel[X] = computar_velocidad(nave->vel[X], 0, dt);
    nave->vel[Y] = computar_velocidad(nave->vel[Y], -aceleracion, dt);

    nave->pos[X] = computar_posicion(nave->pos[X], nave->vel[X], dt);
    nave->pos[Y] = computar_posicion(nave->pos[Y], nave->vel[Y], dt);
}






void nave_imprimir(SDL_Renderer *renderer, nave_t *nave, double escala, bool chorro){
    if(chorro){
        figura_imprimir(renderer, nave->fig_chorro, escala, nave->pos[X], nave->pos[Y]);
    }else{
        figura_imprimir(renderer, nave->fig, escala, nave->pos[X], nave->pos[Y]);
    }
}