#ifndef FISICAS_H
#define FISICAS_H

double computar_velocidad(double v, double a, double dt);

double computar_posicion(float pi, double vi, double dt);

/*
** Calcula el angulo entre 2 puntos
** PRE: Se considera el origen de coordenadas ubicado en x_centro, y_centro
** POST: El angulo está entre 0 y 2 PI
*/
double computar_angulo(float x_centro, float y_centro, float x_movil, float y_movil);

double distancia_entre_puntos(float x1, float y1, float x2, float y2);

#endif