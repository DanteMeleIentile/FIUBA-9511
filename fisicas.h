#ifndef FISICAS_H
#define FISICAS_H

/*
** Calcula cuánto debe cambiar la velocidad dada según la aceleracion y el intervalo de tiempo.
*/
float computar_velocidad(float v, float a, double dt);

/*
** calcula cuánto debe cambiar la posicion dada según la velocidad y el intervalo de tiempo.
*/
float computar_posicion(float pi, float vi, double dt);

/*
** Calcula el angulo entre 2 puntos
** PRE: Se considera el origen de coordenadas ubicado en x_centro, y_centro.
** POST: El angulo está entre 0 y 2 PI
*/
double computar_angulo(float x_centro, float y_centro, float x_movil, float y_movil);

/*
** Calcula la distancia entre dos puntos.
*/
float distancia_entre_puntos(float x1, float y1, float x2, float y2);

#endif //FISICAS_H