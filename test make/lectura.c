#include <stdbool.h> 
#include <stdint.h> 
#include <stdio.h> 

#include "polilineas.h"
#include "figura.h"


#define MASK_TIPO 0x07  // 0000 0111

bool leer_encabezado_figura(FILE *f, char nombre[], figura_tipo_t *tipo, bool *infinito, size_t *cantidad_polilineas){
    if (fread(nombre, 1, 20, f) != 20){
        return false;
    } 

    uint8_t aux;
    if (fread(&aux, 1, 1, f) != 1){
        return false;
    }

    *tipo = ((aux >> 1) & MASK_TIPO);
    
    *infinito = aux >> 6;
    

    if (fread(cantidad_polilineas, sizeof(uint16_t), 1, f) != 1){
        return false;
    }

    return true;
}


#define MASK_CANT_PUNTOS_POLI 0x03ff // 0000 0011 1111 1111
#define MASK_COLOR_POLI 0xe000 // 1110 0000 0000 0000



polilinea_t *leer_polilinea(FILE *f){
    polilinea_t *p;
    
    size_t a; 
    size_t n; // Corresponde a cantidad de puntos de la poli

    color_t c; // Correponde a los 3 bits del color de la poli


//    fread(&a, sizeof(uint16_t), 1, f);
    fread(&a, 2, 1, f);

    //agarro n del archivo para crear la poli de n puntos

    
    c = (a & MASK_COLOR_POLI) >> 13; // obtengo valores de color de encabezado
    //printf("\nEL COLOR ES %d\n", c);
    

    n = (a & MASK_CANT_PUNTOS_POLI);// obtengo valores de cantidad de puntos de encabezado
    if ((p = polilinea_crear_vacia(n)) == NULL){ // Creo la polilinea según cantidad de puntos obtendido. OPCIONAL: + 2 bytes (16 bits) que corresponden al encabezado
        return NULL;
    }


    //agarro color del archivo para settear color 
    if (polilinea_setear_color (p, c) == false){
        return NULL;
    }


    //agarro un punto, lea cada mitad y la meto en x e y de la funcion poli settear punto. Además la posición va a ser la variable a iterar


    float x; // Corresponde a la coordenada x de cada punto de la poli
    float y; // Corresponde a la coordenada y de cada punto de la poli

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