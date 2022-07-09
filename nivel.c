#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h>


#include "nivel.h"
#include "config.h"

#define X 0
#define Y 1


struct nivel {
    figura_t *fig;
    float pos[2];
    bool infinito;
    size_t cant_torretas;
    size_t cant_combustible;
};

nivel_t *nivel_crear(figura_t *figura, size_t cant_torretas, size_t cant_combustible){
    nivel_t *nivel = malloc(sizeof(nivel_t));
    if(nivel == NULL) return NULL;

    nivel->fig = figura_clonar(figura);
    if(nivel->fig == NULL) return NULL;

    nivel->infinito = figura->infinito;

    nivel->cant_torretas = cant_torretas;

    nivel->cant_combustible = cant_combustible;

    nivel->pos[X] = -150 -989/2;
    nivel->pos[Y] = -150 -596/2;


    return nivel;
}

void nivel_imprimir(SDL_Renderer *renderer, nivel_t *nivel, float escala){
    figura_imprimir(renderer, nivel->fig, escala, nivel->pos[X], nivel->pos[Y]);
}

bool nivel_act_figura(nivel_t *nivel, figura_t *figura){
    nivel->fig = figura_clonar(figura);

    if(nivel->fig == NULL){
        free(nivel);
        return false;
    }

    figura_trasladar(nivel->fig, nivel->pos[X], nivel->pos[Y]);

    return true;
}

double nivel_get_pos_x(nivel_t *nivel){
    return nivel->pos[X];
}

double nivel_get_pos_y(nivel_t *nivel){
    return nivel->pos[Y];
}

void nivel_trasladar(nivel_t *nivel, float dx, float dy){
    figura_trasladar(nivel->fig, dx, dy);

    nivel->pos[X] = dx;
    nivel->pos[Y] = dy;
}



