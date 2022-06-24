#include <SDL2/SDL.h>
#include <stdbool.h>

#include "config.h"
#include "polilinea.h"
#include "color.h"
#include "figura.h"


int main() {
    FILE *file1 = fopen("/figuras.bin", "rb");

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Gravitar");

    int dormir = 0;
    char nombre[20];
    bool infinito;
    figura_tipo_t tipo;
    size_t cantidad_polilineas;

    // Queremos que todo se dibuje escalado por f:
    float f = 10;

    // BEGIN código del alumno
    // Mi nave:
    const float nave[][2] = {{8, 0}, {-1, 6}, {-4, 4}, {-4, 2}, {-2, 0}, {-4, -2}, {-4, -4}, {-1, -6}, {8, 0}};
    size_t nave_tam = 9;

    // TEST:
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


    // El chorro de la nave:
    const float chorro[][2] = {{-4, 2}, {-8, 0}, {-4, -2}};
    size_t chorro_tam = 3;

    bool chorro_prendido = false;

    // END código del alumno

    unsigned int ticks = SDL_GetTicks();
    while(1) {
        if(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                break;
            // BEGIN código del alumno
            if (event.type == SDL_KEYDOWN) {
                // Se apretó una tecla
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        // Prendemos el chorro:
                        chorro_prendido = true;
                        break;
                    case SDLK_DOWN:
                    case SDLK_RIGHT:
                    case SDLK_LEFT:
                        break;
                }
            }
            else if (event.type == SDL_KEYUP) {
                // Se soltó una tecla
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        // Apagamos el chorro:
                        chorro_prendido = false;
                        break;
                }
            }
            // END código del alumno
            continue;
        }

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);

        // BEGIN código del alumno
        // Dibujamos la nave escalada por f en el centro de la pantalla:
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0x00);
        for(int i = 0; i < nave_tam - 1; i++)
            SDL_RenderDrawLine(
                renderer,
                nave[i][0] * f + VENTANA_ANCHO / 2,
                -nave[i][1] * f + VENTANA_ALTO / 2,
                nave[i+1][0] * f + VENTANA_ANCHO / 2,
                -nave[i+1][1] * f + VENTANA_ALTO / 2
            );

        if(chorro_prendido) {
            // Dibujamos el chorro escalado por f en el centro de la pantalla:
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
            for(int i = 0; i < chorro_tam - 1; i++)
                SDL_RenderDrawLine(
                    renderer,
                    chorro[i][0] * f + VENTANA_ANCHO / 2,
                    -chorro[i][1] * f + VENTANA_ALTO / 2,
                    chorro[i+1][0] * f + VENTANA_ANCHO / 2,
                    -chorro[i+1][1] * f + VENTANA_ALTO / 2
                );
        }
        // END código del alumno

        SDL_RenderPresent(renderer);
        ticks = SDL_GetTicks() - ticks;
        if(dormir) {
            SDL_Delay(dormir);
            dormir = 0;
        }
        else if(ticks < 1000 / JUEGO_FPS)
            SDL_Delay(1000 / JUEGO_FPS - ticks);
        ticks = SDL_GetTicks();
    }

    // BEGIN código del alumno
    // No tengo nada que destruir.
    // END código del alumno

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    fclose(file1);

    return 0;
}

