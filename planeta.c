
#include "figura.h"
#include "nave.h"
#include "fisicas.h"
#include "planeta.h"

#define X 0
#define Y 1

struct planeta {
    figura_t *fig;
    float pos[2];
};

planeta_t *planeta_crear(figura_t *figura, float x, float y){
    planeta_t *planeta = malloc(sizeof(planeta_t));
    if(planeta == NULL) return NULL;
    planeta->fig = figura_clonar(figura);
    if(planeta->fig == NULL){
        free(planeta);
        return NULL;
    }
    planeta_set_pos(planeta, x, y);

    figura_trasladar(planeta->fig, planeta->pos[X], planeta->pos[Y]);
    return planeta;
}

//GETTERS:

float planeta_get_pos_x(planeta_t *planeta){
    return planeta->pos[X];
}

float planeta_get_pos_y(planeta_t *planeta){
    return planeta->pos[Y];
}

void planeta_set_pos(planeta_t *planeta, float x, float y){
    planeta->pos[X] = x;
    planeta->pos[Y] = y;
}

void planeta_imprimir(SDL_Renderer *renderer, planeta_t *planeta, float escala, float escala_x, float escala_y, float tras_x, float tras_y){
    figura_imprimir(renderer, planeta->fig, escala, escala_x, escala_y, tras_x, tras_y);
}

double distancia_a_planeta(planeta_t *planeta, float pos_x, float pos_y){
    return distancia_punto_a_figura(planeta->fig, pos_x, pos_y);
}

void planeta_destruir(planeta_t *planeta){
    if(planeta == NULL) return;
    figura_destruir(planeta->fig);
    free(planeta);
}