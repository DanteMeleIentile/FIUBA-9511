#include <stdio.h>
#include <math.h>

#define DISTANCIA_X 1.5
#define DISTANCIA_Y 0.5

#define ANGULO_INICIAL 90

//CORRECCIÓN
#define PI 3.141592653589793116

#define X 0
#define Y 1



double DEG_A_RAD(double grados){
    return grados * PI / 180;
}


double prod_interno (double ax, double ay, double bx, double by){
    return (ax * bx) + (ay * by);
}


double norma(double ax, double ay, double bx, double by){
    double resta_x = ax - bx;
    double resta_y = ay - by;
    return sqrt((resta_x * resta_x) + (resta_y * resta_x));
}


double norma_2(double x, double y){
    return sqrt((x * x) + (y * x));
}


double computar_escalar(float px, float py, double ax, double ay, double bx, double by){
    return prod_interno(px-ax, py-ay, bx-ax, by-ay) / pow (norma (bx, by, ax, ay),2);
}

double distancia_punto_a_segmento(float polilinea[][2], size_t n, float px, float py){


}


double distancia_punto_a_polilinea(float polilinea[][2], size_t n, float px, float py){
    double d_menor = norma (px, py, polilinea[0][X], polilinea[0][Y]); //dist punto a segmento
    
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
    return d_menor;
}


void trasladar (float polilinea [][2], size_t n, float dx, float dy){
    for (int i = 0; i < n; i++){
        polilinea [i][X] += dx;
        polilinea [i][Y] += dy;
    }
}


void rotar (float polilinea [][2], size_t n, double rad){
    float polilinea_r[n];
    for (int i = 0; i < n; i++){
        polilinea_r[i] = polilinea[i][0];
        polilinea_r[i] = ( polilinea [i][X] * cos(rad) ) - ( polilinea [i][Y] * sin(rad) );

        polilinea[i][Y] = polilinea [i][X] * sin(rad) + polilinea [i][Y] * cos(rad);
        
        polilinea[i][X] = polilinea_r[i];
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

    trasladar(polilinea, n, DISTANCIA_X, DISTANCIA_Y);
    printf ("\nPolilinea trasladada x = _; y = _: \n");
    for (int i = 0; i < n; i++){
        printf ("(%f, %f)\n", polilinea[i][0], polilinea[i][1]); //Descomentar para validar traslación
    }

    rotar(polilinea, n, DEG_A_RAD(ANGULO_INICIAL));
    printf ("\nPolilinea rotada _°: \n");
    for (int i = 0; i < n; i++){
        printf ("(%f, %f)\n", polilinea[i][0], polilinea[i][1]); //Descomentar para validar rotación
    }

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