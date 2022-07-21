#ifndef _LETRAS_H_
#define _LETRAS_H_

#include "color.h"
#include <SDL2/SDL.h>


#define CARACTER_ANCHO 6
#define CARACTER_ALTO 6

extern const int caracter_a[7][2];
extern const int caracter_b[12][2];
extern const int caracter_c[4][2];
extern const int caracter_d[7][2];
extern const int caracter_e[7][2];
extern const int caracter_f[6][2];
extern const int caracter_g[7][2];
extern const int caracter_h[6][2];
extern const int caracter_i[6][2];
extern const int caracter_j[4][2];
extern const int caracter_k[6][2];
extern const int caracter_l[3][2];
extern const int caracter_m[5][2];
extern const int caracter_n[4][2];
extern const int caracter_o[5][2];
extern const int caracter_p[5][2];
extern const int caracter_q[9][2];
extern const int caracter_r[7][2];
extern const int caracter_s[6][2];
extern const int caracter_t[4][2];
extern const int caracter_u[4][2];
extern const int caracter_v[3][2];
extern const int caracter_w[5][2];
extern const int caracter_x[5][2];
extern const int caracter_y[5][2];
extern const int caracter_z[4][2];

extern const int caracter_0[5][2];
extern const int caracter_1[2][2];
extern const int caracter_2[6][2];
extern const int caracter_3[7][2];
extern const int caracter_4[5][2];
extern const int caracter_5[6][2];
extern const int caracter_6[5][2];
extern const int caracter_7[3][2];
extern const int caracter_8[7][2];
extern const int caracter_9[5][2];

extern const int caracter_derecha[5][2];
extern const int caracter_izquierda[5][2];
extern const int caracter_arriba[5][2];
extern const int caracter_abajo[5][2];

extern const int caracter_espacio[1][2];

extern const int caracter_nave[9][2];

/*
** Imprime "cadena" en la pantalla escalado "escala" y en la posición dada.
*/
void cadena_imprimir(SDL_Renderer *renderer, const char *cadena, float pos_x, float pos_y, double escala, color_t color);

/*
** Imprime "cadena" en la pantalla escalado "escala" y en la posición dada y centrado a esa posicion.
*/
void cadena_imprimir_centrado(SDL_Renderer *renderer, const char *cadena, float pos_x, float pos_y, double escala, color_t color);

/*
** Imprime "numero" en la pantalla escalado "escala" y en la posición dada.
** PRE: el numero no puede superar las 15 cifras
*/
void entero_imprimir(SDL_Renderer *renderer, int numero, float pos_x, float pos_y, double escala, color_t color);

/*
** Imprime "numero" en la pantalla escalado "escala" y en la posición dada y centrado a esa posicion.
** PRE: el numero no puede superar las 15 cifras.
*/
void entero_imprimir_centrado(SDL_Renderer *renderer, int numero, float pos_x, float pos_y, double escala, color_t color);

#endif // _LETRAS_H_
