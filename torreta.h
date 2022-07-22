#ifndef TORRETA_H
#define TORRETA_H

#include "figura.h"

// INVARIANTES: Angulos se encuentran en radianes, entre 0 y 2 PI
struct torreta;

typedef struct torreta torreta_t;

/*
** Crea la torreta en posicion y angulo dado.
*/
torreta_t *torreta_crear(const figura_t *figura1, const figura_t *figura2, double cooldown, float pos_x, float pos_y, double angulo);

/*
** Devuelve la posicion en "x" de la torreta
*/
float torreta_get_pos_x(torreta_t *torreta);

/*
** Devuelve la posicion en "y" de la torreta
*/
float torreta_get_pos_y(torreta_t *torreta);

/*
** Devuelve el angulo de apuntado de la torreta
*/
double torreta_get_angulo_apuntado(torreta_t *torreta);

/*
** Devuelve la figura principal (actual) de la torreta
*/
figura_t *torreta_get_figura_principal(torreta_t *torreta);

/*
** Devuelve el angulo de rotacion de la torreta
*/
double torreta_get_angulo(torreta_t *torreta);

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
** Setea la posicion y el angulo de rotacion de la torreta dada
*/
void torreta_setear_en_lugar(torreta_t *torreta, float pos_x, float pos_y, double angulo);

/*
** Setea el angulo de apuntado de la torreta hacia las cordenadas centro_x y centro_y
** Devuelve bool si pudo apuntar, caso contrario devuelve false
*/
bool torreta_apuntar(torreta_t *torreta, float x_objetivo, float y_objetivo);

/*
** Imprime la torreta dada
*/
void torreta_imprimir(SDL_Renderer *renderer, const torreta_t *torreta, float escala, float escala_x, float escala_y, float tras_x, float tras_y, bool disparo);

/*
** Libera la memoria de la torreta.
*/
void torreta_destruir(torreta_t *torreta);

#endif //TORRETA_H