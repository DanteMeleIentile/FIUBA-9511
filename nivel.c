#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h>


#include "nivel.h"
#include "config.h"
#include "lista.h"

#define X 0
#define Y 1


struct nivel {
    figura_t *fig;
    bool infinito;
    lista_t *torretas;
    lista_t *combustibles;
};

nivel_t *nivel_crear(figura_t *figura){
    nivel_t *nivel = malloc(sizeof(nivel_t));
    if(nivel == NULL) return NULL;

    nivel->fig = figura_clonar(figura);
    if(nivel->fig == NULL){
        free(nivel);
        return NULL;
    } 

    nivel->infinito = figura->infinito;

    nivel->torretas = lista_crear();
    if(nivel->torretas == NULL){
        free(nivel->fig);
        free(nivel);
        return NULL;
    } 

    nivel->combustibles = lista_crear();
    if(nivel->combustibles == NULL){
        free(nivel->torretas);
        free(nivel->fig);
        free(nivel);
        return NULL;
    } 

    return nivel;
}

figura_t *nivel_get_figura(nivel_t *nivel){
    return  nivel->fig;
}

lista_t *nivel_get_lista_torretas(nivel_t *nivel){
    return nivel->torretas;
}

lista_t *nivel_get_lista_combustibles(nivel_t *nivel){
    return nivel->combustibles;
}

void nivel_imprimir(SDL_Renderer *renderer, nivel_t *nivel, float escala){
    figura_imprimir(renderer, nivel->fig, escala, 0, 0);

}

void nivel_trasladar(nivel_t *nivel, float dx, float dy){
    figura_trasladar(nivel->fig, dx, dy);
}




