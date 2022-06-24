#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "color.h"
#include "figura.h"
#include "polilinea.h"

int main(void) {
    FILE *file1 = fopen("/figuras.bin", "rb");

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window;
    SDL_Renderer *renderer;
    //SDL_Event event;

    SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Gravitar");

    //leer una figura

    float f = 10;

        char nombre[20];
        bool infinito;
        figura_tipo_t tipo;
        size_t cantidad_polilineas;

    if(! leer_encabezado_figura(file1, nombre, &tipo, &infinito, &cantidad_polilineas))
            return 1;

    for(size_t i = 0; i < cantidad_polilineas; i++) {
            polilinea_t *p = leer_polilinea(file1);
            if(p == NULL) {
                fprintf(stderr, "Error en el archivo");
                fclose(file1);
                return 1;
            }

            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0x00);

            for(size_t j = 0; j < p->n - 1; j++)
                SDL_RenderDrawLine(
                    renderer,
                    p->puntos[j][0] * f + VENTANA_ANCHO / 2,
                    -p->puntos[j][1] * f + VENTANA_ALTO / 2,
                    p->puntos[j+1][0] * f + VENTANA_ANCHO / 2,
                    -p->puntos[j+1][1] * f + VENTANA_ALTO / 2
                );

            polilinea_destruir(p);
    }

    fclose(file1);

    return 0;
}