#ifndef PLANETA_H
#define PLANETA_H

#include "figura.h"
#include "nave.h"



typedef struct {
    figura_t *figura;
    double x, y;
}planeta_t;

planeta_t planeta_crear(figura_t *figura, double x, double y);

//GETTERS

double planeta_get_pos_x(planeta_t planeta);

double planeta_get_pos_y(planeta_t planeta);

//SETTERS

void planeta_set_pos(planeta_t *planeta, double x, double y);

void planeta_dibujar(SDL_Renderer *renderer, const planeta_t planeta);

double distancia_a_planeta(planeta_t planeta, nave_t *nave);


#endif