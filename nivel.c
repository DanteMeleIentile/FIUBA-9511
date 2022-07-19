#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "nivel.h"
#include "config.h"
#include "lista.h"
#include "reactor.h"

#define X 0
#define Y 1


struct nivel {
    figura_t *fig;
    bool infinito;
    lista_t *torretas;
    lista_t *combustibles;
    reactor_t *reactor;
    int bonus;
};

nivel_t *nivel_crear(figura_t *figura, reactor_t *reactor, int bonus){
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

    nivel->reactor = reactor;

    nivel->bonus = bonus;

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

int nivel_get_bonus(nivel_t *nivel){
    return nivel->bonus;
}

bool nivel_es_infinito(nivel_t *nivel){
    return nivel->infinito;
}

void nivel_reactor_destruir(nivel_t *nivel){
    reactor_destruir(nivel->reactor);
}

float nivel_get_extremo_x(nivel_t *nivel, bool mayor){
    return figura_get_extremo_x(nivel->fig, mayor);
}

float nivel_get_extremo_y(nivel_t *nivel, bool mayor){
    return figura_get_extremo_y(nivel->fig, mayor);
}

void nivel_destruir(nivel_t *nivel){
    figura_destruir(nivel->fig);
    if(nivel->reactor != NULL) reactor_destruir(nivel->reactor);
}


nivel_t *nivel_clonar(const nivel_t *nivel){
    return nivel_crear(nivel->fig, nivel->reactor, nivel->bonus);
}

void nivel_imprimir(SDL_Renderer *renderer, nivel_t *nivel, float escala, float escala_x, float escala_y, float tras_x, float tras_y){

    figura_imprimir(renderer, nivel->fig, escala, escala_x, escala_y, tras_x, tras_y);
    if(nivel->infinito){
        float shift_der = nivel_get_extremo_x(nivel, true) * escala;
        float shift_izq = - shift_der;
        //Impresión a derecha
        figura_imprimir(renderer, nivel->fig, escala, escala_x, escala_y, tras_x + shift_der, tras_y);
        //Impresión a izquierda
        figura_imprimir(renderer, nivel->fig, escala, escala_x, escala_y, tras_x + shift_izq, tras_y);
    }
}