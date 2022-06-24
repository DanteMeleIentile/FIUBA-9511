#include "figura.h"

#include <stdint.h>

#define IN 0x40 //0100 0000s
#define TYPE 0x0E //0000 1110

const char figura_tipo_s[8][7] = {
    [ICONO] = "Icono", 
    [NIVEL] = "Nivel", 
    [SPRITE] = "Sprite",
    [PLANETA] = "Planeta",
    [BASE] = "Base",
    [COMBUSTIBLE] = "Combustible",
    [TORRETA] = "Torreta",
    [REACTOR] = "Reactor",
};

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

const char* figura_tipo_a_cadena(figura_tipo_t figura){
    return figura_tipo_s[figura];
}