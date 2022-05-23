#include <stdio.h>
#include <math.h>

#define DISTANCIA_X 1.5
#define DISTANCIA_Y 0.5

#define ANGULO_INICIAL 90

#define PI 3.141592653589793116

#define X 0
#define Y 1



double DEG_A_RAD(double grados){
    return grados * PI / 180;
}



//"prod_interno" calcula el producto interno de dos vectores A = (ax; ay) y B = (bx;by)
double prod_interno (double ax, double ay, double bx, double by){
    return (ax * bx) + (ay * by);
}



//"norma" calcula la norma de un vector
double norma(double x, double y){
    return sqrt((x * x) + (y * x));
}



//"dist_puntos" calcula la distancia entre dos puntos A = (ax; ay) y B = (bx;by)
double dist_puntos (double ax, double ay, double bx, double by){
    double resta_x = ax - bx;
    double resta_y = ay - by;
    return sqrt((resta_x * resta_x) + (resta_y * resta_y));
}



//"computar_alpha" calcula el escalar utilizado en "dist_punto_a_segmento"
double computar_alpha(double ax, double ay, double bx, double by, float px, float py){
    double norma_cuadrado = dist_puntos (bx, by, ax, ay);
    norma_cuadrado *= norma_cuadrado;
    return prod_interno (px-ax, py-ay, bx-ax, by-ay) / (norma_cuadrado);
}



//"dist_punto_a_segmento" calcula la distancia entre un punto P = (px; py) y el segmento AB, siendo A = (px; py) y B = (bx;by) 
double dist_punto_a_segmento(float ax, float ay, float bx, float by, float px, float py){
        
    double alpha = computar_alpha(ax, ay, bx, by, px, py);

    if (alpha <= 0){
        return dist_puntos (px, py, ax, ay);;
    } else if (alpha >= 1){
        return dist_puntos (px, py, bx, by);
    }
    double vd[2];
    vd[X] = ax + alpha * (bx - ax);
    vd[Y] = ay + alpha * (by - ay);

    return dist_puntos (px, py, vd[X], vd[Y]);
}



double distancia_punto_a_polilinea(float polilinea[][2], size_t n, float px, float py){
    double d_menor = dist_punto_a_segmento (polilinea[0][X], polilinea[0][Y], polilinea[1][X], polilinea[1][Y], px, py);

    double d_temp = 0;

    for (int i = 1; i < n-1; i++){
        double ax = polilinea[i][X];
        double ay = polilinea[i][Y];
        double bx = polilinea[i+1][X];
        double by = polilinea[i+1][Y];
        
        d_temp = dist_punto_a_segmento(ax, ay, bx, by, px, py);

        if (d_temp < d_menor){
            d_menor = d_temp;
        }
    }
    return d_menor;
}



void trasladar (float polilinea [][2], size_t n, float dx, float dy){
    for (int i = 0; i < n; i++){
        polilinea [i][X] += dx;
        polilinea [i][Y] += dy;
    }
}


void rotar (float polilinea [][2], size_t n, double rad){
    float polilinea_r;
    double coseno = cos(rad);
    double seno = sin(rad);

    for (int i = 0; i < n; i++){
        polilinea_r = (polilinea [i][X] * coseno) - (polilinea [i][Y] * seno);
        
        polilinea[i][Y] = (polilinea [i][X] * seno) + (polilinea [i][Y] * coseno);
        polilinea[i][X] = polilinea_r;
    }
}


int main (void){
    float polilinea[][2] = {
        {0, 1}, 
        {1, 3}, 
        {1, 5}, 
        {2, 5}, 
        {3, 4}, 
        {4, 4}, 
        {5, 3}, 
        {4, 2}, 
        {5, 1}, 
        {2, 0}
    };

    float puntos[][2] = {
        {0, 0},
        {0, 2},
        {6, 1},
        {2, 2},
        {1, 1},
        {1, 4},
        {5, 4},
        {-1, -3},
        {3, 3},
        {5, 3},
        {0, 7}
    };

    double resultados_punto_a_polilinea[] = {
        1.000000,
        0.447213,
        1.000000,
        1.341640,
        0.894427,
        0.000000,
        0.707106,
        4.123105,
        1.000000,
        0.000000,
        2.236067
    };

    size_t n = sizeof (polilinea) / sizeof(polilinea[0]);
    size_t p = sizeof (puntos) / sizeof(puntos[0]);

    /* trasladar(polilinea, n, DISTANCIA_X, DISTANCIA_Y);
    printf ("\nPolilinea trasladada x = %f; y = %f: \n", DISTANCIA_X, DISTANCIA_Y);
    for (int i = 0; i < n; i++){
        //printf ("(%f, %f)\n", polilinea[i][X], polilinea[i][Y]); //Descomentar para validar traslación
    } */

    /* rotar(polilinea, n, DEG_A_RAD(ANGULO_INICIAL));
    printf ("\nPolilinea rotada %d°: \n", ANGULO_INICIAL);
    for (int i = 0; i < n; i++){
        //printf ("(%f, %f)\n", polilinea[i][X], polilinea[i][Y]); //Descomentar para validar rotación
    } */

    for (int i = 0; i < p; i++){
        double d_menor = distancia_punto_a_polilinea (polilinea, n, puntos[i][X], puntos[i][Y]);
        printf("%.8f ", d_menor);

        if (resultados_punto_a_polilinea[i] != trunc(d_menor*1000000)/1000000){
            printf ("- RESULTADO INVALIDO\n");
        } else{
            printf ("\n");
        }
    }
    

return 0;
}