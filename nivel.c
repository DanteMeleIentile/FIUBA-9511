#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "nivel.h"
#include "lista.h"
#include "torreta.h"
#include "combustible.h"

#define X 0
#define Y 1

struct nivel {
    figura_t *fig;
    bool infinito;
    lista_t *torretas;
    lista_t *combustibles;
    int bonus;
    size_t id; 
};

nivel_t *nivel_crear(const figura_t *figura, size_t id){
    nivel_t *nivel = malloc(sizeof(nivel_t));
    if(nivel == NULL) return NULL; 

    if(figura != NULL){
        nivel->fig = figura_clonar(figura);
        if(nivel->fig == NULL){
            free(nivel);
            return NULL;
        } 

        nivel->infinito = figura_get_infinito(figura);
    } else{
        nivel->fig = NULL;
        nivel->infinito = false;
    }

    nivel->torretas = lista_crear();
    if(nivel->torretas == NULL){
        figura_destruir(nivel->fig);
        free(nivel);
        return NULL;
    } 

    nivel->combustibles = lista_crear();
    if(nivel->combustibles == NULL){
        free(nivel->torretas);
        figura_destruir(nivel->fig);
        free(nivel);
        return NULL;
    }

    nivel->bonus = 0;
    nivel->id = id;
    return nivel;
}

figura_t *nivel_get_figura(const nivel_t *nivel){
    return nivel->fig;
}

lista_t *nivel_get_lista_torretas(const nivel_t *nivel){
    return nivel->torretas;
}

lista_t *nivel_get_lista_combustibles(const nivel_t *nivel){
    return nivel->combustibles;
}

int nivel_get_bonus(const nivel_t *nivel){
    return nivel->bonus;
}

bool nivel_get_infinito(const nivel_t *nivel){
    return nivel->infinito;
}

float nivel_get_extremo_x(const nivel_t *nivel, bool mayor){
    if(nivel->fig == NULL) return 0;
    return figura_get_extremo_x(nivel->fig, mayor);
}

float nivel_get_extremo_y(const nivel_t *nivel, bool mayor){
    if(nivel->fig == NULL) return 0;
    return figura_get_extremo_y(nivel->fig, mayor);
}

size_t nivel_get_id(const nivel_t *nivel){
    return nivel->id;
}

void nivel_set_bonus(nivel_t *nivel, int n){
    nivel->bonus = n;
}

void nivel_imprimir(SDL_Renderer *renderer, const nivel_t *nivel, float escala, float escala_x, float escala_y, float tras_x, float tras_y){
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

void nivel_destruir(nivel_t *nivel){
    if(nivel == NULL) return;
    figura_destruir(nivel->fig);
    lista_destruir(nivel->torretas, (void (*)(void*))torreta_destruir);
    lista_destruir(nivel->combustibles, (void (*)(void*))combustible_destruir);
    free(nivel);
}