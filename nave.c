#include <stdlib.h>
#include <SDL2/SDL.h>

#include "nave.h"
#include "figura.h"
#include "config.h"

#define X 0
#define Y 1

nave_t *nave_crear(void){
    //Evaluar necesidad de memoría dinámica
    nave_t *nave = malloc(sizeof(nave_t));
    if(nave == NULL) return NULL;

    nave->angulo_actual = 0;

    nave->vel[X] = 0;
    nave->vel[Y] = 0;

    return nave;
}

void nave_rotar(nave_t *nave, double angulo){
    figura_rotar(nave->nave_fig, angulo);
    figura_rotar(nave->nave_fig_mas_chorro, angulo);

    nave->angulo_actual += angulo;

    while(nave->angulo_actual > 2 * PI)
        nave->angulo_actual = nave->angulo_actual - (2 * PI);

    while(nave->angulo_actual < 0)
        nave->angulo_actual = nave->angulo_actual + (2 * PI);
}

void nave_trasladar(nave_t *nave, double dx, double dy){
    figura_trasladar(nave->nave_fig, dx, dy);
    figura_trasladar(nave->nave_fig_mas_chorro, dx, dy);
    nave->pos[X] += dx;
    nave->pos[Y] += dy;
}

void nave_setear_posicion(nave_t *nave, double dx, double dy){
    figura_trasladar(nave->nave_fig, dx, dy);
    figura_trasladar(nave->nave_fig_mas_chorro, dx, dy);
    nave->pos[X] = dx;
    nave->pos[Y] = dy;
}

void nave_impulso(nave_t *nave){

    nave_trasladar(nave, nave->vel[X], nave->vel[Y]);
}
/*
void nave_aceleracion(nave_t *nave, double a, double dt){
    double vx = nave->velocidad*cos(nave->angulo_velocidad) + dt * a * cos(nave->angulo_actual);
    double vy = nave->velocidad*sin(nave->angulo_velocidad) + dt * a * sin(nave->angulo_actual);

    nave->velocidad = sqrt(vx*vx + vy*vy);
    nave->angulo_velocidad = asin(vy);

//    nave_trasladar(nave, vx, vy);
}
*/
/*
void nave_chorro(nave_t *nave, double a, double dt){

}
*/


/*  FUNCION INTERNA
** Setear las figuras de la nave según "figura_nave".
** PRE: La nave fue creada. 
*/
static void nave_setear_figura(nave_t *nave, figura_t *fig_nave, figura_t *fig_nave_mas_chorro){
    nave->nave_fig = figura_clonar(fig_nave);
    nave->nave_fig_mas_chorro = figura_clonar(fig_nave_mas_chorro);
}


void nave_inicializar(nave_t *nave, figura_t *figura_nave, figura_t *fig_nave_mas_chorro){
    nave_setear_figura(nave, figura_nave, fig_nave_mas_chorro);
    figura_rotar(nave->nave_fig, nave->angulo_actual);
    figura_rotar(nave->nave_fig_mas_chorro, nave->angulo_actual);

    nave_setear_posicion(nave, nave->pos[X], nave->pos[Y]);

    //figura_trasladar(figura_nave, nave->pos[X], nave->pos[Y]);
    //figura_trasladar(fig_nave_mas_chorro, nave->pos[X], nave->pos[Y]);

}

void nave_imprimir(SDL_Renderer *renderer, nave_t *nave, double escala, bool chorro){
    if(chorro){
        figura_imprimir(renderer, nave->nave_fig_mas_chorro, escala, nave->pos[X], nave->pos[Y]);
    }else{
        figura_imprimir(renderer, nave->nave_fig, escala, nave->pos[X], nave->pos[Y]);
    }
        
}