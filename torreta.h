#ifndef TORRETA_H
#define TORRETA_H

#include "figura.h"

// INVARIANTES: Angulos se encuentran en radianes, entre 0 y 2 PI

struct torreta;

typedef struct torreta torreta_t;

torreta_t *torreta_crear(void);

/*
** Devuelve la posicion en "x" de la torreta
*/
double torreta_get_pos_x(torreta_t *torreta);

/*
** Devuelve la posicion en "y" de la torreta
*/
double torreta_get_pos_y(torreta_t *torreta);

/*
** Devuelve el angulo de apuntado de la torreta
*/
double torreta_get_angulo_apuntado(torreta_t *torreta);

/*
** Devuelve el cooldown de la torreta
*/
double torreta_get_cooldown(torreta_t *torreta);

/*
** Setea el cooldown de la torreta
*/
void torreta_set_cooldown(torreta_t *torreta, double t);

/*
** Resta "t" al cooldown de la torreta
*/
void torreta_restar_cooldown(torreta_t *torreta, double t);

/*
** Setea el la posicion y el angulo de rotacion de la torreta dada
*/
void torreta_setear_en_lugar(torreta_t *torreta, double pos_x, double pos_y, double angulo);

/*
** Setea el angulo de apuntado de la torreta hacia las cordenadas centro_x y centro_y
** Devuelve bool si pudo apuntar, caso contrario devuelve false
*/
bool torreta_apuntar(torreta_t *torreta, double x_objetivo, double y_objetivo);

/*
** Actualiza las 2 figuras de la torreta según los parametros de la misma (posición y ángulo).
** PRE: La torreta fue creada.
** El angulo de apuntado son +90 y -90 grados
*/
bool torreta_act_figura(torreta_t *torreta, figura_t *fig, figura_t *fig_disparo);

/*
** Destruye la torreta dada
*/
void torreta_destruir(torreta_t *torreta);

/*
** Imprime la torreta dada
*/
void torreta_imprimir(SDL_Renderer *renderer, torreta_t *torreta, double escala, bool disparo);

//SPAWN TORRETA EN POSICION XY Y ROTARLO UN ANGULO, Y QUE DISPARE

#endif