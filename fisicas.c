#include <math.h>

#include "fisicas.h"

#define PI 3.14159265358979323846

float computar_velocidad(float vi, float a, double dt){
    return (vi + a * dt);
}

float computar_posicion(float pi, float vi, double dt){
    return (pi + vi * dt);
}

double computar_angulo(float x_centro, float y_centro, float x_movil, float y_movil){
    return atan2((y_centro - y_movil),(x_centro - x_movil)) + PI;

}

float distancia_entre_puntos(float x1, float y1, float x2, float y2){
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double DEG_A_RAD(double grados){
    return grados * PI / 180;
}