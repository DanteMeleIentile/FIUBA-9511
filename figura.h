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


typedef struct{
    char nombre[20];
    figura_tipo_t tipo;
    bool infinito;
    size_t cant_polilineas;
    polilinea_t **polilineas;
} figura_t;



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
** Apunta el puntero "polilineas" de la "figura" a un arreglo de cant_polilineas "polilineas". Si no puede retorna false
** PRE: figura_t->cant_polilineas debe ser igual a la longitud de polilineas;
** POST: El puntero "polilineas" de la figura apunta al vector "polilineas" 
*/
bool figura_setear_polilinea(figura_t *figura, polilinea_t **polilineas);

/*
** Devuelve el extremo en "x" de la figura
** Si "mayor" es true, devuelve el extremo mayor, sino el menor
*/
double figura_get_extremo_x(figura_t *figura, bool mayor);

/*
** Devuelve el extremo en "y" de la figura
** Si "mayor" es true, devuelve el extremo mayor, sino el menor
*/
double figura_get_extremo_y(figura_t *figura, bool mayor);

char *figura_get_nombre(figura_t *figura);

/*
** Destruye figuras
*/
void figura_destruir(figura_t *figura);

/*
** Dada una figura de nombre "nombre" y una lista_t "lista", agrega a "lista" un nodo con dato = "nombre".
** PRE: Lista creada utilizando funciones del TDA lista.
** POST: El último elemento de la lista apunta a NULL 
*/
void figura_agregar_en_lista(char *nombre, lista_t *lista);

/*
** Dada una figura de nombre "nombre" y una lista_t "lista", ELIMINA de "lista" EL PRIMER nodo con dato = "nombre".
** PRE: Lista creada utilizando funciones del TDA lista.
** POST: El último elemento de la lista apunta a NULL 
*/
//EVALIUAR FUNCION PARA ELIMINAR TODAS LAS ENTIDADES CON "NOMBRE"
void figura_eliminar_en_lista(char *nombre, lista_t *lista);


void figura_eliminar_en_lista_nombre(char *nombre, lista_t *lista);


//Dado un vector de polilineas de longitud cant_polilineas, una escala y un renderer, imprime por pantalla todas las polilineas del vector dado.
void figura_imprimir(SDL_Renderer *renderer, const figura_t *figura, float escala, double x, double y);


//Rota la figura dada un angulo "rad"
void figura_rotar(figura_t *figura, double rad);


//Traslada la figura dada una distancia "dx" en coordenada "x" y una distancia "dy" en coordenada "y"
void figura_trasladar(figura_t *figura, double dx, double dy);

//Traslada y rota la figura con los mismos parametros que las anteriores 2 funciones
void figura_rototrasladar(figura_t *figura, double dx, double dy, double angulo);

//Da la distancia más cercana entre el punto y la figura
double distancia_punto_a_figura(figura_t *figura, double x, double y);

/*
** Dada una figura, la setea en unas coordenadas "x" e "y" rotada un angulo "rad" y escalada por "escala".
** PRE: Lista creada utilizando funciones del TDA lista.
** POST: El último elemento de la lista apunta a NULL 
*/
//figura_t *rototrasladar_figura(figura_t *figura, float dx, float dy, float rad, float escala, float posicion_x, float posicion_y);

#endif