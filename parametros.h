#ifndef _PARAMETROS_H_
#define _PARAMETROS_H_

typedef enum{
    NIVEL0 = 0,
    NIVEL1 = 1,
    NIVEL2 = 2,
    NIVEL3 = 3,
    NIVEL4 = 4,
    NIVEL5 = 5,
} tabla_niveles;

const int tabla_bonus[] = {
    [NIVEL0] = 0,
    [NIVEL1] = 2000,
    [NIVEL2] = 4000,
    [NIVEL3] = 6000,
    [NIVEL4] = 8000,
    [NIVEL5] = 9000,
};

const size_t tabla_cant_torretas[] = {
    [NIVEL0] = 0,
    [NIVEL1] = 2,
    [NIVEL2] = 4,
    [NIVEL3] = 6,
    [NIVEL4] = 8,
    [NIVEL5] = 0,
};

const size_t tabla_cant_combustibles[] = {
    [NIVEL0] = 0,
    [NIVEL1] = 2,
    [NIVEL2] = 2,
    [NIVEL3] = 3,
    [NIVEL4] = 4,
    [NIVEL5] = 0,
};

const float tabla_ubicacion_torretas[][3] = {
    {916, 75, -0.66},
    {1425, 159, 0.66},
//Cambio de nivel

    {423, 195, -0.66},
    {806, 215, -0.33},
    {1254, 153, 0.66},
    {1587, 223, 2.23},
//Cambio de nivel

    {70, 46, 0},
    {506, 12, 0},
    {952, 12, 0},
    {1385, 12, 0},
    {757, 210, 3.14},
    {1161, 210, 3.14},
//Cambio de nivel

    {257, 440, 0.66},
    {719, 674, 2.23},
    {985, 565, 0},
    {1125, 417, 3.8},
    {862, 163, 3.8},
    {626, 323, 2.23}, 
    {505, 331, 3.8},
    {378, 296, 2.23},
};

const float tabla_ubicacion_combustibles[][3] = {
    {1064, 13, 0},
    {1685, 113, 0},
//Cambio de nivel

    {482, 94, 0},
    {1751, 247, 0},
//Cambio de nivel

    {820, 46, 0},
    {1196, 68, 0},
    {1602, 46, 0},

//Cambio de nivel
    {188, 429, 0},
    {667, 600, 0},
    {1054, 404, 3.14},
    {574, 344, 3.14},
};


typedef enum{
    BASE1  = NIVEL0,
    PLANETA1 = NIVEL1,
    PLANETA2 = NIVEL2,
    PLANETA3 = NIVEL3,
    PLANETA4 = NIVEL4,
    PLANETA5 = NIVEL5,
    ESTRELLA,
} tabla_planeta;

const float tabla_ubicacion_planetas[][2] = {
    [PLANETA1] = {663, 473},
    [PLANETA2] = {671, 145},
    [PLANETA3] = {110, 79},
    [PLANETA4] = {204, 455},
    [PLANETA5] = {111, 307},
    [ESTRELLA] = {457, 364},
    [BASE1] = {388, 218},
};

#endif // _CONFIG_H_