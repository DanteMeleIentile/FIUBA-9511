#include <SDL2/SDL.h>

#include "reactor.h"
#include "nivel.h"
#include "figura.h"

#define X 0
#define Y 1

struct reactor {
    figura_t *fig;
    float pos[2];
};

reactor_t *reactor_crear(figura_t *figura, float x, float y, double angulo){
    reactor_t *reactor = malloc(sizeof(reactor));
    if(reactor == NULL) return NULL;

    reactor->fig = figura_clonar(figura);
    if(reactor->fig == NULL){
        free(reactor);
        return NULL;
    }
    figura_rototrasladar(reactor->fig, x, y, angulo);

    reactor->pos[X] = x;
    reactor->pos[Y] = y;
    return reactor;
}

float reactor_get_pos_x(reactor_t *reactor){
    return reactor->pos[X];
}

float reactor_get_pos_y(reactor_t *reactor){
    return reactor->pos[Y];
}

figura_t *reactor_get_figura(reactor_t *reactor){
    return reactor->fig;
}

void reactor_imprimir(SDL_Renderer *renderer, reactor_t *reactor, float escala){
    figura_imprimir(renderer, reactor->fig, escala, reactor->pos[X], reactor->pos[Y]);
}

void reactor_destruir(reactor_t *reactor){
    figura_destruir(reactor->fig);
    free(reactor);
}