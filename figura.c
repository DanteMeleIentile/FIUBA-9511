#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>


#include "polilinea.h"
#include "polilinea.h"
#include "figura.h"
#include "lista.h"

#define DIMENSION 2
#define X 0
#define Y 1

char *nombre_icono[] = {
    [ICONO] = "Icono", 
    [NIVEL] = "Nivel", 
    [SPRITE] = "Sprite",
    [PLANETA] = "Planeta",
    [BASE] = "Base",
    [COMBUSTIBLE] = "Combustible",
    [TORRETA] = "Torreta",
    [REACTOR] = "Reactor",
};

struct figura{
    char nombre[20];
    figura_tipo_t tipo;
    bool infinito;
    size_t cant_polilineas;
    polilinea_t **polilineas;
};

const char* figura_tipo_a_cadena(figura_tipo_t figura){
    return nombre_icono[figura];
}

figura_t *figura_crear(const char nombre[], figura_tipo_t tipo, bool infinito, size_t cant_polilineas){
    figura_t *fig = malloc(sizeof(figura_t));
    if(fig == NULL) return NULL;

    strcpy(fig->nombre, nombre);

    fig->tipo = tipo;

    fig->infinito = infinito;

    fig->cant_polilineas = cant_polilineas;

    fig->polilineas = NULL;
    
    return fig;
}

figura_t *figura_clonar(const figura_t *figura){
    figura_t *fig = figura_crear(figura->nombre, figura->tipo, figura->infinito, figura->cant_polilineas);
    if(fig == NULL){
        return NULL;
    }

    polilinea_t **vector_polilineas = malloc(sizeof(polilinea_t*) * figura->cant_polilineas);

    if(vector_polilineas == NULL){
        figura_destruir(fig);
        return NULL;
    }

    for(size_t j = 0; j < fig->cant_polilineas; j++){
        vector_polilineas[j] = polilinea_clonar(figura->polilineas[j]); //Iguala cada componente de las polilineas de cada figura leida del archivo

        if(vector_polilineas[j] == NULL){
            if(j >= 1){
                for(size_t l = 0; l < j; l++){
                    polilinea_destruir(vector_polilineas[l]);
                }
            }
            free(vector_polilineas);
            figura_destruir(fig);
            return NULL;
        }
    }
    
    figura_setear_polilinea(fig, vector_polilineas);
    return fig;
}

bool figura_get_infinito(const figura_t *figura){
    return figura->infinito;
}

bool figura_setear_polilinea(figura_t *figura, polilinea_t **polilineas){
    if((figura->polilineas = polilineas) == NULL)
        return false;
    return true;
}

float figura_get_extremo_x(const figura_t *figura, bool mayor){
    float aux = 0;
    for(size_t i = 0; i < figura->cant_polilineas; i++){
        if(i == 0){
            aux = polilinea_get_extremo_x(figura->polilineas[i], mayor);
        }
        if(aux < polilinea_get_extremo_x(figura->polilineas[i], mayor) && mayor){
            aux = polilinea_get_extremo_x(figura->polilineas[i], mayor);
        }

        if(aux > polilinea_get_extremo_x(figura->polilineas[i], mayor) && !mayor){
            aux = polilinea_get_extremo_x(figura->polilineas[i], mayor);
        }
    }
    return aux;
}

float figura_get_extremo_y(const figura_t *figura, bool mayor){
    float aux = 0;
    for(size_t i = 0; i < figura->cant_polilineas; i++){
        if(i == 0){
            aux = polilinea_get_extremo_y(figura->polilineas[i], mayor);
        }
        if((aux < polilinea_get_extremo_y(figura->polilineas[i], mayor)) && mayor){
            aux = polilinea_get_extremo_y(figura->polilineas[i], mayor);
        }

        if((aux > polilinea_get_extremo_y(figura->polilineas[i], mayor)) && !mayor){
            aux = polilinea_get_extremo_y(figura->polilineas[i], mayor);
        }
    }
    return aux;
}

char *figura_get_nombre(figura_t *figura){
    return figura->nombre;
}

void figura_destruir(figura_t *figura){
    if(figura == NULL) return;
    for(size_t i = 0; (i < figura->cant_polilineas); i++){
        polilinea_destruir(figura->polilineas[i]);
    }
    free(figura->polilineas);
    free(figura);
}

void figura_rotar(figura_t *figura, double rad){
    for(size_t i = 0; i < figura->cant_polilineas; i++){
        polilinea_rotar(figura->polilineas[i], rad);
    }
}

void figura_trasladar(figura_t *figura, float dx, float dy){
    for(size_t i = 0; i < figura->cant_polilineas; i++){
        polilinea_trasladar(figura->polilineas[i], dx, dy);
    }
}

float distancia_punto_a_figura(const figura_t *figura, float x, float y){
    float distancia;
    float distancia_actual;
    distancia = distancia_punto_a_polilinea(figura->polilineas[0], x, y);
    distancia_actual = distancia;
    
    for(size_t i = 1; i < figura->cant_polilineas; i++){
        distancia = distancia_punto_a_polilinea(figura->polilineas[i], x, y);
        if(distancia < distancia_actual) distancia_actual = distancia;
    }
    return distancia_actual;
}

void figura_imprimir(SDL_Renderer *renderer, const figura_t *figura, float escala, float escala_x, float escala_y, float tras_x, float tras_y){
    for(size_t k = 0; k < figura->cant_polilineas; k++){
        polilinea_imprimir(renderer, figura->polilineas[k], escala, escala_x, escala_y, tras_x, tras_y);
    }
}

