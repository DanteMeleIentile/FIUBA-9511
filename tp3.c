#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>


#define DIMENSION 2
#define X 0
#define Y 1


/*
Para ver salida Vangrid:
- compilar con -g
- valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./tp3
*/


/* Estructura de las polilineas */
typedef struct {
    float (*puntos)[2];
    size_t n;
} polilinea_t;


polilinea_t *polilinea_crear_vacia(size_t n){
    polilinea_t *p = malloc(sizeof(polilinea_t)); 
    if (p == NULL){
        return NULL;
    }

    p->n = n;
    p->puntos = malloc(n * sizeof(float) * DIMENSION);
    if (p->puntos == NULL){
        free(p);
        return NULL;
    }

    return p;
}


polilinea_t *polilinea_crear(const float puntos[][2], size_t n){
    polilinea_t *p = polilinea_crear_vacia(n);
    if (p == NULL){
        return NULL;
    }
    
    memcpy (*p->puntos, puntos, (n * sizeof(float) * DIMENSION));
    
    /* for (size_t i = 0; i < n; i++){
        p->puntos[i][X] = puntos [i][X];
        p->puntos[i][Y] = puntos [i][Y];
    } */

    return p;
}


void polilinea_destruir(polilinea_t *polilinea){
    free(polilinea->puntos);
    free(polilinea);
}


size_t polilinea_cantidad_puntos(const polilinea_t *polilinea){
    return polilinea->n;
}


bool polilinea_obtener_punto(const polilinea_t *polilinea, size_t pos, float *x, float *y){
    if (polilinea->n <= pos){ //Confío que la persona que utiliza la función garantiza 'polilinea->puntos != NULL' 
        return false;
    }

    *x = polilinea->puntos[pos][X];
    *y = polilinea->puntos[pos][Y];
    return true;
}


bool polilinea_setear_punto(polilinea_t *polilinea, size_t pos, float x, float y){
    if (polilinea->n <= pos){  //Confío que la persona que utiliza la función garantiza 'polilinea->puntos != NULL'
        return false;
    }

    polilinea->puntos[pos][X] = x;
    polilinea->puntos[pos][Y] = y;
    return true;
}


polilinea_t *polilinea_clonar(const polilinea_t *polilinea){
    return polilinea_crear((const float(*)[DIMENSION])(polilinea->puntos), polilinea->n);
}



int main(void) {
    const float puntos[3][2] = {{0, 0}, {1, 0}, {0, 1}};

    polilinea_t *p1 = polilinea_crear(puntos, 3);
    if(p1 == NULL) {
        fprintf(stderr, "Error en creacion de polilinea\n");
        return 1;
    }

    float x, y;

    assert(polilinea_cantidad_puntos(p1) == 3);
    assert(! polilinea_obtener_punto(p1, 3, &x, &y));
    assert(polilinea_obtener_punto(p1, 1, &x, &y));
    assert(x == 1 && y == 0);

    polilinea_t *p2 = polilinea_crear_vacia(2);
    if(p2 == NULL) {
        fprintf(stderr, "Error en creacion de polilinea\n");
        return 1;
    }

    assert(polilinea_cantidad_puntos(p2) == 2);
    assert(! polilinea_setear_punto(p2, 2, 0, 0));
    assert(polilinea_setear_punto(p2, 1, 3, 1));
    assert(polilinea_obtener_punto(p2, 1, &x, &y));
    assert(x == 3 && y == 1);

    polilinea_destruir(p2);

    p2 = polilinea_clonar(p1);
    polilinea_destruir(p1);
    if(p2 == NULL) {
        fprintf(stderr, "Error en creacion de polilinea\n");
        return 1;
    }
    
    assert(polilinea_cantidad_puntos(p2) == 3);
    assert(polilinea_obtener_punto(p2, 2, &x, &y));
    assert(x == 0 && y == 1);

    polilinea_destruir(p2);

    assert(polilinea_crear(puntos, 1UL << 50) == NULL);

    return 0;
}