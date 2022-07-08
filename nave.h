#ifndef NAVE_H
#define NAVE_H

#include <SDL2/SDL.h>

#include "figura.h"


// INVARIANTES: Angulo se encuentra en radianes, entre 0 y 2 PI
typedef struct{
    figura_t *fig;
    figura_t *fig_chorro;
    double angulo;
    double vel[2];
    double pos[2];
    //int cant_combustible;
} nave_t;

/*
** Retorna la coordenada "x" de la nave.
*/
double nave_get_pos_x(nave_t *nave);

/*
** Retorna la coordenada "y" de la nave.
*/
double nave_get_pos_y(nave_t *nave);

/*
** Setea los parametros de posicion de la nave a los pedidos
*/
void nave_setear_posicion(nave_t *nave, double x, double y);

/*
** Actualiza las 2 figuras de la nave según los parametros de la misma (posición y ángulo).
** PRE: La nave fue creada.
*/
void nave_act_figura(nave_t *nave, figura_t *figura, figura_t *figura2);

/*
** Rota la nave dada según angulo y actualiza los valores de la nave.
*/
void nave_rotar(nave_t *nave, double angulo);

/*
** Avanza en dirección a la punta de la nave con acc "aceleracion" en un tiempo dt. Actualiza los valores de velocidad de la nave. 
*/
void nave_avanzar(nave_t *nave, double aceleracion, double dt);

/*
** Acerca la nave hacia el centro con una aceleración "aceleracion" en un tiempo dt. Actualiza los valores de velocidad de la nave. 
*/
void nave_acercar(nave_t *nave, double aceleracion, double centro_x, double centro_y, double dt);

/*
** Invierte el parámetro de velocidad en "x" de la nave.
*/
void nave_invertir_vel_x(nave_t *nave);


/*
** Invierte el parámetro de velocidad en "y" de la nave.
*/
void nave_invertir_vel_y(nave_t *nave);

/*  
** Crea una nave con sus parámetros en 0 en memoria nueva. Si falla, devuelve null
*/
nave_t *nave_crear(void);

void nave_imprimir(SDL_Renderer *renderer, nave_t *nave, double escala, bool chorro);


#endif