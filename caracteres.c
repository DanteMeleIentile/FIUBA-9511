#include "caracteres.h"
#include "color.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string.h>

#define VENTANA_ANCHO 800
#define VENTANA_ALTO 600

#define EJE_X 0
#define EJE_Y 1

#define SHIFT 6

#define CANT_CARACTERES 42


const int caracter_a[7][2] = {
	{0, 0},
	{0, 4},
	{2, 6},
	{4, 4},
	{4, 0},
	{4, 2},
	{0, 2}
};

const int caracter_b[12][2] = {
	{0, 3},
	{0, 6},
	{3, 6},
	{4, 5},
	{4, 4},
	{3, 3},
	{0, 3},
	{0, 0},
	{3, 0},
	{4, 1},
	{4, 2},
	{3, 3},
};

const int caracter_c[4][2] = {
	{4, 0},
	{0, 0},
	{0, 6},
	{4, 6},
};

const int caracter_d[7][2] = {
	{0, 0},
	{0, 6},
	{2, 6},
	{4, 4},
	{4, 2},
	{2, 0},
	{0, 0}
};

const int caracter_e[7][2] = {
	{4, 0},
	{0, 0},
	{0, 3},
	{3, 3},
	{0, 3},
	{0, 6},
	{4, 6},
};

const int caracter_f[6][2] = {
	{0, 0},
	{0, 3},
	{3, 3},
	{0, 3},
	{0, 6},
	{4, 6},
};

const int caracter_g[7][2] = {
	{2, 2},
	{4, 2},
	{4, 0},
	{0, 0},
	{0, 6},
	{4, 6},
	{4, 4},
};

const int caracter_h[6][2] = {
	{0, 0},
	{0, 6},
	{0, 3},
	{4, 3},
	{4, 6},
	{4, 0},
};

const int caracter_i[6][2] = {
	{0, 0},
	{4, 0},
	{2, 0},
	{2, 6},
	{4, 6},
	{0, 6},
};

const int caracter_j[4][2] = {
	{0, 2},
	{2, 0},
	{4, 0},
	{4, 6},
};

const int caracter_k[6][2] = {
	{0, 0},
	{0, 6},
	{0, 3},
	{3, 6},
	{0, 3},
	{3, 0},
};

const int caracter_l[3][2] = {
	{4, 0},
	{0, 0},
	{0, 6},
};

const int caracter_m[5][2] = {
	{0, 0},
	{0, 6},
	{2, 4},
	{4, 6},
	{4, 0},
};

const int caracter_n[4][2] = {
	{0, 0},
	{0, 6},
	{4, 0},
	{4, 6},
};

const int caracter_o[5][2] = {
	{4, 0},
	{0, 0},
	{0, 6},
	{4, 6},
	{4, 0},
};

const int caracter_p[5][2] = {
	{0, 0},
	{0, 6},
	{4, 6},
	{4, 3},
	{0, 3},
};

const int caracter_q[9][2] = {
	{2, 2},
	{3, 1},
	{2, 0},
	{0, 0},
	{0, 6},
	{4, 6},
	{4, 2},
	{3, 1},
	{4, 0},
};

const int caracter_r[7][2] = {
	{0, 0},
	{0, 6},
	{4, 6},
	{4, 3},
	{0, 3},
	{1, 3},
	{4, 0},
};

const int caracter_s[6][2] = {
	{0, 0},
	{4, 0},
	{4, 3},
	{0, 3},
	{0, 6},
	{4, 6},
};

const int caracter_t[4][2] = {
	{2, 0},
	{2, 6},
	{4, 6},
	{0, 6},
};

const int caracter_u[4][2] = {
	{0, 6},
	{0, 0},
	{4, 0},
	{4, 6},
};

const int caracter_v[3][2] = {
	{0, 6},
	{2, 0},
	{4, 6},
};

const int caracter_w[5][2] = {
	{0, 6},
	{0, 0},
	{2, 2},
	{4, 0},
	{4, 6},
};

const int caracter_x[5][2] = {
	{0, 0},
	{4, 6},
	{2, 3},
	{0, 6},
	{4, 0},
};

const int caracter_y[5][2] = {
	{0, 6},
	{2, 4},
	{4, 6},
	{2, 4},
	{2, 0},
};

const int caracter_z[4][2] = {
	{0, 6},
	{4, 6},
	{0, 0},
	{4, 0},
};

const int caracter_0[5][2] = {
	{4, 0},
	{0, 0},
	{0, 6},
	{4, 6},
	{4, 0},
};

const int caracter_1[2][2] = {
	{2, 0},
	{2, 6},
};

const int caracter_2[6][2] = {
	{0, 6},
	{4, 6},
	{4, 3},
	{0, 3},
	{0, 0},
	{4, 0},
};

const int caracter_3[7][2] = {
	{0, 0},
	{4, 0},
	{4, 3},
	{0, 3},
	{4, 3},
	{4, 6},
	{0, 6},
};

