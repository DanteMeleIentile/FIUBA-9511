#include <stdint.h>

#include "figura.h"
#include "polilinea.h"

const char figura_tipo_s[8][15] = {
    [ICONO] = "Icono", 
    [NIVEL] = "Nivel", 
    [SPRITE] = "Sprite",
    [PLANETA] = "Planeta",
    [BASE] = "Base",
    [COMBUSTIBLE] = "Combustible",
    [TORRETA] = "Torreta",
    [REACTOR] = "Reactor",
};