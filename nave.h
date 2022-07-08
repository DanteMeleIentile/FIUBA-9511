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
** Actualiza las 2 figuras de la nave según los parametros de la misma (posición y ángulo).
** PRE: La nave fue creada.
*/
void nave_act_figura(nave_t *nave, figura_t *figura, figura_t *figura2);

/*
** Rota la nave dada según angulo y actualiza los valores de la nave.
*/
void nave_rotar(nave_t *nave, double angulo);

/*
** Avanza nave según la tasa de avance en dirección a la punta de la nave. Actualiza los valores de la nave. 
*/
void nave_avanzar(nave_t *nave, double tasa_avance);





/*  
** Crea una nave con sus parámetros en 0 en memoria nueva. Si falla, devuelve null
*/
nave_t *nave_crear(void);

void nave_imprimir(SDL_Renderer *renderer, nave_t *nave, double escala, bool chorro);


#endif