const int caracter_4[5][2] = {
	{0, 6},
	{0, 3},
	{4, 3},
	{4, 6},
	{4, 0},
};

const int caracter_5[6][2] = {
	{0, 0},
	{4, 0},
	{4, 3},
	{0, 3},
	{0, 6},
	{4, 6},
};

const int caracter_6[5][2] = {
	{0, 6},
	{0, 0},
	{4, 0},
	{4, 3},
	{0, 3},
};

const int caracter_7[3][2] = {
	{0, 6},
	{4, 6},
	{4, 0},
};

const int caracter_8[7][2] = {
	{0, 3},
	{0, 6},
	{4, 6},
	{4, 0},
	{0, 0},
	{0, 3},
	{4, 3},
};

const int caracter_9[5][2] = {
	{4, 0},
	{4, 6},
	{0, 6},
	{0, 3},
	{4, 3},
};

const int caracter_derecha[5][2] = {
	{0, 3},
	{12, 3},
	{9, 5},
	{9, 1},
	{12, 3},
};

const int caracter_izquierda[5][2] = {
	{12, 3},
	{0, 3},
	{3, 5},
	{3, 1},
	{0, 3},
};

const int caracter_arriba[5][2] = {
	{5, -2},
	{5, 10},
	{3, 7},
	{7, 7},
	{5, 10},
};

const int caracter_abajo[5][2] = {
	{5, 10},
	{5, -2},
	{3, 1},
	{7, 1},
	{5, -2},
};

const int caracter_espacio[1][2] = {
	{0, 0},
};

/* const int caracter_nave[9][2] = {
	{0, 8},
	{-6, -1},
	{-4, -4},
	{-2, -4}, 
	{-0, -2},
	{2, -4},
	{4, -4},
	{6, -1},
	{0, 8},
}; */

const int caracter_nave[9][2] = {
	{0, -8}, 
	{6, 1}, 
	{4, 4}, 
	{2, 4}, 
	{-0, 2}, 
	{-2, 4}, 
	{-4, 4}, 
	{-6, 1}, 
	{0, -8}, 
};

typedef enum {
	CERO = 0,
	UNO = 1,
	DOS = 2,
	TRES = 3,
	CUATRO = 4,
	CINCO = 5,
	SEIS = 6,
	SIETE = 7,
	OCHO = 8,
	NUEVE = 9,
	ESPACIO = 10,
	ARRIBA = 11,
	ABAJO = 12, 
	IZQUIERDA = 13,
	DERECHA = 14,
	A = 15,
	B = 16,
	C = 17,
	D = 18,
	E = 19,
	F = 20,
	G = 21,
	H = 22,
	I = 23,
	J = 24,
	K = 25,
	L = 26,
	M = 27,
	N = 28,
	O = 29,
	P = 30,
	Q = 31,
	R = 32,
	S = 33,
	T = 34,
	U = 35,
	V = 36,
	W = 37,
	X = 38,
	Y = 39,
	Z = 40,
	NAVE = 41,

} caracteres_t;

const char tabla_caracteres[] = { 
	[CERO] = '0',
	[UNO] = '1',
	[DOS] = '2',
	[TRES] = '3',
	[CUATRO] = '4',
	[CINCO] = '5',
	[SEIS] = '6',
	[SIETE] = '7',
	[OCHO] = '8',
	[NUEVE] = '9',
	[ESPACIO] = ' ',
	[ARRIBA] = 'a',
	[ABAJO] = 'b', 
	[IZQUIERDA] = 'c',
	[DERECHA] = 'd',
	[A] = 'A',
	[B] = 'B',
	[C] = 'C',
	[D] = 'D',
	[E] = 'E',
	[F] = 'F',
	[G] = 'G',
	[H] = 'H',
	[I] = 'I',
	[J] = 'J',
	[K] = 'K',
	[L] = 'L',
	[M] = 'M',
	[N] = 'N',
	[O] = 'O',
	[P] = 'P',
	[Q] = 'Q',
	[R] = 'R',
	[S] = 'S',
	[T] = 'T',
	[U] = 'U',
	[V] = 'V',
	[W] = 'W',
	[X] = 'X',
	[Y] = 'Y',
	[Z] = 'Z',
	[NAVE] = 'n',
};

