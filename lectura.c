#include "lectura.h"
#include "polilinea.h"
#include "figura.h"
#include "color.h"

#include <stdbool.h> 
#include <stdint.h> 
#include <stdio.h> 


#define MASK_TIPO 0x07  // 0000 0111

#define MASK_CANT_PUNTOS_POLI 0x03ff // 0000 0011 1111 1111

bool leer_encabezado_figura(FILE *f, char nombre[], figura_tipo_t *tipo, bool *infinito, size_t *cantidad_polilineas){
    if (fread(nombre, sizeof(char), 20, f) != 20){
        return false;
    } 

    static uint8_t aux;
    if (fread(&aux, sizeof(uint8_t), 1, f) != 1){
        return false;
    }

    *tipo = ((aux >> 1) & MASK_TIPO);
    
    *infinito = aux >> 6;

    static uint16_t aux_cant_poli; // Variable de 1 Byte para obtener la cantidad de polilineas

    if (fread(&aux_cant_poli, sizeof(uint8_t), 2, f) != 2){ // Garantizo que el parámetro de "size" del fread sea de 1 byte. Ver "man 3 fread"
        return false;
    }

    *cantidad_polilineas = (size_t)aux_cant_poli; 

    return true;
}

polilinea_t *leer_polilinea(FILE *f){
    polilinea_t *p;
    
    size_t aux; 

    size_t n; // Cant. puntos polilinea
    color_t c; // 3 bits del color de la polilinea

    fread(&aux, sizeof(uint16_t), 1, f);
    
    c = (aux >> 13);

    n = (aux & MASK_CANT_PUNTOS_POLI);
    
    if ((p = polilinea_crear_vacia(n)) == NULL){
        return NULL;
    }

    if (polilinea_setear_color (p, c) == false){
        return NULL;
    }

    float x; // Corresponde a la coordenada x de cada punto
    float y; // Corresponde a la coordenada y de cada punto

    for (size_t i = 0; i < n; i++){
        fread(&x, sizeof(float), 1, f);
        fread(&y, sizeof(float), 1, f);

        if (polilinea_setear_punto(p, i, x, y) == false){
            polilinea_destruir(p);
            return NULL;
        }
    }

    return p;
}