#include <SDL2/SDL.h>
#include <stdlib.h>

#include "reactor.h"
#include "nivel.h"
#include "figura.h"

#define X 0
#define Y 1

struct reactor {
    figura_t *fig;
    float pos[2];
    double angulo;
};

reactor_t *reactor_crear(figura_t *figura, float x, float y, double angulo){
    reactor_t *reactor = malloc(sizeof(reactor_t));
    if(reactor == NULL) return NULL;

    reactor->fig = figura_clonar(figura);
    if(reactor->fig == NULL){
        free(reactor);
        return NULL;
    }

    reactor->pos[X] = x;
    reactor->pos[Y] = y;

    reactor->angulo = angulo;

    figura_rotar(reactor->fig, reactor->angulo);
    figura_trasladar(reactor->fig, reactor->pos[X], reactor->pos[Y]);
    
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

void reactor_imprimir(SDL_Renderer *renderer, const reactor_t *reactor, float escala, float escala_x, float escala_y, float tras_x, float tras_y){
    figura_imprimir(renderer, reactor->fig, escala, escala_x, escala_y, tras_x, tras_y);
}

void reactor_destruir(reactor_t *reactor){
    if(reactor == NULL) return;
    figura_destruir(reactor->fig);
    free(reactor);
}