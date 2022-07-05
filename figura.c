#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#include "polilinea.h"
#include "polilinea.h"
#include "figura.h"
#include "lista.h"



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

bool figura_setear_polilinea(figura_t *figura, polilinea_t **polilineas){
    if((figura->polilineas = polilineas) == NULL)
        return false;
    
    return true;
}

void figura_destruir(figura_t *figura){
    for(size_t i = 0; (i < figura->cant_polilineas); i++){
        polilinea_destruir(figura->polilineas[i]);
    }

    free(figura->polilineas);

    free(figura);
}



void figura_agregar_en_lista(char *nombre, lista_t *lista){
    lista_insertar_ultimo(lista, nombre);
}

void figura_eliminar_en_lista(char *nombre, lista_t *lista){
    lista_iter_t *iter = lista_iter_crear(lista);
    for(size_t i = 0; i < lista_largo(lista); i++){
        if(strcmp(lista_iter_ver_actual(iter), nombre) == 0){
            lista_iter_borrar(iter);
            break;
            //continue;
        }
        lista_iter_avanzar(iter);
    }
    
    lista_iter_destruir(iter);
}

void figura_eliminar_todos_nombre(char *nombre, lista_t *lista){
    lista_iter_t *iter = lista_iter_crear(lista);
    for(size_t i = 0; i < lista_largo(lista); i++){
        if(strcmp(lista_iter_ver_actual(iter), nombre) == 0){
            lista_iter_borrar(iter);
            //break;
            //continue;
        }
        lista_iter_avanzar(iter);
    }
    
    lista_iter_destruir(iter);
}