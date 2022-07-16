#include <stdlib.h>
#include <SDL2/SDL.h>
#include "combustible.h"
#include "figura.h"

#define X 0
#define Y 1

struct combustible{
    figura_t *fig;
    float pos[2];
    double angulo;
};

combustible_t *combustible_crear(float pos_x, float pos_y, double angulo){
    combustible_t *combustible = malloc(sizeof(combustible));
    if(combustible == NULL) return NULL;

    combustible->pos[X] = pos_x;
    combustible->pos[Y] = pos_y;
    combustible->angulo = angulo;
    return combustible;
}

void combustible_act_figura(combustible_t *combustible, figura_t *figura){
    combustible->fig = figura_clonar(figura);
    if(combustible->fig == NULL) return NULL;
    figura_rototrasladar(combustible->fig, combustible->pos[X], combustible->pos[Y], combustible->angulo);
}

float combustible_get_pos_x(combustible_t *combustible){
    return combustible->pos[X];
}

float combustible_get_pos_y(combustible_t *combustible){
    return combustible->pos[Y];
}

void combustible_imprimir(SDL_Renderer *renderer, combustible_t *combustible, float escala){
    figura_imprimir(renderer, combustible->fig, escala, combustible->pos[X], combustible->pos[Y]);
}