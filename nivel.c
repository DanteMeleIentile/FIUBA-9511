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

figura_t *nivel_get_figura(nivel_t *nivel){
    return  nivel->fig;
}

void nivel_imprimir(SDL_Renderer *renderer, nivel_t *nivel, float escala){
    nivel_trasladar(nivel, 0, 56*escala);
    figura_imprimir(renderer, nivel->fig, escala, 0, 56*escala);

}

void nivel_trasladar(nivel_t *nivel, float dx, float dy){
    figura_trasladar(nivel->fig, dx, dy);
}




