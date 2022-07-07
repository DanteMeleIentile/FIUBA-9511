#include <stdlib.h>

#include "nave.h"
#include "figura.h"
#include "config.h"

nave_t *nave_crear(void){
    //Evaluar necesidad de memoría dinámica
    nave_t *nave = malloc(sizeof(nave_t));
    if(nave == NULL) return NULL;

    nave->angulo_actual = 0;

    return nave;
}

void nave_rotar(nave_t *nave, double angulo){
    figura_rotar(nave->figura, angulo);
    nave->angulo_actual += angulo;

    while(nave->angulo_actual > 2 * PI)
        nave->angulo_actual = nave->angulo_actual - (2 * PI);

    while(nave->angulo_actual < 0)
        nave->angulo_actual = nave->angulo_actual + (2 * PI);
}

/*  FUNCION INTERNA
** Setear las figuras de la nave según "figura_nave".
** PRE: La nave fue creada. 
*/
static void nave_setear_figura(nave_t *nave, figura_t *fig_nave){
    nave->figura = figura_clonar(fig_nave);
}

void nave_inicializar(nave_t *nave, figura_t *figura_nave){
    nave_setear_figura(nave, figura_nave);
    figura_rotar(nave->figura, nave->angulo_actual);
}