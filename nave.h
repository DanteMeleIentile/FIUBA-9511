#ifndef NAVE_H
#define NAVE_H

#include "figura.h"

typedef struct{
    figura_t *figura;
    double angulo_actual;
    //int cant_combustible;
    //double angulo_velocidad;
    //double posición;
} nave_t;

/*  
** Crea una nave con sus parámetros en 0 en memoria nueva. Si falla, devuelve null
*/
nave_t *nave_crear(void);

/*  
** Iniciliza las parametros de la nave según la "nave" recibida.
** PRE: La nave fue creada.
** POST: La figura de la nave es igual a "figura" 
*/ 
void nave_inicializar(nave_t *nave, figura_t *figura_nave);

/*  
** Rota la nave un angulo "angulo" y actualiza el valor de "angulo_actual". "Angulo actual" siempre se encontrará entre [0 y 2PI]
*/
void nave_rotar(nave_t *nave, double angulo);


//nave_trasladar(dx, dy);

//nave_clonar(dx, dy);

//nave_status(dx, dy);

//nave_status(dx, dy2);


#endif