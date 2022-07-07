#include <SDL2/SDL.h>
#include <stdbool.h>

#include "polilinea.h"
#include "lista.h"
#include "figura.h"
#include "lectura.h"
#include "fisicas.h"
#include "config.h"
#include "nave.h"


#define X 0
#define Y 1

#define POS_BASE_X 388
#define POS_BASE_Y 218

figura_t *encontrar_figura(char *nombre, figura_t **vector_figuras, size_t n){ // Esta funcion como que ya está clonando
    figura_t *fig;
    for (size_t i = 0; i < n; i++){
        if(strcmp(nombre, vector_figuras[i]->nombre) == 0){
            fig = vector_figuras[i];
            break;
        }
    } 
    return fig;
}


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
        fclose(f1);
        return 1;
    }

    char nombre[20];
    bool infinito;
    figura_tipo_t tipo;
    size_t cant_polilineas;

    size_t cant = 0;

    for(size_t i = 0; leer_encabezado_figura(f1, nombre, &tipo, &infinito, &cant_polilineas); i++){
        if(i != 0){
            vector_figuras = realloc(vector_figuras, (i + 1) * sizeof(figura_t*)); //Agrega una componente a "vector_figuras" hasta que no pueda leer mas figuras
            if(vector_figuras == NULL){
                fclose(f1);
                return 1;
            }
        }
        vector_figuras[i] = figura_crear(nombre, tipo, infinito, cant_polilineas); //Iguala cada componente a la figura leida del archivo

        if(vector_figuras[i] == NULL){
            if(i >= 1){
                for(size_t m = 0; m < i; m++){
                    figura_destruir(vector_figuras[m]);
                }
                fclose(f1);
                return 1;
            }
        }

        polilinea_t **vector_polilineas = malloc(sizeof(polilinea_t*) * cant_polilineas); //Creamos un puntero que apunta a un vector "vector_polilineas" de "cant_polilineas"z polilinea_t

        if(vector_polilineas == NULL){
            fprintf(stderr, "Error de memoria");
            free(vector_figuras);
            fclose(f1);
            return 1;
        }

        for(size_t j = 0; j < cant_polilineas; j++){
            vector_polilineas[j] = leer_polilinea(f1); //Iguala cada componente de las polilineas de cada figura leida del archivo
            if(vector_polilineas[j] == NULL){
                if(j >= 1){
                    for(size_t l = 0; l < j; l++){
                        polilinea_destruir(vector_polilineas[l]);
                    }
                }
                free(vector_polilineas);
                free(vector_figuras);
                fclose(f1);
                return 1;
            }
        }

        if(!figura_setear_polilinea(vector_figuras[i], vector_polilineas)){
            fprintf(stderr, "ERROR");
            return 1; // ERROR 
        }

        cant++; //EVALUAR
    }

    const size_t cant_figuras = cant;

    fclose(f1);
    
    figura_t *base = encontrar_figura("BASE", vector_figuras, cant_figuras);

    figura_t *nave_leida = encontrar_figura("NAVE", vector_figuras, cant_figuras);

    figura_t *planeta1 = encontrar_figura("PLANETA1", vector_figuras, cant_figuras);

    figura_t *estrella = encontrar_figura("ESTRELLA", vector_figuras, cant_figuras);

//----------------------------------------------------------------------------------------------------------------------

    //El chorro de la nave:
    float chorro[][2] = {{-4, 2}, {-8, 0}, {-4, -2}};
    size_t chorro_tam = 3;

    //Creamos ejes de referencia
    float ejes_y[][2] = {{0, 10}, {0, -10}};
    float ejes_x[][2] = {{10, 0}, {-10, 0}};
    size_t ejes_tam = 2;


    bool chorro_prendido = false;
    bool rotacion_derecha = false;

    //Boleeanos de rotación
    bool rotacion_horaria = false;
    bool rotacion_antihoraria = false;

    //Cración de entidades
    nave_t *nave = nave_crear();


    // Queremos que todo se dibuje escalado por f:
    float f = 1;
    float mov_x = 0;
    float mov_y = 0;

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
                        f++;
                        // Prendemos el chorro:
                        chorro_prendido = true;
                        break;

                    case SDLK_DOWN:
                        // Disminuimos el valor de la escala
                        break;
                        
                    case SDLK_RIGHT:
                        rotacion_horaria = true;
                        break;

                    case SDLK_LEFT:
                        rotacion_antihoraria = true;
                        break;

                    case SDLK_w:
                        mov_y += 20;
                        break;
                    case SDLK_s:
                        mov_y -= 20;
                        break;

                    case SDLK_a:
                        mov_x -= 20;
                        break;
                    case SDLK_d:
                        mov_x += 20;
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
                    case SDLK_RIGHT:
                        rotacion_horaria = false;
                        break;
                    case SDLK_LEFT:
                        rotacion_antihoraria = false;
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
        

        nave_inicializar(nave, nave_leida);

        if(rotacion_horaria){
            nave_rotar(nave, - NAVE_ROTACION_PASO);
        }

        if(rotacion_antihoraria){
            nave_rotar(nave, + NAVE_ROTACION_PASO);
        }

        figura_trasladar (nave->figura, mov_x, mov_y);
        for(size_t k = 0; k < nave->figura->cant_polilineas; k++){
            SDL_SetRenderDrawColor(renderer, nave->figura->polilineas[k]->r, nave->figura->polilineas[k]->g, nave->figura->polilineas[k]->b, 0xFF);
            for(size_t z = 0; z < nave->figura->polilineas[k]->n - 1; z++){
                SDL_RenderDrawLine(
                renderer,
                (nave->figura->polilineas[k]->puntos[z][X] * f) + VENTANA_ANCHO / 2 ,
                -nave->figura->polilineas[k]->puntos[z][Y] * f + VENTANA_ALTO / 2 ,
                (nave->figura->polilineas[k]->puntos[z+1][X] * f) + VENTANA_ANCHO / 2 ,
                -nave->figura->polilineas[k]->puntos[z+1][Y] * f + VENTANA_ALTO / 2 
                // Al sumar VENTANA_ALTO definimos el origen DE IMPRESIÓN abajo a la izquierda
                );

            }
        }

        //************* CREACION DE EJES DE REFENCIA*************************
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0x00);
        for(int i = 0; i < ejes_tam - 1; i++)
            SDL_RenderDrawLine(
                renderer,
                ejes_y[i][0] * f + VENTANA_ANCHO / 2,
                -ejes_y[i][1] * f + VENTANA_ALTO / 2,
                ejes_y[i+1][0] * f + VENTANA_ANCHO / 2,
                -ejes_y[i+1][1] * f + VENTANA_ALTO / 2
            );
        
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0x00);
        for(int i = 0; i < ejes_tam - 1; i++)
            SDL_RenderDrawLine(
                renderer,
                ejes_x[i][0] * f + VENTANA_ANCHO / 2,
                -ejes_x[i][1] * f + VENTANA_ALTO / 2,
                ejes_x[i+1][0] * f + VENTANA_ANCHO / 2,
                -ejes_x[i+1][1] * f + VENTANA_ALTO / 2
            );

        //************* CREACION DE EJES DE REFENCIA*************************

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

