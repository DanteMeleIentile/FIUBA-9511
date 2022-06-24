#include "polilinea.h"
#include "color.h"
#include <stdlib.h>


#define DIM 2

#define CANT 0xFC00 //1111 1100

//Creacion y destruccion:

polilinea_t *polilinea_crear_vacia(size_t n){
    polilinea_t *polilinea = malloc(sizeof(polilinea_t));

    if(polilinea == NULL){
        return NULL;
    }

    polilinea->puntos = malloc(sizeof(float) * DIM * n);

    if(polilinea->puntos == NULL){
        free(polilinea);
        return NULL;
    }

    polilinea->n = n;

    return polilinea;
}

polilinea_t *polilinea_crear(const float puntos[][2], size_t n){

    polilinea_t *polilinea = polilinea_crear_vacia(n);

    if(polilinea == NULL){
        return NULL;
    }

    memcpy(polilinea->puntos, puntos, (polilinea->n)*sizeof(float)*DIM);

    return polilinea;
}

polilinea_t *polilinea_clonar(const polilinea_t *polilinea){
    
    if(polilinea == NULL){
        return NULL;
    }

    return polilinea_crear((const float(*)[2]) polilinea->puntos, polilinea->n);
}

void polilinea_destruir(polilinea_t *polilinea){
    free(polilinea->puntos);
    free(polilinea);
}

//Setters:

bool polilinea_setear_punto(polilinea_t *polilinea, size_t pos, float x, float y){
    if(polilinea != NULL && pos < polilinea->n){
        polilinea->puntos[pos][0] = p[0];
        polilinea->puntos[pos][1] = p[1];
        return true;
    }
    return false;
}

bool polilinea_setear_color(polilinea_t *polilinea, color_t color) {
    uint8_t r, g, b;
    color_a_rgb(color, &r, &g, &b);
    printf("POLILINEA COLOR: (%d, %d, %d)\n", r, g, b);
    return true;
}

//Modificadores:

void polilinea_trasladar(polilinea_t *polilinea, float dx, float dy) {
    for(int i = 0; i < polilinea->n; i+=1){
        polilinea->puntos[i][0] += dx;
        polilinea->puntos[i][1] += dy;
    }
}

void polilinea_rotar(polilinea_t *polilinea,  double rad) {
    double accx;
    double accy;

    for(int i = 0; i < polilinea->n; i++){
        accx = polilinea->puntos[i][0];
        accy = polilinea->puntos[i][1];
        polilinea->puntos[i][0] = accx * cos(rad) - accy * sin(rad);
        polilinea->puntos[i][1] = accx * sin(rad) + accy * cos(rad);
    }
}

//Distancia:

double calcular_distancia(const punto p, const punto q){
    return sqrt(pow(p[0]-q[0],2) + pow(p[1]-q[1],2));
}

double calcular_parametro(const punto a, const punto b, const punto p){
    double k = ((p[0] - a[0]) * (b[0] - a[0]) + (p[1] - a[1]) * (b[1] - a[1]))/ pow(calcular_distancia(b, a),2); 
    return k;
}

double polilinea_distancia_punto_a_polilinea(polilinea_t polilinea, const punto p){}

//FILE:

polilinea_t *leer_polilinea(FILE *f){

    uint16_t encabezado;
    if(fread(&encabezado, sizeof(uint16_t), 1, f) != 1){
        return NULL;
    } 

    color_t color = encabezado >> 13;
    uint16_t cant = encabezado & (~CANT);

    polilinea_t *p = polilinea_crear_vacia(cant);

    p->c = color;

    if(!polilinea_setear_color(p, color)){
        polilinea_destruir(p);
        return NULL;
    }

    float pol[cant][2];

    if(fread(pol, sizeof(float) * cant * 2, 1, f) != 1){
        polilinea_destruir(p);
        return NULL;
    }

    for(size_t i = 0; i < cant; i++){
        polilinea_setear_punto(p, i, pol[i][0], pol[i][1]);
    }

    return p;
}