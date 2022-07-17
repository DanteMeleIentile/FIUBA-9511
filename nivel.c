#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "nivel.h"
#include "config.h"

#define X 0
#define Y 1


struct nivel {
    figura_t *fig;
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


    return nivel;
}


float nivel_get_extremo_x(nivel_t *nivel, bool mayor){
    return figura_get_extremo_x(nivel->fig, mayor);
}


float nivel_get_extremo_y(nivel_t *nivel, bool mayor){
    return figura_get_extremo_y(nivel->fig, mayor);
}


void nivel_imprimir(SDL_Renderer *renderer, nivel_t *nivel, float escala, float pos_x, float pos_y){
    figura_imprimir(renderer, nivel->fig, escala, pos_x, pos_y);
}


void nivel_imprimir_tras(SDL_Renderer *renderer, nivel_t *nivel, float escala, float pos_x, float pos_y, float tras_x, float tras_y){
    figura_imprimir_tras(renderer, nivel->fig, escala, 0, 0, tras_x, tras_y);
}

void nivel_trasladar(nivel_t *nivel, float dx, float dy){
    figura_trasladar(nivel->fig, dx, dy);
}

nivel_t *nivel_clonar(const nivel_t *nivel){
    return nivel_crear(nivel->fig, nivel->cant_torretas, nivel->cant_combustible);
}