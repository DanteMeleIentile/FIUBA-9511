#include <SDL2/SDL.h>
#include <stdbool.h>

#include "polilinea.h"
#include "lista.h"
#include "figura.h"
#include "lectura.h"
#include "fisicas.h"
#include "config.h"

#include "nave.h"
#include "planeta.h"

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

    size_t nivel = 0;

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
    
    planeta_t base = planeta_crear(encontrar_figura("BASE", vector_figuras, cant_figuras), 388, 218);
    planeta_t estrella = planeta_crear(encontrar_figura("ESTRELLA", vector_figuras, cant_figuras), 457, 364);
    planeta_t planeta1 = planeta_crear(encontrar_figura("PLANETA1", vector_figuras, cant_figuras), 663, 473);
    planeta_t planeta2 = planeta_crear(encontrar_figura("PLANETA2", vector_figuras, cant_figuras), 671, 145);
    planeta_t planeta3 = planeta_crear(encontrar_figura("PLANETA3", vector_figuras, cant_figuras), 110, 79);
    planeta_t planeta4 = planeta_crear(encontrar_figura("PLANETA4", vector_figuras, cant_figuras), 204, 455);
    planeta_t planeta5 = planeta_crear(encontrar_figura("PLANETA5", vector_figuras, cant_figuras), 111, 307);

    figura_t *nave_leida = encontrar_figura("NAVE", vector_figuras, cant_figuras);
    figura_t *nave_mas_chorro_leida = encontrar_figura("NAVE+CHORRO", vector_figuras, cant_figuras);
    
//----------------------------------------------------------------------------------------------------------------------
    
    bool chorro_prendido = false;
    
    //Boleeanos de rotación
    bool rotacion_horaria = false;
    bool rotacion_antihoraria = false;

    double mov_x = 0;
    double mov_y = 0;
    double f = 1;

    //Cración de entidades
    nave_t *nave = nave_crear();
     
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
                    case SDLK_ESCAPE:
                        return 0;
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
        
        nave_inicializar(nave, nave_leida, nave_mas_chorro_leida);

        if(rotacion_antihoraria){
            nave_rotar(nave, NAVE_ROTACION_PASO);
        } 

        if(rotacion_horaria){
            nave_rotar(nave, -NAVE_ROTACION_PASO);
        } 
      
        if(nivel == 0){
            //NECESITO SABER LAS COORDENADAS DE LOS PLANETAS PARA CALCULAR COLISIONES
            nave_spawn(nave, base.x, base.y);
            planeta_dibujar(renderer, base);
            planeta_dibujar(renderer, estrella);

            planeta_dibujar(renderer, planeta1);
            planeta_dibujar(renderer, planeta2);
            //if(distancia_a_planeta(planeta2, nave) < 2) nivel = 2;
            planeta_dibujar(renderer, planeta3);
            //if(distancia_a_planeta(planeta3, nave) < 2) nivel = 3;
            planeta_dibujar(renderer, planeta4);
            //if(distancia_a_planeta(planeta4, nave) < 2) nivel = 4;
            planeta_dibujar(renderer, planeta5);
            //if(distancia_a_planeta(planeta5, nave) < 2) nivel = 5;
        }
        /*
        if(nivel == 1){
            return 1;
        }
        if(nivel == 2){
            return 1;
        }
        if(nivel == 3){
            return 1;
        }
        if(nivel == 4){
            return 1;
        }
        if(nivel == 5){
            return 1;
        }
        */
        nave_trasladar(nave, mov_x, mov_y);

        if(chorro_prendido){
            nave_aceleracion(nave, NAVE_ACELERACION, 1/JUEGO_FPS);
            nave_impulso(nave);
            printf("X = %f , Y = %f\n", nave->x, nave->y);
            nave_imprimir(renderer, nave, 1, true);
        }else{
            nave_impulso(nave);

            printf("X = %f , Y = %f\n", nave->x, nave->y);
            nave_imprimir(renderer, nave, 1, false);
        }

        if(distancia_a_planeta(estrella, nave) < 15) printf("AUCH\n");
        if(distancia_a_planeta(planeta1, nave) < 15) nivel = 0;
        if(distancia_a_planeta(planeta2, nave) < 15) nivel = 0;
        if(distancia_a_planeta(planeta3, nave) < 15) nivel = 0;
        if(distancia_a_planeta(planeta4, nave) < 15) nivel = 0;
        if(distancia_a_planeta(planeta5, nave) < 15) nivel = 0;


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

