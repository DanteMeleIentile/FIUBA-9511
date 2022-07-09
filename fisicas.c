#include <math.h>

#include "fisicas.h"

double computar_velocidad(double vi, double a, double dt){
    return (vi + a * dt);
}

double computar_posicion(double pi, double vi, double dt){
    return (pi + vi * dt);
}

double distancia_entre_puntos(double x1, double y1, double x2, double y2){
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
