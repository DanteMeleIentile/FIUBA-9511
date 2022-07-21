#ifndef _CONFIG_H_
#define _CONFIG_H_

#define PI 3.14159265358979323846

#define VENTANA_ANCHO 800
#define VENTANA_ALTO 600

#define MARGEN_ALTURA 0.7
#define MARGEN_ANCHO 0.7
#define MARGEN_NIVEL_FIJO 0.9
#define ESCALA_MINIMA 0.6

#define JUEGO_FPS 100
#define JUEGO_COMBUSTIBLE_INICIAL 100000000
#define JUEGO_COMBUSTIBLE_POT_X_SEG 250
#define JUEGO_COMBUSTIBLE_ESC_X_SEG 500

#define G 10

#define NAVE_ROTACION_PASO (PI/20)
#define NAVE_ACELERACION (10*G)

#define NAVE_ANGULO_INICIAL (PI/2)

#define X 0
#define Y 1

#define TIEMPO_MAX_DISPAROS 2
#define VEL_DISPARO 150

#define COOLDOWN_NAVE 0.2
#define COOLDOWN_TORRETA 3

#define SCORE_NEXT_SHIP 10000

#define TIEMPO_REACTOR 90

#define DT (1.0/JUEGO_FPS)

#define ESCALA_NIVEL_0 1

#define DMIN 7

#endif // _CONFIG_H_
