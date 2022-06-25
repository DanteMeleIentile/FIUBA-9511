#ifndef FIGURA_H
#define FIGURA_H

#include "polilinea.h"

#include <stdbool.h>
#include <stdlib.h>

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
** Apunta el puntero "polilineas" de la "figura" a un arreglo de "cant_polilineas" polilineas. Si no puede retorna false
*/
bool figura_settear_polilinea(figura_t *figura, polilinea_t **polilineas);

/*
** Destruye figuras
*/
void figura_destruir(figura_t *figura);

#endif