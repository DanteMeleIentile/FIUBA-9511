#include <SDL2/SDL.h>

#include "planeta.h"
#include "figura.h"


planeta_t posicionar_planeta(SDL_Renderer *renderer, const figura_t *figura, float x, float y){
    figura_t *planeta_fig = figura_clonar(figura);

    figura_trasladar(planeta_fig, x, y);
    figura_imprimir(renderer, planeta_fig, 1, x, y);
    figura_destruir(planeta_fig);
    
    planeta_t planeta;

    planeta.x = x;
    planeta.y = y;

    return planeta;
}