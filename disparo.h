#ifndef DISPARO_H
#define DISPARO_H

typedef struct{
    figura_t *fig;
    double angulo;
    double vel[2];
    double pos[2];
} disparo_t;

/*
** Crea un disparo inicializando sus parámetros en 
*/
disparo_t disparo_crear(figura_t *figura, double pos[2], double vel[2], double angulo);




#endif