const void *tabla_polilineas_caracteres[] = {
	[CERO] = &caracter_0,
	[UNO] = &caracter_1,
	[DOS] = &caracter_2,
	[TRES] = &caracter_3,
	[CUATRO] = &caracter_4,
	[CINCO] = &caracter_5,
	[SEIS] = &caracter_6,
	[SIETE] = &caracter_7,
	[OCHO] = &caracter_8,
	[NUEVE] = &caracter_9,
	[ESPACIO] = &caracter_espacio,
	[ARRIBA] = &caracter_arriba,
	[ABAJO] = &caracter_abajo, 
	[IZQUIERDA] = &caracter_izquierda,
	[DERECHA] = &caracter_derecha,
	[A] = &caracter_a,
	[B] = &caracter_b,
	[C] = &caracter_c,
	[D] = &caracter_d,
	[E] = &caracter_e,
	[F] = &caracter_f,
	[G] = &caracter_g,
	[H] = &caracter_h,
	[I] = &caracter_i,
	[J] = &caracter_j,
	[K] = &caracter_k,
	[L] = &caracter_l,
	[M] = &caracter_m,
	[N] = &caracter_n,
	[O] = &caracter_o,
	[P] = &caracter_p,
	[Q] = &caracter_q,
	[R] = &caracter_r,
	[S] = &caracter_s,
	[T] = &caracter_t,
	[U] = &caracter_u,
	[V] = &caracter_v,
	[W] = &caracter_w,
	[X] = &caracter_x,
	[Y] = &caracter_y,
	[Z] = &caracter_z,
	[NAVE] = &caracter_nave,
};

const size_t cant_puntos_caracteres[] = {
	[CERO] = 5,
	[UNO] = 2,
	[DOS] = 6,
	[TRES] = 7,
	[CUATRO] = 5,
	[CINCO] = 6,
	[SEIS] = 5,
	[SIETE] = 3,
	[OCHO] = 7,
	[NUEVE] = 5,
	[ESPACIO] = 1,
	[ARRIBA] = 5,
	[ABAJO] = 5, 
	[IZQUIERDA] = 5,
	[DERECHA] = 5,
	[A] = 7,
	[B] = 12,
	[C] = 4,
	[D] = 7,
	[E] = 7,
	[F] = 6,
	[G] = 7,
	[H] = 6,
	[I] = 6,
	[J] = 4,
	[K] = 6,
	[L] = 3,
	[M] = 5,
	[N] = 4,
	[O] = 5,
	[P] = 5,
	[Q] = 9,
	[R] = 7,
	[S] = 6,
	[T] = 4,
	[U] = 4,
	[V] = 3,
	[W] = 5,
	[X] = 5,
	[Y] = 5,
	[Z] = 4,
	[NAVE] = 9,
};

void cadena_imprimir_centrado(SDL_Renderer *renderer, char *cadena, float pos_x, float pos_y, double escala, color_t color){
	size_t len = strlen(cadena);
	if(len == 0) return;
	uint8_t r;
	uint8_t g;
	uint8_t b;
	color_a_rgb(color, &r, &g, &b);

	for(size_t i = 0; i < len; i++){
		for(size_t j = 0; j < CANT_CARACTERES ; j++){
			if(cadena[i] == tabla_caracteres[j]){
				const int *poli = (const int (*))tabla_polilineas_caracteres[j];
				SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
				for(size_t k = 0; k < ((cant_puntos_caracteres[j] - 1) * 2); k+=2){
					SDL_RenderDrawLine(
					renderer,
					( (*(poli+k+EJE_X) + pos_x) * escala - pos_x*(escala-1) + SHIFT*escala*i) - SHIFT*escala*(0.5 + (float)len/2),
					(-(*(poli+k+EJE_Y) + pos_y) * escala + VENTANA_ALTO + pos_y*(escala-1)),
					( (*(poli+k+EJE_X+2) + pos_x) * escala - pos_x*(escala-1)  + SHIFT*escala*i) - SHIFT*escala*(0.5 + (float)len/2),
					(-(*(poli+k+EJE_Y+2) + pos_y) * escala + VENTANA_ALTO + pos_y*(escala-1))
					);
				}
			}
		}
	}
}

void cadena_imprimir(SDL_Renderer *renderer, char *cadena, float pos_x, float pos_y, double escala, color_t color){
	size_t len = strlen(cadena);
	if(len == 0) return;
	uint8_t r;
	uint8_t g;
	uint8_t b;
	color_a_rgb(color, &r, &g, &b);

	for(size_t i = 0; i < len; i++){
		for(size_t j = 0; j < CANT_CARACTERES ; j++){
			if(cadena[i] == tabla_caracteres[j]){
				const int *poli = (const int (*))tabla_polilineas_caracteres[j];
				SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
				for(size_t k = 0; k < ((cant_puntos_caracteres[j] - 1) * 2); k+=2){
					SDL_RenderDrawLine(
					renderer,
					( (*(poli+k+EJE_X) + pos_x) * escala - pos_x*(escala-1) + SHIFT*escala*i),
					(-(*(poli+k+EJE_Y) + pos_y) * escala + VENTANA_ALTO + pos_y*(escala-1)),
					( (*(poli+k+EJE_X+2) + pos_x) * escala - pos_x*(escala-1)  + SHIFT*escala*i),
					(-(*(poli+k+EJE_Y+2) + pos_y) * escala + VENTANA_ALTO + pos_y*(escala-1))
					);
				}
			}
		}
	}
}



