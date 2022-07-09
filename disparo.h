#ifndef DISPARO_H
#define DISPARO_H

#include "figura.h"

/* INVARIANTES:
** Angulo se encuentra en radianes, entre 0 y 2 PI
** El tiempo nunca puede ser negativo. 
*/
typedef struct{
    figura_t *fig;
    double pos[2];
    double vel[2];
    double angulo;
    double tiempo;
} disparo_t;

//GETTERS

/*
** Devuelve el tiempo que el disparo estuvo vivo
** PRE: el disparo fue creado
*/
double disparo_get_tiempo(disparo_t *disparo);


//SETTERS

/*
** Aumenta el tiempo del disparo dado en "t" unidades
*/
void disparo_aumentar_tiempo(disparo_t *disparo, double t);


/*
** Crea un disparo inicializando sus parámetros segun los valores dados
** Retorna NULL en caso de falla de memoria
*/
disparo_t *disparo_crear(double pos_x, double pos_y, double vel_x, double vel_y, double angulo);


/*
** Destruye el disparo dado
*/
void disparo_destruir(disparo_t *disparo);


/*
** Dado el renderer de SDL, un disparo y una escala, dibuja.
*/
void disparo_imprimir(SDL_Renderer *renderer, disparo_t *disparo, double escala);


/*
** avanza en la posicion del disparo según su velocidad.
*/
void disparo_avanzar(disparo_t *disparo, double dt);


/*
** Actualiza la figura del disparo según los parametros de del mismo (posición y ángulo).
** PRE: El disparo fue creado.
*/
bool disparo_act_figura(disparo_t *disparo, figura_t *figura);

#endif