#ifndef FIGURA_H
#define FIGURA_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>

#include "polilinea.h"
#include "lista.h"

/* 
** Etiquetas para cada tipo de figura
*/

typedef enum {
    ICONO = 0,
    NIVEL = 1,
    SPRITE = 2,
    PLANETA = 3,
    BASE = 4,
    COMBUSTIBLE = 5,
    TORRETA = 6,
    REACTOR = 7,
} figura_tipo_t;

struct figura;

typedef struct figura figura_t;

/* 
** Devuelve el nombre de la figura
*/
const char* figura_tipo_a_cadena(figura_tipo_t figura);

/*  
** Crea una figura con nombre = nombre, con tipo = tipo, si es infinita o no y con "cant_polilineas" polilineas. El puntero polilineas apunta a null. Si falla, devuelve null
*/
figura_t *figura_crear(const char nombre[], figura_tipo_t tipo, bool infinito, size_t cant_polilineas);

/*  
** Devuelve una copia de figura en memoria nueva
*/
figura_t *figura_clonar(const figura_t *figura);

/*  
** Devuelve "true" si el nivel es infinito y "false" si no lo es
*/
bool figura_get_infinito(const figura_t *figura);

/*
** Apunta el puntero "polilineas" de la "figura" a un arreglo de cant_polilineas "polilineas". Si no puede retorna false
** PRE: figura_t->cant_polilineas debe ser igual a la longitud de polilineas;
** POST: El puntero "polilineas" de la figura apunta al vector "polilineas" 
*/
bool figura_setear_polilinea(figura_t *figura, polilinea_t **polilineas);

/*
** Devuelve el extremo en "x" de la figura
** Si "mayor" es true, devuelve el extremo mayor, sino el menor
*/
float figura_get_extremo_x(const figura_t *figura, bool mayor);

/*
** Devuelve el extremo en "y" de la figura
** Si "mayor" es true, devuelve el extremo mayor, sino el menor
*/
float figura_get_extremo_y(const figura_t *figura, bool mayor);

/*
** Devuelve el nombre de la figura dada.
*/
char *figura_get_nombre(figura_t *figura);

/*
** Dada una figura, la rota un angulo "rad".
*/
void figura_rotar(figura_t *figura, double rad);

/*
** Dada una figura, le suma las coordenadas "x" e "y".
*/
void figura_trasladar(figura_t *figura, float dx, float dy);

//Da la distancia más cercana entre el punto y la figura
float distancia_punto_a_figura(const figura_t *figura, float x, float y);

/*
** Libera la memoria de la figura dada. Es importante destacar que también eli
*/
void figura_destruir(figura_t *figura);

/*
**Imprime una "figura" con una "escala" determinada. El centro desde el cual se escalará esta determinado por las coordenadas "escala_x; escala_y". La traslación dada a la hora de dibujar estará determinada por "tras_x; tras_y".
*/
void figura_imprimir(SDL_Renderer *renderer, const figura_t *figura, float escala, float escala_x, float escala_y, float tras_x, float tras_y);


#endif