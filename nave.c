#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>

#include "nave.h"
#include "figura.h"
#include "fisicas.h"

#define PI 3.14159265358979323846
#define X 0
#define Y 1


struct nave {
    figura_t *fig;                  //La figura principal de la nave
    figura_t *fig_chorro;           //La figura del chorro de propulsion
    figura_t *fig_escudo;           //La figura del escudo principal
    figura_t *fig_escudo_nivel;     //La figura secundaria del escudo (el tractor beam para el combustible)
    float pos[2];
    float vel[2];
    double angulo;                  //Ángulo de la nave
    double angulo_escudo;           //Ángulo de la figura secundaria del escudo
    uint8_t estado;                 //Determina cual figura utilizar
    int cant_combustible;
    int cant_vidas;
};


static double DEG_A_RAD(double grados){
    return grados * PI / 180;
}

nave_t *nave_crear(int cant_combustible){
    nave_t *nave = malloc(sizeof(nave_t));
    if(nave == NULL) return NULL;

    nave->angulo = DEG_A_RAD(0);

    nave->pos[X] = 0;
    nave->pos[Y] = 0;

    nave->vel[X] = 0;
    nave->vel[Y] = 0;

    nave->estado = 0;

    nave->cant_combustible = cant_combustible;

    nave->fig = NULL;
    nave->fig_chorro = NULL;
    nave->fig_escudo = NULL;
    nave->fig_escudo_nivel = NULL;

    return nave;
}

float nave_get_pos_x(nave_t *nave){
    return nave->pos[X];
}

float nave_get_pos_y(nave_t *nave){
    return nave->pos[Y];
}

float nave_get_vel_x(nave_t *nave){
    return nave->vel[X];
}

float nave_get_vel_y(nave_t *nave){
    return nave->vel[Y];
}

double nave_get_angulo(nave_t *nave){
    return nave->angulo;
}

figura_t *nave_get_figura_principal(nave_t *nave){
    return nave->fig;
}

int nave_get_combustible(nave_t *nave){
    return nave->cant_combustible;
}

int nave_get_vidas(nave_t *nave){
    return nave->cant_vidas;
}


bool nave_estado_escudo(nave_t *nave){
    if(((nave->estado >> 2) % 2) || ((nave->estado >> 1) % 2)){
        return true;
    }
    return false;
}


bool nave_estado_escudo_nivel(nave_t *nave){
    if((nave->estado >> 2) % 2){
        return true;
    }
    return false;
}

void nave_setear_posicion(nave_t *nave, float x, float y, double angulo){
    nave->pos[X] = x;
    nave->pos[Y] = y;
    nave->angulo = angulo;
}

void nave_setear_velocidad(nave_t *nave, float vel_x, float vel_y){
    nave->vel[X] = vel_x;
    nave->vel[Y] = vel_y;
}

void nave_set_vidas(nave_t *nave, int set){
    nave->cant_vidas = set;
}

void nave_agregar_vida(nave_t *nave){
    nave->cant_vidas ++;
}

void nave_quitar_vida(nave_t *nave){
    nave->cant_vidas --;
}

void nave_prender(nave_t *nave, bool chorro, bool escudo, bool escudo_nivel){
    if(chorro && !((nave->estado) % 2)){
        nave->estado += 1;
    }
    
    if(escudo && !((nave->estado >> 1) % 2)){
        nave->estado += 2;
    }

    if(escudo_nivel && !((nave->estado >> 2) % 2)){
        nave->estado += 4;
    }
}

void nave_apagar(nave_t *nave, bool chorro, bool escudo, bool escudo_nivel){
    if(chorro && ((nave->estado) % 2)){
        nave->estado -= 1;
    }
    
    if(escudo && ((nave->estado >> 1) % 2)){
        nave->estado -= 2;
    }

    if(escudo_nivel && ((nave->estado >> 2) % 2)){
        nave->estado -= 4;
    }
}

bool nave_act_figura(nave_t *nave, const figura_t *nave_fig, const figura_t *nave_mas_chorro_fig, const figura_t *escudo_fig, const figura_t *escudo_nivel_fig){

    if(nave->fig != NULL){
        figura_destruir(nave->fig);
        figura_destruir(nave->fig_chorro);
        figura_destruir(nave->fig_escudo);
        figura_destruir(nave->fig_escudo_nivel);
    }

    nave->fig = figura_clonar(nave_fig);
    if(nave->fig == NULL){
        return false;
    }
    nave->fig_chorro = figura_clonar(nave_mas_chorro_fig);
    if(nave->fig == NULL){
        figura_destruir(nave->fig);
        return false;
    }
    nave->fig_escudo = figura_clonar(escudo_fig);
    if(nave->fig_escudo == NULL){
        figura_destruir(nave->fig);
        figura_destruir(nave->fig_chorro);
        return false;
    }
    nave->fig_escudo_nivel = figura_clonar(escudo_nivel_fig);
    if(nave->fig_escudo_nivel == NULL){
        figura_destruir(nave->fig);
        figura_destruir(nave->fig_chorro);
        figura_destruir(nave->fig_escudo);
        return false;
    }

    if(nave->angulo != 0){
        figura_rotar(nave->fig, nave->angulo);
        figura_rotar(nave->fig_chorro, nave->angulo);
        figura_rotar(nave->fig_escudo, nave->angulo);
        figura_rotar(nave->fig_escudo_nivel, nave->angulo_escudo);
    }

    if(!(nave->pos[X] == 0 && nave->pos[Y] == 0)){
        figura_trasladar(nave->fig, nave->pos[X], nave->pos[Y]);
        figura_trasladar(nave->fig_chorro, nave->pos[X], nave->pos[Y]);
        figura_trasladar(nave->fig_escudo, nave->pos[X], nave->pos[Y]);
        figura_trasladar(nave->fig_escudo_nivel, nave->pos[X], nave->pos[Y]);
    }
    return true;
}

