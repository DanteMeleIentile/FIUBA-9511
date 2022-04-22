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
    double resta_y = bx - by;;
    return sqrt(pow(resta_x, 2) + pow(resta_y, 2));
}

double computar_escalar(double px, double py, double ax, double ay, double bx, double by){
    return prod_interno(px-ax, py-ay, bx-ax, by-ay) / pow (norma (bx, by, ax, ay),2);
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

    /* double puntos[][2] = {
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
    }; */

    punto[] = {2, 2};

    size_t n = sizeof (polilinea) / sizeof(polilinea[0]);
    
    for (int i = 0; i < n-1; i++){
        double ax = polilinea[i][X];
        double ay = polilinea[i][Y];

        double bx = polilinea[i+1][X];
        double by = polilinea[i+1][Y];

        if (computar_escalar(p, v2, v1, 2) <= 0){
                norma (p, v1);
                printf("%f\n", norma(p, v1));

            } else if (computar_escalar(p, v2, v1, 2) >= 1){
                norma (p, v2);
                printf("%f\n", norma(p, v2));

            } else{
                resta_vectores (resta_3, p, v1, 2);
                double vd[2];
                vd[0] = v1[0] + computar_escalar(p, v2, v1, 2) * resta_3[0];
                vd[1] = v1[1] + computar_escalar(p, v2, v1, 2) * resta_3[1];
                
                //punto d e recta en condición de que el punto esté en el medio
                printf("%f, %f\n", vd[0], vd[1]);

                //impresión de norma 
                printf("%f\n", norma(p, vd));
            }


        computar_escalar ()

        printf("%f\n", ax);
        printf("%f\n\n", ay);

        printf("%f\n", bx);
        printf("%f\n\n", by);

        
    }

    return 0;
}


    /*double resta_3[2];
    if (computar_escalar(p, v2, v1, 2) <= 0){
        norma (p, v1);
        printf("%f\n", norma(p, v1));

    } else if (computar_escalar(p, v2, v1, 2) >= 1){
        norma (p, v2);
        printf("%f\n", norma(p, v2));

    } else{
        resta_vectores (resta_3, p, v1, 2);
        double vd[2];
        vd[0] = v1[0] + computar_escalar(p, v2, v1, 2) * resta_3[0];
        vd[1] = v1[1] + computar_escalar(p, v2, v1, 2) * resta_3[1];
        
        //punto d e recta en condición de que el punto esté en el medio
        printf("%f, %f\n", vd[0], vd[1]);

        //impresión de norma 
        printf("%f\n", norma(p, vd));
    }
} */

