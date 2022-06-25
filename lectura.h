#ifndef LECTURA_H
#define LECTURA_H

#include "polilinea.h"
#include "figura.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

bool leer_encabezado_figura(FILE *f, char nombre[], figura_tipo_t *tipo, bool *infinito, size_t *cantidad_polilineas);

polilinea_t *leer_polilinea(FILE *f);

#endif