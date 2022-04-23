#include <stdio.h>
#include <math.h>

#define X 0
#define Y 1

double prod_interno (double ax, double ay, double bx, double by){
    return (ax * bx) + (ay * by);
}

double norma(double ax, double ay, double bx, double by){
    double resta_x = ax - bx;
    double resta_y = ay - by;
    return sqrt(pow(resta_x, 2) + pow(resta_y, 2));
}

double computar_escalar(float px, float py, double ax, double ay, double bx, double by){
    return prod_interno(px-ax, py-ay, bx-ax, by-ay) / pow (norma (bx, by, ax, ay),2);
}

double distancia_punto_a_polilinea(const float polilinea[][2], size_t n, float px, float py){
    double d_menor = norma (px, py, polilinea[0][X], polilinea[0][Y]);
    
    double d_temp = 0;

    for (int i = 0; i < n-1; i++){
        double ax = polilinea[i][X];
        double ay = polilinea[i][Y];
        double bx = polilinea[i+1][X];
        double by = polilinea[i+1][Y];
        if (computar_escalar(px, py, ax, ay, bx, by) <= 0){
            d_temp = norma (px, py, ax, ay);
        } else if (computar_escalar(px, py, ax, ay, bx, by) >= 1){
            d_temp = norma (px, py, bx, by);
        } else{
            double vd[2];
            vd[X] = ax + computar_escalar(px, py, ax, ay, bx, by) * (bx - ax);
            vd[Y] = ay + computar_escalar(px, py, ax, ay, bx, by) * (by - ay);

            d_temp = norma (px, py, vd[X], vd[Y]);
        }

        if (d_menor > d_temp){
            d_menor = d_temp;
        }
    }
    printf("distancia a polilinea: %.8f ", d_menor);
    return d_menor;
}

int main (void){
    const float polilinea[][2] = {
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

    double resultados[] = {
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
    for (int i = 0; i < p; i++){
        double d_menor = distancia_punto_a_polilinea (polilinea, n, puntos[i][X], puntos[i][Y]);
        
        if (resultados[i] != trunc(d_menor*1000000)/1000000){
            printf ("- RESULTADO INVALIDO\n");
        } else{
            printf ("\n");
        }
    }
    return 0;
}

/* COMENTARIOS */
// Que onda el cost float
// compitibilidad con "rotar" y "trasladar"