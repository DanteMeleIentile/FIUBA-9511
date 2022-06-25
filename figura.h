#ifndef FIGURA_H
#define FIGURA_H


/* 
** Etiquetas para cada tipo de figura
*/
typedef enum{
    ICONO,
    NIVEL,
    SPRITE,
} figura_tipo_t;

/* 
** Devuelve el nombre de la figura
*/
const char* figura_tipo_a_cadena(figura_tipo_t figura);

#endif