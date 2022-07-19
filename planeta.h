#ifndef PLANETA_H
#define PLANETA_H

#include "figura.h"
#include "nave.h"

typedef struct{
    figura_t *figura;
    double x, y;
}planeta_t;

planeta_t planeta_crear(figura_t *figura, double x, double y);

//GETTERS

double planeta_get_pos_x(planeta_t planeta);

double planeta_get_pos_y(planeta_t planeta);

//SETTERS

void planeta_set_pos(planeta_t *planeta, double x, double y);

void planeta_imprimir(SDL_Renderer *renderer, planeta_t planeta, float escala, float escala_x, float escala_y, float tras_x, float tras_y);

double distancia_a_planeta(planeta_t planeta, double pos_x, double pos_y);


#endif