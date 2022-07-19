#include <SDL2/SDL.h>

#include "planeta.h"
#include "figura.h"
#include "nave.h"
#include "fisicas.h"

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

void planeta_imprimir(SDL_Renderer *renderer, planeta_t planeta, float escala, float escala_x, float escala_y, float tras_x, float tras_y){
    figura_t *planeta_fig = figura_clonar(planeta.figura);

    figura_trasladar(planeta_fig, planeta.x, planeta.y);
    figura_imprimir(renderer, planeta_fig, escala, escala_x, escala_y, tras_x, tras_y);
    figura_destruir(planeta_fig);
}

double distancia_a_planeta(planeta_t planeta, double pos_x, double pos_y){
    return distancia_entre_puntos(pos_x, pos_y, planeta.x, planeta.y);
}