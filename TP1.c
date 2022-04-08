    /* TRABAJO PRÁCTICO N°1
Link consignas: https://algoritmos9511.gitlab.io/tps/20221_ej1.html */

/* FUNCIONES PLANTEADAS PARA LA EVOLUCIÓN EN EL TIEMPO
double computar_velocidad(double vi, double a, double dt);
double computar_posicion(double pi, double vi, double dt);

double computar_velocidad(double vi, double a, double dt){
    return (vi + a * dt);
}

double computar_posicion(double pi, double vi, double dt){
    return (pi + vi * dt);
} */

#include <stdio.h>
#include <math.h>

#define DT 0.001
#define G 9.81
#define VELOCIDAD_INICIAL 20
#define ANGULO_INICIAL 50
#define X_INICIAL 0
#define Y_INICIAL 0

#define PI 3.14159265359

/* double conversor_radianes(double angulo_inicial){
    return angulo_inicial * PI/180;
} */

double DEG_A_RAD(double grados){
    return grados * PI / 180;
}

double velocidad_inicial_x(double vi, double angulo_inicial){
    return vi * cos(DEG_A_RAD(angulo_inicial));
}

double velocidad_inicial_y(double vi, double angulo_inicial){
    return vi * sin(DEG_A_RAD(angulo_inicial));
}

double computar_velocidad(double vi, double a, double dt){
    return (vi + a * dt);
}

double computar_posicion(double pi, double vi, double dt){
    return (pi + vi * dt);
}

int main(){
    printf("TRABAJO PRÁCTICO N°1 - DANTE MELE IENTILE\n");
    double velocidad_x = velocidad_inicial_x(VELOCIDAD_INICIAL, ANGULO_INICIAL);
    double velocidad_y = velocidad_inicial_y(VELOCIDAD_INICIAL, ANGULO_INICIAL);
    double posicion_x = X_INICIAL;
    double posicion_y = Y_INICIAL;
    double t = 0;
    printf("Posición X: \t\t\tPosición Y: \t\t\tTime: \t\t\t\n");
    
    while (posicion_y >= 0){
        printf("%lf\t\t\t", posicion_x);
        printf("%lf\t\t\t", posicion_y);
        printf("%lf\t\t\t", velocidad_x);
        printf("%lf\t\t\t", velocidad_y);
        printf("%lf\t\t\t\n", t);
        velocidad_y = computar_velocidad(velocidad_y, -G, DT);

        posicion_x = computar_posicion(posicion_x, velocidad_x, DT);
        posicion_y = computar_posicion(posicion_y, velocidad_y, DT);

        t += DT;
    }
    return 0;
}
