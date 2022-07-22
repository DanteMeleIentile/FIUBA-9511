#ifndef DISPARO_H
#define DISPARO_H

#include "figura.h"

/* INVARIANTES:
** Angulo se encuentra en radianes, entre 0 y 2 PI
** El tiempo nunca puede ser negativo. 
*/
struct disparo;

typedef struct disparo disparo_t;

/*
** Crea un disparo inicializando sus parámetros segun los valores dados
** Retorna NULL en caso de falla de memoria
*/
disparo_t *disparo_crear(float pos_x, float pos_y, float vel_x, float vel_y, double angulo, bool friendly);

/*
** Devuelve el tiempo que el disparo estuvo vivo
** PRE: el disparo fue creado
*/
double disparo_get_tiempo(disparo_t *disparo);

/*
** Devuelve la posicion en "x" del disparo
*/
float disparo_get_pos_x(disparo_t *disparo);

/*
** Devuelve la posicion en "y" del disparo
*/
float disparo_get_pos_y(disparo_t *disparo);

/*
** Devuelve si el disparo puede hacer daño
*/
bool disparo_friendly(disparo_t *disparo);

/*
** Devuelve la distancia entre el disparo y punto (pos_x; pos_y)
*/
float distancia_a_disparo(disparo_t *disparo, float pos_x, float pos_y);

/*
** Aumenta el tiempo del disparo dado en "t" unidades
*/
void disparo_aumentar_tiempo(disparo_t *disparo, double t);

/*
** Avanza la posicion del disparo según su velocidad.
*/
void disparo_avanzar(disparo_t *disparo, double dt);

/*
** Actualiza la figura del disparo.
** PRE: El disparo fue creado.
*/
bool disparo_act_figura(disparo_t *disparo, const figura_t *figura);

/*
** Dado el renderer de SDL y parámetros de dibujo, dibuja un disparo.
*/
void disparo_imprimir(SDL_Renderer *renderer, const disparo_t *disparo, float escala, float escala_x, float escala_y, float tras_x, float tras_y);

/*
** Libera la memoria del disparo dado.
*/
void disparo_destruir(disparo_t *disparo);

#endif //DISPARO_H