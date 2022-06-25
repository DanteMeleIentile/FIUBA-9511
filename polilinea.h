#ifndef POLILINEA_H
#define POLILINEA_H

#include <stdio.h>

#include "figura.h"
#include "color.h"

typedef struct{
    float (*puntos)[2];
    size_t n;
    color_t c;
} polilinea_t;

typedef float punto[2]; 

//Creacion y destruccion:

polilinea_t *polilinea_crear_vacia(size_t n);

polilinea_t *polilinea_crear(const float puntos[][2], size_t n);

polilinea_t *polilinea_clonar(const polilinea_t *polilinea);

void polilinea_destruir(polilinea_t *polilinea);

//Setters:

bool polilinea_setear_punto(polilinea_t *polilinea, size_t pos, float x, float y);

bool polilinea_setear_color(polilinea_t *polilinea, color_t color);

//Modificadores:

void polilinea_trasladar(polilinea_t *polilinea, float dx, float dy);

void polilinea_rotar(polilinea_t *polilinea, double rad);

//Distancia:

double calcular_distancia(const punto p, const punto q);

double calcular_parametro(const punto a, const punto b, const punto p);

double polilinea_distancia_punto_a_polilinea(polilinea_t polilinea, const punto p);

//otra funcion que calcule distancia entre polilineas:

double polilinea_distancia_a_polilinea(polilinea_t polilinea1, polilinea_t polilinea2);

#endif