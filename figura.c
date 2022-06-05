#include "figura.h"


/* typedef enum{
    ICONO,
    NIVEL,
    SPRITE,
} figura_tipo_t; */

char *nombre_icono[] = {
    [ICONO] = "Icono",
    [NIVEL] = "Nivel",
    [SPRITE] = "Sprite",
};

const char* figura_tipo_a_cadena(figura_tipo_t figura){
    return nombre_icono[figura];
}