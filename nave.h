#ifndef NAVE_H
#define NAVE_H

#include <SDL2/SDL.h>

#include "figura.h"


// INVARIANTES: Angulo se encuentra en radianes, entre 0 y 2 PI
struct nave;

typedef struct nave nave_t;

/*  
** Crea una nave con sus parámetros en 0 en memoria nueva. Si falla, devuelve null.
*/
nave_t *nave_crear(void);

/*
** Devuelve la coordenada "x" de la nave.
*/
double nave_get_pos_x(nave_t *nave);

/*
** Devuelve la coordenada "y" de la nave.
*/
double nave_get_pos_y(nave_t *nave);

/*
** Devuelve el angulo de la nave.
*/
double nave_get_angulo(nave_t *nave);

/*
** Devuelve la figura principal de la nave dada.
*/
figura_t *nave_get_figura_principal(nave_t *nave);

/*
** Setea los parametros de posicion de la nave a los pedidos.
*/
void nave_setear_posicion(nave_t *nave, double x, double y, double angulo);

/*
** Setea los parametros de velocidad de la nave a los pedidos.
*/
void nave_setear_velocidad(nave_t *nave, double vel_x, double vel_y);

/*
** Enciende su respectiva opcion.
*/
void nave_prender(nave_t *nave, bool chorro, bool escudo, bool escudo_nivel);

/*
** Enciende su respectiva opcion
*/
void nave_apagar(nave_t *nave, bool chorro, bool escudo, bool escudo_nivel);

/*
** Actualiza las 2 figuras de la nave según los parametros de la misma (posición y ángulo).
** PRE: La nave fue creada.
*/
void nave_act_figura(nave_t *nave, figura_t *nave_fig, figura_t *nave_mas_chorro_fig, figura_t *escudo_fig, figura_t *escudo_nivel_fig);

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
** Acerca la nave en direccion al angulo dado en un tiempo dt. Actualiza los valores de velocidad de la nave. 
*/
void nave_acercar_direccion(nave_t *nave, double aceleracion, double angulo, double dt);

/*
** Invierte el parámetro de velocidad en "x" de la nave.
*/
void nave_invertir_vel_x(nave_t *nave);


/*
** Invierte el parámetro de velocidad en "y" de la nave.
*/
void nave_invertir_vel_y(nave_t *nave);

/*
** Dibuja la nave en pantalla segun sus parametros;
*/
void nave_imprimir(SDL_Renderer *renderer, nave_t *nave, double escala);


#endif