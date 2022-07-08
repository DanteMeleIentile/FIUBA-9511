#include <SDL2/SDL.h>

#include "planeta.h"
#include "figura.h"
#include "nave.h"

planeta_t planeta_crear(figura_t *figura, double x, double y){
    planeta_t planeta;
    planeta.figura = figura;
    planeta_set_pos(&planeta, x, y);
    return planeta;
}

//GETTERS:

double planeta_get_pos_x(planeta_t planeta){
    return planeta.x;
}

double planeta_get_pos_y(planeta_t planeta){
    return planeta.y;
}

void planeta_set_pos(planeta_t *planeta, double x, double y){
    planeta->x = x;
    planeta->y = y;
}

void planeta_dibujar(SDL_Renderer *renderer, const planeta_t planeta){
    figura_t *planeta_fig = figura_clonar(planeta.figura);

    figura_trasladar(planeta_fig, planeta.x, planeta.y);
    figura_imprimir(renderer, planeta_fig, 1, planeta.x, planeta.y);
    figura_destruir(planeta_fig);
}

double distancia_a_planeta(planeta_t planeta, nave_t *nave){
    return distancia_punto_a_figura(nave->fig, planeta.x, planeta.y);
}