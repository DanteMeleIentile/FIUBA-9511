#include <SDL2/SDL.h>
#include <stdbool.h>

#include "polilinea.h"
#include "lista.h"
#include "figura.h"
#include "lectura.h"
#include "config.h"
#include "config.h"

int main() {
    
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Gravitar");

    int dormir = 0;

    // BEGIN código del alumno

//----------------------------------------------------------------------------------------------------------------------
//CREACIÓN DE ESTRUCTURA DE LECTURA


    FILE *f1 = fopen("figuras.bin", "rb");
    if(f1 == NULL) {
        fprintf(stderr, "No pudo abrirse figuras.bin\n");
        return 1;
    }

//Creamos un puntero que apunta a un vector "vector_figuras" de una (1) figura_t


    figura_t **vector_figuras = malloc(sizeof(figura_t*));
    if(vector_figuras == NULL){
        fprintf(stderr, "Error de memoria");
        return 1;
    }

    char nombre[20];
    bool infinito;
    figura_tipo_t tipo;
    size_t cant_polilineas;

    size_t cant_figuras = 0;

    for(size_t i = 0; leer_encabezado_figura(f1, nombre, &tipo, &infinito, &cant_polilineas); i++){
        if(i != 0)
            vector_figuras = realloc(vector_figuras, (i + 1) * sizeof(figura_t*)); //Agrega una componente a "vector_figuras" hasta que no pueda leer mas figuras
            //CHEQUEAR ESTO
        vector_figuras[i] = figura_crear(nombre, tipo, infinito, cant_polilineas); //Iguala cada componente a la figura leida del archivo

        polilinea_t **vector_polilineas = malloc(sizeof(polilinea_t*) * cant_polilineas); //Creamos un puntero que apunta a un vector "vector_polilineas" de "cant_polilineas"z polilinea_t

        if(vector_polilineas == NULL){
            fprintf(stderr, "Error de memoria");
            return 1;
        }

        for(size_t j = 0; j < cant_polilineas; j++){
            vector_polilineas[j] = leer_polilinea(f1); //Iguala cada componente de las polilineas de cada figura leida del archivo
        }

        if(!figura_setear_polilinea(vector_figuras[i], vector_polilineas)){
            fprintf(stderr, "ERROR");
            return 1; // ERROR 
        }

        cant_figuras++; //EVALUAR
    }

    printf("CANT FIGURAS = %zd\n", cant_figuras);

    fclose(f1);


//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//CREACIÓN DE "LISTA ACTIVA"
    lista_t *lista_activa = lista_crear();

    figura_agregar_en_lista("BASE", lista_activa);
    figura_agregar_en_lista("PLANETA3", lista_activa);
    figura_eliminar_en_lista("BASE", lista_activa);


//----------------------------------------------------------------------------------------------------------------------
    
    
    // Mi nave:
    const float nave[][2] = {{8, 0}, {-1, 6}, {-4, 4}, {-4, 2}, {-2, 0}, {-4, -2}, {-4, -4}, {-1, -6}, {8, 0}};
    size_t nave_tam = 9;

    // El chorro de la nave:
    const float chorro[][2] = {{-4, 2}, {-8, 0}, {-4, -2}};
    size_t chorro_tam = 3;

    bool chorro_prendido = false;

    // Queremos que todo se dibuje escalado por f:
    float f = 10;
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
//---------------------------------------------------------------
    lista_iter_t *iter = lista_iter_crear(lista_activa);
    size_t i = 0;
    
    while(i < lista_largo(lista_activa)){
        for (size_t j = 0; j < cant_figuras; j++){
            if(strcmp(lista_iter_ver_actual(iter), vector_figuras[j]->nombre) == 0){
                for(size_t k = 0; k < vector_figuras[j]->cant_polilineas; k++){
                    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0xFF);
                    for(int z = 0; z < vector_figuras[j]->polilineas[k]->n - 1; z++)
                        SDL_RenderDrawLine(
                        renderer,
                        vector_figuras[j]->polilineas[k]->puntos[z][0] * f + VENTANA_ANCHO / 2,
                        -vector_figuras[j]->polilineas[k]->puntos[z][1] * f + VENTANA_ALTO / 2,
                        vector_figuras[j]->polilineas[k]->puntos[z+1][0] * f + VENTANA_ANCHO / 2,
                        -vector_figuras[j]->polilineas[k]->puntos[z+1][1] * f + VENTANA_ALTO / 2
                        );
                }
            }  
        } 
        i++;  
        lista_iter_avanzar(iter);   
    }
//---------------------------------------------------------------
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
    return 0;
}

