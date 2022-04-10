/* -----------TRABAJO PRÁCTICO N°1 - Dante Mele Ientile --------------
Link consignas: https://algoritmos9511.gitlab.io/tps/20221_ej1.html */

#include <stdio.h>
#include <math.h>

#define DT 0.001
#define G 9.81
#define VELOCIDAD_INICIAL 20
#define ANGULO_INICIAL 50
#define X_INICIAL 0
#define Y_INICIAL 0
#define PI 3.14159265359

/* ----- CONVERSOR DE GRADOS A RADIANES ----- */
double DEG_A_RAD(double grados){
    return grados * PI / 180;
}
 
/* ----- FUNCIONES QUE CALCULAN VELOCIDADES INICIALES ----- */

double velocidad_inicial_x(double vi, double angulo_inicial){
    return vi * cos(DEG_A_RAD(angulo_inicial));
}

double velocidad_inicial_y(double vi, double angulo_inicial){
    return vi * sin(DEG_A_RAD(angulo_inicial));
}

/* ----- FUNCIONES QUE CALCULAN VELOCIDAD Y POSICIÓN ----- */

double computar_velocidad(double vi, double a, double dt){
    return (vi + a * dt);
}

double computar_posicion(double pi, double vi, double dt){
    return (pi + vi * dt);
}

int main(){
    double velocidad_x = velocidad_inicial_x(VELOCIDAD_INICIAL, ANGULO_INICIAL);
    double velocidad_y = velocidad_inicial_y(VELOCIDAD_INICIAL, ANGULO_INICIAL);
    double posicion_x = X_INICIAL;
    double posicion_y = Y_INICIAL;
    double t = 0;
    printf("T,X,Y\n");
    
    while (posicion_y >= 0){
        printf("%.4lf,%.4lf,%.4lf\n", t, posicion_x, posicion_y);
        velocidad_x = computar_velocidad(velocidad_x, 0, DT);
        velocidad_y = computar_velocidad(velocidad_y, -G, DT);

        posicion_x = computar_posicion(posicion_x, velocidad_x, DT);
        posicion_y = computar_posicion(posicion_y, velocidad_y, DT);

        t += DT;
    }
    return 0;
}