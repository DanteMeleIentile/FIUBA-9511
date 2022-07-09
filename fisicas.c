#include <math.h>

#include "fisicas.h"
#include "config.h"

double computar_velocidad(double vi, double a, double dt){
    return (vi + a * dt);
}

double computar_posicion(float pi, double vi, double dt){
    return (pi + vi * dt);
}

double computar_angulo(float x_centro, float y_centro, float x_movil, float y_movil){
    return atan2((y_centro - y_movil),(x_centro - x_movil)) + PI;

}


double distancia_entre_puntos(float x1, float y1, float x2, float y2){
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
