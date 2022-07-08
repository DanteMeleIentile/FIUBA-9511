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

    nave->angulo = 0;

    nave->pos[X] = 20;
    nave->pos[Y] = 20;

    nave->vel[X] = 0;
    nave->vel[Y] = 0;

    return nave;
}

/*  FUNCION INTERNA
** Setea el angulo de la figura según "angulo".
** PRE: La figura y la Nave fueron creadas
*/

static void nave_setear_angulo(nave_t *nave, double angulo){
    float aux[2] = {nave->pos[X], nave->pos[Y]};


    figura_trasladar(nave->nave_fig, 0, 0); // Movimiento a la posición pedida
    figura_trasladar(nave->nave_fig_mas_chorro, 0, 0);

    nave->pos[X] = 0;
    nave->pos[Y] = 0;

    figura_rotar(nave->nave_fig, angulo);
    figura_rotar(nave->nave_fig_mas_chorro, angulo);

    figura_trasladar(nave->nave_fig, aux[X], aux[Y]); // Movimiento a la posición pedida
    figura_trasladar(nave->nave_fig_mas_chorro, aux[X], aux[Y]);

    nave->pos[X] = aux[X];
    nave->pos[Y] = aux[Y];

    nave->angulo = angulo;

    while(nave->angulo > 2 * PI)
        nave->angulo = nave->angulo - (2 * PI);

    while(nave->angulo < 0)
        nave->angulo = nave->angulo + (2 * PI);
}

void nave_rotar(nave_t *nave, double angulo){
    nave_setear_angulo(nave, nave->angulo + angulo);
}

/*
void nave_trasladar(nave_t *nave, double dx, double dy){
    figura_trasladar(nave->nave_fig, dx, dy);
    figura_trasladar(nave->nave_fig_mas_chorro, dx, dy);
    nave->pos[X] += dx;
    nave->pos[Y] += dy;
}*/
/*
void nave_setear_angulo(nave_t *nave, double angulo){
    double pos_x = nave->pos[X];
    double pos_y = nave->pos[Y];

    nave_trasladar(nave, -pos_x, -pos_y);

    printf("X = %f , Y = %f\n", nave->pos[X], nave->pos[Y]);

    figura_rotar(nave->nave_fig, angulo);
    figura_rotar(nave->nave_fig_mas_chorro, angulo);
    
    nave->angulo = angulo;

    nave_trasladar(nave, pos_x, pos_y);

    printf("X = %f , Y = %f\n", nave->pos[X], nave->pos[Y]);

    while(nave->angulo > 2 * PI)
        nave->angulo = nave->angulo - (2 * PI);

    while(nave->angulo < 0)
        nave->angulo = nave->angulo + (2 * PI);
}*/
/*
void nave_impulso(nave_t *nave){
    nave_trasladar(nave, nave->vel[X], nave->vel[Y]);
}*/
/*
void nave_aceleracion(nave_t *nave, double a, double dt){
    double vx = nave->velocidad*cos(nave->angulo_velocidad) + dt * a * cos(nave->angulo);
    double vy = nave->velocidad*sin(nave->angulo_velocidad) + dt * a * sin(nave->angulo);

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


/*  FUNCION INTERNA
** Setea la posicion de la figura a la dada en "dx" y "dy" con respecto al origen de coordenadas (coord. absolutas).
** PRE: La figura y la Nave fueron creadas
*/
static void nave_figura_setear_posicion(nave_t *nave ,double dx, double dy){
   /* figura_trasladar(nave->nave_fig, -(nave->pos[X]), -(nave->pos[Y])); // Trasladar al origen según la posición de una nave
    figura_trasladar(nave->nave_fig_mas_chorro, -(nave->pos[X]), -(nave->pos[Y]));
*/
    figura_trasladar(nave->nave_fig, dx, dy); // Movimiento a la posición pedida
    figura_trasladar(nave->nave_fig_mas_chorro, dx, dy);
}

void nave_setear_posicion(nave_t *nave, double dx, double dy){
    nave_figura_setear_posicion(nave, dx, dy);
    
    nave->pos[X] = dx;
    nave->pos[Y] = dy;
}

void nave_inicializar(nave_t *nave, figura_t *figura_nave, figura_t *fig_nave_mas_chorro){
    nave_setear_figura(nave, figura_nave, fig_nave_mas_chorro);
    
    nave_setear_posicion(nave, nave->pos[X], nave->pos[Y]);
    
    nave_setear_angulo(nave, nave->angulo);

}


void nave_imprimir(SDL_Renderer *renderer, nave_t *nave, double escala, bool chorro){
    if(chorro){
        figura_imprimir(renderer, nave->nave_fig_mas_chorro, escala, nave->pos[X], nave->pos[Y]);
    }else{
        figura_imprimir(renderer, nave->nave_fig, escala, nave->pos[X], nave->pos[Y]);
    }
        
}
