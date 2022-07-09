#include "nivel.h"
#include "figura.h"
#include "lista.h"

struct nivel {
    figura_t *fig;
    lista_t *torretas;
    lista_t *disparos;
    lista_t *combustible;
};



