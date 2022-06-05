#ifndef LECTURA_H
#define LECTURA_H

#include "polilineas.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>



/*
** Recibe un archivo "f" y, de ser posible, devuelve el "nombre", el "tipo", si es de tipo infinito y la cantidad de polilíneas asociadas a una figura junto con un "true" que indica el exito de la lectura. Caso contrario, devuelve "false".
*/
bool leer_encabezado_figura(FILE *f, char nombre[], figura_tipo_t *tipo, bool *infinito, size_t *cantidad_polilineas);

/*
** Lee un archivo "f" y devuelva una polilínea con lo parámetros indicados. En caso de error devuelve "NULL".
*/
polilinea_t *leer_polilinea(FILE *f);

#endif