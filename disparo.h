#ifndef DISPARO_H
#define DISPARO_H

#include "figura.h"

// INVARIANTES: Angulo se encuentra en radianes, entre 0 y 2 PI
typedef struct{
    figura_t *fig;
    double pos[2];
    double vel[2];
    double angulo;
    double tiempo; //el tiempo máximo es 1000, tiempo siempre es menor a 1000
} disparo_t;


//GETTERS

/*
** Devuelve el tiempo que el disparo estuvo vivo
** PRE: el disparo fue creado
*/
double disparo_get_tiempo(disparo_t *disparo);

/*
** Crea un disparo inicializando sus parámetros segun los valores dados
** Retorna NULL en caso de falla de memoria
*/
disparo_t *disparo_crear(figura_t *figura, double pos[2], double vel[2], double angulo, double dt);

/*
** Destruye el disparo dado
*/
void disparo_destruir(disparo_t *disparo);


void disparo_imprimir(SDL_Renderer *renderer, disparo_t *disparo, double escala);



#endif