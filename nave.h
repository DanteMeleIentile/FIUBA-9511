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
nave_t *nave_crear(int cant_combustible);

/*
** Devuelve la coordenada "x" de la nave.
*/
float nave_get_pos_x(nave_t *nave);

/*
** Devuelve la coordenada "y" de la nave.
*/
float nave_get_pos_y(nave_t *nave);

/*
** Devuelve la velocidad en "x" de la nave.
*/
float nave_get_vel_x(nave_t *nave);

/*
** Devuelve la velocidad en "y" de la nave.
*/
float nave_get_vel_y(nave_t *nave);

/*
** Devuelve el angulo de la nave.
*/
double nave_get_angulo(nave_t *nave);

/*
** Devuelve la figura principal (en uso/actual) de la nave dada.
*/
figura_t *nave_get_figura_principal(nave_t *nave);

/*
** Devuelve la cantidad de combustible de la nave.
*/
int nave_get_combustible(nave_t *nave);

/*
** Devuelve la cantidad de vidas de la nave.
*/
int nave_get_vidas(nave_t *nave);

/*
** Devuelve el estado del escudo.
*/
bool nave_estado_escudo(nave_t *nave);

/*
** Devuelve el estado del escudo en nivel.
*/
bool nave_estado_escudo_nivel(nave_t *nave);

/*
** Setea los parametros de posicion de la nave a los pedidos.
*/
void nave_setear_posicion(nave_t *nave, float x, float y, double angulo);

/*
** Setea los parametros de velocidad de la nave a los pedidos.
*/
void nave_setear_velocidad(nave_t *nave, float vel_x, float vel_y);

/*
** Setea las vidas de la nave.
*/
void nave_set_vidas(nave_t *nave, int set);

/*
** Agrega UNA vida a la nave.
*/
void nave_agregar_vida(nave_t *nave);

/*
** Quita UNA vida a la nave.
*/
void nave_quitar_vida(nave_t *nave);

/*
** Enciende su respectivo estado.
*/
void nave_prender(nave_t *nave, bool chorro, bool escudo, bool escudo_nivel);

/*
** Apaga su respectivo estado.
*/
void nave_apagar(nave_t *nave, bool chorro, bool escudo, bool escudo_nivel);

/*
** Actualiza las figuras de la nave.
** PRE: La nave fue creada.
*/
bool nave_act_figura(nave_t *nave, const figura_t *nave_fig, const figura_t *nave_mas_chorro_fig, const figura_t *escudo_fig, const figura_t *escudo_nivel_fig);

/*
** Rota la nave dada según angulo y actualiza los valores de la nave.
*/
void nave_rotar(nave_t *nave, double angulo);

/*
** Avanza en dirección a la punta de la nave con acc "aceleracion" en un tiempo dt. Actualiza los valores de velocidad de la nave. 
*/
void nave_avanzar(nave_t *nave, float aceleracion, double dt);

/*
** Acerca la nave hacia el centro con una aceleración "aceleracion" en un tiempo dt. Actualiza los valores de velocidad de la nave. 
*/
void nave_acercar(nave_t *nave, float aceleracion, float centro_x, float centro_y, double dt);

/*
** Acerca la nave en direccion al angulo dado en un tiempo dt. Actualiza los valores de velocidad de la nave. 
*/
void nave_acercar_direccion(nave_t *nave, float aceleracion, double angulo, double dt);

/*
** Invierte el parámetro de velocidad en "x" de la nave.
*/
void nave_invertir_vel_x(nave_t *nave);

/*
** Invierte el parámetro de velocidad en "y" de la nave.
*/
void nave_invertir_vel_y(nave_t *nave);

/*
** Suma a la variable de combustible de la nave.
*/
void nave_sumar_combustible(nave_t *nave, int combustible);

/*
** Setea el angulo del escudo dentro de un nivel.
*/
void nave_escudo_setear_angulo(nave_t *nave, double angulo);

/*
** Apunta el escudo hacia el objetivo dado
*/
bool nave_escudo_apuntar(nave_t *nave, float x_objetivo, float y_objetivo);

/*
** Dibuja la nave en pantalla segun sus parametros.
*/
void nave_imprimir(SDL_Renderer *renderer, const nave_t *nave, float escala, float escala_x, float escala_y, float tras_x, float tras_y);

/*
** Libera la memoria de la nave dada.
*/
void nave_destruir(nave_t *nave);

#endif //NAVE_H