void nave_rotar(nave_t *nave, double angulo){
    nave->angulo += angulo;

    while(nave->angulo > 2 * PI)
        nave->angulo = nave->angulo- (2 * PI);

    while(nave->angulo < 0)
        nave->angulo = nave->angulo + (2 * PI);
}

void nave_escudo_setear_angulo(nave_t *nave, double angulo){

    nave->angulo_escudo = angulo;

    while(nave->angulo_escudo > 2 * PI)
        nave->angulo_escudo = nave->angulo_escudo - (2 * PI);

    while(nave->angulo_escudo < 0)
        nave->angulo_escudo = nave->angulo_escudo + (2 * PI);
}

/*
** FUNCIÓN INTERNAS TDA
** Dado el módulo de la aceleración, su ángulo y un intervalo de tiempo, computa ambas componentes de velocidad
*/
static void nave_aceleracion(nave_t *nave, float aceleracion, double rad, double dt){
    nave->vel[X] = computar_velocidad(nave->vel[X], aceleracion * cos(rad), dt);
    nave->vel[Y] = computar_velocidad(nave->vel[Y], aceleracion * sin(rad), dt);
}

/*
** FUNCIÓN INTERNAS TDA
** Dado un intervalo de tiempo, computa ambas componentes de posición según la velocidad "inicial" de la nave
*/
static void nave_velocidad(nave_t *nave, double dt){
    nave->pos[X] = computar_posicion(nave->pos[X], nave->vel[X], dt);
    nave->pos[Y] = computar_posicion(nave->pos[Y], nave->vel[Y], dt);
}

void nave_avanzar(nave_t *nave, float aceleracion, double dt){
    nave_aceleracion(nave, aceleracion, nave->angulo, dt);
    nave_velocidad(nave, dt);
}

void nave_acercar(nave_t *nave, float aceleracion, float centro_x, float centro_y, double dt){
    double angulo = computar_angulo(nave->pos[X], nave->pos[Y], centro_x, centro_y);
    nave_acercar_direccion(nave, aceleracion, angulo, dt);
}

void nave_acercar_direccion(nave_t *nave, float aceleracion, double angulo, double dt){
    while(angulo > 2 * PI)
        angulo = angulo- (2 * PI);

    while(angulo < 0)
        angulo = angulo + (2 * PI);

    nave_aceleracion(nave, aceleracion, angulo, dt);
    nave_velocidad(nave, dt);
}


void nave_invertir_vel_x(nave_t *nave){
    nave->vel[X] = -nave->vel[X];
}

void nave_invertir_vel_y(nave_t *nave){
    nave->vel[Y] = -nave->vel[Y];
}

void nave_sumar_combustible(nave_t *nave, int combustible){
    nave->cant_combustible += combustible;
}

bool nave_escudo_apuntar(nave_t *nave, float x_objetivo, float y_objetivo){
    double angulo = computar_angulo(x_objetivo, y_objetivo, nave->pos[X], nave->pos[Y]);    
    nave->angulo_escudo = angulo - PI/2;
    return true;
}

void nave_imprimir(SDL_Renderer *renderer, const nave_t *nave, float escala, float escala_x, float escala_y, float tras_x, float tras_y){
    if((nave->estado % 2)){
        figura_imprimir(renderer, nave->fig_chorro, escala, escala_x, escala_y, tras_x, tras_y);
    } else {
        figura_imprimir(renderer, nave->fig, escala, escala_x, escala_y, tras_x, tras_y);
    }

    if((nave->estado >> 1) % 2){
        figura_imprimir(renderer, nave->fig_escudo, escala, escala_x, escala_y, tras_x, tras_y);
    } else if((nave->estado >> 2) % 2){
        figura_imprimir(renderer, nave->fig_escudo_nivel, escala, escala_x, escala_y, tras_x, tras_y);
    }
}

void nave_destruir(nave_t *nave){
    if(nave == NULL) return;
    if(nave->fig != NULL){
        figura_destruir(nave->fig);
        figura_destruir(nave->fig_chorro);
        figura_destruir(nave->fig_escudo);
        figura_destruir(nave->fig_escudo_nivel);
    }
    free(nave);
}