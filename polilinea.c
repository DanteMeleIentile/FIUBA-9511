#include "polilinea.h"
#include "color.h"
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define DIMENSION 2
#define X 0
#define Y 1

#include "polilinea.h"
#include "color.h"


/* Estructura de las polilineas */


polilinea_t *polilinea_crear_vacia(size_t n){
    polilinea_t *polilinea = malloc(sizeof(polilinea_t));

    if(polilinea == NULL){
        return NULL;
    }

    polilinea->puntos = malloc(sizeof(float) * DIMENSION * n);

    if(polilinea->puntos == NULL){
        free(polilinea);
        return NULL;
    }

    polilinea->n = n;

    return polilinea;
}


polilinea_t *polilinea_crear(const float puntos[][2], size_t n, color_t c){

    polilinea_t *polilinea = polilinea_crear_vacia(n);

    if(polilinea == NULL){
        return NULL;
    }

    polilinea_setear_color(polilinea, c);

    memcpy(polilinea->puntos, puntos, (polilinea->n)*sizeof(float)*DIMENSION);

    return polilinea;
}

double polilinea_get_extremo_x(polilinea_t *polilinea, bool mayor){
    double aux = 0; 
    for(size_t i = 0; i < polilinea->n; i++){
        if(i == 0){
            aux = polilinea->puntos[i][X];
        }
        if((aux < polilinea->puntos[i][X]) && mayor){
            aux = polilinea->puntos[i][X];
        }
        if((aux > polilinea->puntos[i][X]) && !mayor){
            aux = polilinea->puntos[i][X];
        }
    }
    return aux;
}

double polilinea_get_extremo_y(polilinea_t *polilinea, bool mayor){
    double aux = 0; 
    for(size_t i = 0; i < polilinea->n; i++){
        if(i == 0){
            aux = polilinea->puntos[i][Y];
        }
        if((aux < polilinea->puntos[i][Y]) && mayor){
            aux = polilinea->puntos[i][Y];
        }
        if((aux > polilinea->puntos[i][Y]) && !mayor){
            aux = polilinea->puntos[i][Y];
        }
        
    }
    return aux;
}


void polilinea_destruir(polilinea_t *polilinea){
    free(polilinea->puntos);
    free(polilinea);
}


bool polilinea_setear_punto(polilinea_t *polilinea, size_t pos, float x, float y){
    if (polilinea->n <= pos){  //Confío que la persona que utiliza la función garantiza 'polilinea->puntos != NULL'
        return false;
    }
    polilinea->puntos[pos][X] = x;
    polilinea->puntos[pos][Y] = y;
    return true;
}

bool polilinea_setear_color(polilinea_t *polilinea, color_t color) {
    uint8_t r, g, b;
    color_a_rgb(color, &r, &g, &b);
        polilinea->r = r;
        polilinea->g = g;
        polilinea->b = b;
    return true;
}


polilinea_t *polilinea_clonar(const polilinea_t *polilinea){
    color_t c = color_crear_valor(polilinea->r, polilinea->g, polilinea->b);
    return polilinea_crear((const float(*)[DIMENSION])(polilinea->puntos), polilinea->n, c);
}

void trasladar(float polilinea[][2], size_t n, float dx, float dy) {
    for(int i = 0; i < n; i+=1){
        polilinea[i][X] += dx;
        polilinea[i][Y] += dy;
    }
}

void rotar(float polilinea[][2], size_t n, double rad) {
    double accx;
    double accy;

    for(int i = 0; i < n; i++){
        accx = polilinea[i][X];
        accy = polilinea[i][Y];
        polilinea[i][X] = accx * cos(rad) - accy * sin(rad);
        polilinea[i][Y] = accx * sin(rad) + accy * cos(rad);
    }
}

void escalar(float polilinea[][2], size_t n, float escala){
    for(int i = 0; i < n; i+=1){
        polilinea[i][X] *= escala;
        polilinea[i][Y] *= escala;
    }
}

double calcular_distancia(float px, float py, float qx, float qy){
    return sqrt(pow(px-qx,2) + pow(py-qy,2));
}

double calcular_parametro(float ax, float ay, float bx, float by, float px, float py) {

    double k = ((px - ax) * (bx - ax) + (py - ay) * (by - ay))/ pow(calcular_distancia(bx, by, ax, ay),2); 

    return k;
}

double distancia_punto_a_polilinea(float polilinea[][2], size_t n, float px, float py) {

    double punto_cercano_x;
    double punto_cercano_y;
    double ax;
    double ay;
    double bx;
    double by;
    double k;
    double acc_d;
    double distancia;

    for(int i = 0; i < n - 1; i++) {
        ax = polilinea[i][0];
        ay = polilinea[i][1];
        
        bx = polilinea[i+1][0];
        by = polilinea[i+1][1]; 

        k = calcular_parametro(ax, ay, bx, by, px, py);
        
        if(k <= 0) {
            punto_cercano_x = ax;
            punto_cercano_y = ay;
        } 
        else{
        if(k >= 1) {
            punto_cercano_x = bx;
            punto_cercano_y = by;
        }
        else{
            punto_cercano_x = ax + k * (bx - ax);
            punto_cercano_y = ay + k * (by - ay);
        }
        }
        distancia = calcular_distancia(px , py , punto_cercano_x, punto_cercano_y);

        if(!i)
            acc_d = distancia;

        if(distancia < acc_d) 
            acc_d = distancia;
    }
    return acc_d;
}

void polilinea_printf(polilinea_t *polilinea){
    printf("EL COLOR ES %d  %d  %d\n", polilinea->r, polilinea->g, polilinea->b);
    printf("CANT PUNTOS %zd\n", polilinea->n);
    for(size_t i = 0; i < polilinea->n; i++){
        printf("POLILINEA %zd ( %.7f , %.7f )\n", polilinea->n, polilinea->puntos[i][X], polilinea->puntos[i][Y]);
    }
}
