#include <stdio.h>
#include <math.h>
//DIMENTSION -1
#define DISTANCIA_X 1
#define DISTANCIA_Y 1
#define ANGULO_INICIAL 50
#define PI 3.14159265359

/* ----- CONVERSOR DE GRADOS A RADIANES ----- */
double DEG_A_RAD(double grados){
    return grados * PI / 180;
}

/* ----- FUNCION TRASLARA ----- */

/* void trasladar (float polilinea [][2], size_t n, float dx, float dy){
    for (int i = 0; i < n; i++){
        polilinea [i][0] += dx;
        polilinea [i][1] += dy;
    }
}*/

/* ----- FUNCION ROTAR ----- */
void rotar (float polilinea [][2], size_t n, float rad){
    float polilinea_r[3][2];
    for (int i = 0; i < n; i++){
        polilinea_r[i][0] = polilinea[i][0];
        polilinea_r[i][1] = polilinea[i][1];
    }

    for (int i = 0; i < n; i++){
        polilinea_r[i][0] =( polilinea [i][0] * cos(rad) ) - ( polilinea [i][1] * sin(rad));
        polilinea_r[i][1] = polilinea [i][0] * sin(rad) + polilinea [i][1] * cos(rad);
    }
    
    for (int i = 0; i < n; i++){
        printf ("(%f, %f)\n", polilinea_r[i][0], polilinea_r[i][1]);
        //printf ("(%d)\n", n);
    } 

/* ----- FUNCION ROTAR SIN polilinea_r ----- */

    /* for (int i = 0; i < n; i++){
        polilinea [i][0] =( polilinea [i][0] * cos(rad) ) - ( polilinea [i][1] * sin(rad));
        polilinea [i][1] = polilinea [i][0] * sin(rad) + polilinea [i][1] * cos(rad);
    } */
}

/* ----- FUNCION DIST PUNTO A SEGMENTO ----- */
void resta_vectores (double v1[][2], double v2[][2], size_t n, double resta[][2]){
    for (int i = 0; i < n; i++){
        resta[i][0] = v2[i][0] - v1[i][0];
        resta[i][1] = v2[i][1] - v1[i][1];
    }
}


double distancia_punto_a_polilinea (const float polilinea[][2], size_t n, float px, float px)


int main (void){
    float polilinea[][2] = {{0, 1}, {1, 3}, {1, 5}};
    int n = sizeof(polilinea)/sizeof (polilinea[0]); //debe dar 3=3

    /* ----- LLAMADO FUNCION  TRASLADAR ----- */

    /* trasladar(polilinea, n, DISTANCIA_X, DISTANCIA_Y);
    for (int i = 0; i < n; i++){
        printf ("(%f, %f)\n", polilinea[i][0], polilinea[i][1]);
        //printf ("(%d)\n", n);
    } */

    //printf ("(%d)\n", n);

    /* ----- LLAMADO FUNCION ROTAR----- */
    rotar(polilinea, n, DEG_A_RAD(90));

    /*for (int i = 0; i < n; i++){
        printf (", %f)\n", polilinea_r[i][1]);
        //printf ("(%d)\n", n);
    }  */

    /* ----- LLAMADO FUNCION  DIST PUNTO A SEGMENTO ----- */


    double resta[][2];
    double v1[][2] = {0, 1};
    double v2[][2] = {2, 1}; 
    int n1 = sizeof(v1)/sizeof (v1[0]); //debe dar 3=3
    int n = sizeof (v2)/sizeof (v2[0]); //debe dar 3=3
    
    restar_vectores (v1, v2, n1, n2, resta)


    distancia_punto_a_polilinea(polilinea, n, px, py);



}