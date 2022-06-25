#include "lectura.h"
#include "polilinea.h"
#include "figura.h"
#include "color.h"

#include <stdbool.h> 
#include <stdint.h> 
#include <stdio.h> 

#define IN 0x40 //0100 0000
#define TYPE 0x0E //0000 1110

#define CANT 0xFC00 //1111 1100

bool leer_encabezado_figura(FILE *f, char nombre[], figura_tipo_t *tipo, bool *infinito, size_t *cantidad_polilineas){
    uint8_t caracteristica;
    uint16_t cant;

    if(fread(nombre, 20, 1, f) < 1) return false;

    if(fread(&caracteristica, 1, 1, f) < 1) return false;

    if(fread(&cant, 2, 1, f) < 1) return false;

    *cantidad_polilineas = cant;

    *tipo = ((caracteristica & TYPE))>>1;

    *infinito = ((caracteristica & IN))>>6;
    
    return true;
}

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