#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#include "torreta.h"
#include "figura.h"
#include "fisicas.h"
#include "config.h"

#define X 0
#define Y 1

struct torreta {
    figura_t *fig;
    figura_t *fig_disparo;
    float pos[2];
    double angulo;
    double angulo_apuntado;
    double cooldown;
    bool estado;
};

torreta_t *torreta_crear(double cooldown, float pos_x, float pos_y, double angulo){
    torreta_t *torreta = malloc(sizeof(torreta_t));
    if(torreta == NULL) return NULL;

    torreta->pos[X] = pos_x;
    torreta->pos[Y] = pos_y;
    torreta->angulo = angulo;
    torreta->angulo_apuntado = 0;

    torreta->cooldown = cooldown;

    return torreta;
}

double torreta_get_cooldown(torreta_t *torreta){
    return torreta->cooldown;
}

void torreta_restar_cooldown(torreta_t *torreta, double t){
    torreta->cooldown -= t;
}

double torreta_get_pos_x(torreta_t *torreta){
    return torreta->pos[X];
}

double torreta_get_pos_y(torreta_t *torreta){
    return torreta->pos[Y];
}

double torreta_get_angulo_apuntado(torreta_t *torreta){
    return torreta->angulo_apuntado;
}

figura_t *torreta_get_figura_principal(torreta_t *torreta){
    return torreta->fig;
}

double torreta_get_angulo(torreta_t *torreta){
    return torreta->angulo;
}

void torreta_set_cooldown(torreta_t *torreta, double t){
    torreta->cooldown = t;
}

bool torreta_apuntar(torreta_t *torreta, float x_objetivo, float y_objetivo){
    double angulo = computar_angulo(torreta->pos[X], torreta->pos[Y], x_objetivo, y_objetivo);

    if(angulo > (torreta->angulo + PI) || angulo < (torreta->angulo - PI/2)){
        return false;
    }
    
    torreta->angulo_apuntado = angulo;
    return true;
}

bool torreta_act_figura(torreta_t *torreta, figura_t *fig, figura_t *fig_disparo){
    torreta->fig = figura_clonar(fig);

    if(torreta->fig == NULL) return false;
    torreta->fig_disparo = figura_clonar(fig_disparo);

    if(torreta->fig_disparo == NULL){
        figura_destruir(fig);
        return false;
    }

    figura_rototrasladar(torreta->fig, torreta->pos[X], torreta->pos[Y], torreta->angulo);
    figura_rototrasladar(torreta->fig_disparo, torreta->pos[X], torreta->pos[Y], torreta->angulo);
    return true;
}

void torreta_setear_en_lugar(torreta_t *torreta, float pos_x, float pos_y, double angulo){
    torreta->pos[X] = pos_x;
    torreta->pos[Y] = pos_y;

    torreta->angulo = angulo;
}

void torreta_destruir(torreta_t *torreta){
    figura_destruir(torreta->fig);
    figura_destruir(torreta->fig_disparo);

    free(torreta);
}

void torreta_imprimir(SDL_Renderer *renderer, torreta_t *torreta, float escala, float escala_x, float escala_y, float tras_x, float tras_y, bool disparo){
    if(disparo){
        figura_imprimir(renderer, torreta->fig_disparo, escala, escala_x, escala_y, tras_x, tras_y);
    }else{
        figura_imprimir(renderer, torreta->fig, escala, escala_x, escala_y, tras_x, tras_y);
    }
}
