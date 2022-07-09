#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h>


#include "nivel.h"
#include "config.h"



struct nivel {
    figura_t *figura;
    bool infinito;
    size_t cant_torretas;
    size_t cant_combustible;
};

nivel_t *nivel_crear(figura_t *figura, size_t cant_torretas, size_t cant_combustible){
    nivel_t *nivel = malloc(sizeof(nivel_t));
    if(nivel == NULL) return NULL;

    nivel->figura = figura_clonar(figura);
    if(nivel->figura == NULL) return NULL;

    nivel->infinito = figura->infinito;

    nivel->cant_torretas = cant_torretas;

    nivel->cant_combustible = cant_combustible;

    return nivel;
}

void nivel_imprimir(SDL_Renderer *renderer, nivel_t *nivel, float escala){
    figura_imprimir(renderer, nivel->figura, escala, 0, 0);
}


