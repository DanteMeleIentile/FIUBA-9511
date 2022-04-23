#include <stdio.h>
#include <math.h>
//DIMENTSION -1

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

double computar_escalar(double px, double py, double ax, double ay, double bx, double by){
    return prod_interno(px-ax, py-ay, bx-ax, by-ay) / pow (norma (bx, by, ax, ay),2);
}

double distancia_punto_a_polilinea(const float polilinea[][2], size_t n, double px, double py){
    double d_menor = norma (px, py, polilinea[0][X], polilinea[0][Y]);
    double d_temp = 0;
    for (int i = 0; i < n-1; i++){
        double ax = polilinea[i][X];
        double ay = polilinea[i][Y];

        double bx = polilinea[i+1][X];
        double by = polilinea[i+1][Y];

        if (computar_escalar(px, py, ax, ay, bx, by) <= 0){
            d_temp = norma (px, py, ax, ay);
            
            //printf("distancia temporal: %f\n\n", d_temp);

        } else if (computar_escalar(px, py, ax, ay, bx, by) >= 1){
            d_temp = norma (py, px, bx, by);

            //printf("distancia temporal: %f\n\n", d_temp);

        } else{
            double vd[2];
            vd[X] = ax + computar_escalar(px, py, ax, ay, bx, by) * (bx - ax);
            vd[Y] = ay + computar_escalar(px, py, ax, ay, bx, by) * (by - ay);

            d_temp = norma (px, py, vd[X], vd[Y]);
            //printf("distancia temporal: %f\n\n", d_temp);
        }

        if (d_menor > d_temp){
            d_menor = d_temp;
        }
    }
    printf("distancia a polilinea: %f\n\n", d_menor);

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

    //double p[] = {0, 7};
    double puntos[][2] = {
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

    size_t n = sizeof (polilinea) / sizeof(polilinea[0]);
    
    //distancia_punto_a_polilinea (polilinea, n, p[X], p[Y]);

    size_t p = sizeof (puntos) / sizeof(puntos[0]);

    for (int i = 0; i < p; i++){
        double px = puntos[i][X];
        double py = puntos[i][Y];
        distancia_punto_a_polilinea (polilinea, n, px, py);

    }

    return 0;
}

/* COMENTARIOS */
// Falta mensaje de error!!!
//Cambié la función de santisi (tipo de dato!
// Que onda el cost float
// compitibilidad con "rotar" y "trasladar"