#include <SDL2/SDL.h>

#include "planeta.h"
#include "figura.h"

planeta_t planeta_crear(figura_t *figura, float x, float y){
    planeta_t planeta;
    planeta.figura = figura;
    planeta.x = x;
    planeta.y = y;
    return planeta;
}

void planeta_dibujar(SDL_Renderer *renderer, const planeta_t planeta){
    figura_t *planeta_fig = figura_clonar(planeta.figura);

    figura_trasladar(planeta_fig, planeta.x, planeta.y);
    figura_imprimir(renderer, planeta_fig, 1, planeta.x, planeta.y);
    figura_destruir(planeta_fig);
}