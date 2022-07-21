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

combustible_t *combustible_crear(const figura_t *figura, float pos_x, float pos_y, double angulo){
    combustible_t *combustible = malloc(sizeof(combustible_t));
    if(combustible == NULL) return NULL;
    combustible->fig = figura_clonar(figura);
    if(combustible->fig == NULL){
        free(combustible);
        return NULL;
    }

    combustible->pos[X] = pos_x;
    combustible->pos[Y] = pos_y;
    combustible->angulo = angulo;

    figura_rototrasladar(combustible->fig, combustible->pos[X], combustible->pos[Y], combustible->angulo);

    return combustible;
}

/* bool combustible_act_figura(combustible_t *combustible, figura_t *figura){
    if(combustible->fig != NULL) figura_destruir(combustible->fig);
    combustible->fig = figura_clonar(figura);

    if(combustible->fig == NULL) return false;
    figura_rototrasladar(combustible->fig, combustible->pos[X], combustible->pos[Y], combustible->angulo);
    return true;
} */

float combustible_get_pos_x(combustible_t *combustible){
    return combustible->pos[X];
}

float combustible_get_pos_y(combustible_t *combustible){
    return combustible->pos[Y];
}

void combustible_destruir(combustible_t *combustible){
    if(combustible == NULL) return;
    if(combustible->fig != NULL) figura_destruir(combustible->fig);
    free(combustible);
}

void combustible_imprimir(SDL_Renderer *renderer, combustible_t *combustible, float escala, float escala_x, float escala_y, float tras_x, float tras_y){
    figura_imprimir(renderer, combustible->fig, escala, escala_x, escala_y, tras_x, tras_y);
}