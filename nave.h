#ifndef NAVE_H
#define NAVE_H

#include <SDL2/SDL.h>

#include "figura.h"

typedef struct{
    figura_t *nave_fig;
    figura_t *nave_fig_mas_chorro;
    double angulo;
    double vel[2];
    double pos[2];
    //int cant_combustible;
} nave_t;

/*  
** Crea una nave con sus parámetros en 0 en memoria nueva. Si falla, devuelve null
*/
nave_t *nave_crear(void);

/*  
** Iniciliza/actualiza la figura de la nave recibida.
** PRE: La nave fue creada.
** POST: La figura de la nave es igual a "figura" 
*/ 
void nave_inicializar(nave_t *nave, figura_t *figura_nave, figura_t *fig_nave_mas_chorro);

/*  
** Rota la nave un angulo "angulo" y actualiza el valor de "angulo_actual". "Angulo actual" siempre se encontrará entre [0 y 2 PI]
*/
void nave_rotar(nave_t *nave, double angulo);

/*  
** Traslada la nave una distancia "dx" en "x" y una distancia en "dy" en "y" y actualiza los valores de posicion de la nave.
*/
void nave_trasladar(nave_t *nave, double dx, double dy);

/*
** Setea la posicion de la nave a la dada en "dx" y "dy" con respecto al origen de coordenadas (coord. absolutas).
** PRE: "nave" fue creada
** POST: Actualiza los parámetros de posición de "nave" según las coordenadas dadas.
*/
void nave_setear_posicion(nave_t *nave, double dx, double dy);



//VELOCIDAD
void nave_impulso(nave_t *nave);

//CHORRO
void nave_aceleracion(nave_t *nave, double a, double rad);



//nave_clonar(dx, dy);

//nave_status(dx, dy);

//nave_status(dx, dy2);

void nave_imprimir(SDL_Renderer *renderer, nave_t *nave, double escala, bool chorro);


#endif