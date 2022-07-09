#include <SDL2/SDL.h>
#include <stdbool.h>

#include "polilinea.h"
#include "lista.h"
#include "figura.h"
#include "lectura.h"
#include "fisicas.h"
#include "config.h"
#include "disparo.h"
#include "nave.h"
#include "planeta.h"
#include "nivel.h"

#define X 0
#define Y 1

#define TIEMPO_MAX_DISPAROS 2
#define VEL_DISPARO 150

#define COOLDOWN 0.5

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

    //Creación de entidades

    nave_t *nave = nave_crear();

    planeta_t base = planeta_crear(encontrar_figura("BASE", vector_figuras, cant_figuras), 388, 218);
    planeta_t estrella = planeta_crear(encontrar_figura("ESTRELLA", vector_figuras, cant_figuras), 457, 364);
    planeta_t planeta1 = planeta_crear(encontrar_figura("PLANETA1", vector_figuras, cant_figuras), 663, 473);
    planeta_t planeta2 = planeta_crear(encontrar_figura("PLANETA2", vector_figuras, cant_figuras), 671, 145);
    planeta_t planeta3 = planeta_crear(encontrar_figura("PLANETA3", vector_figuras, cant_figuras), 110, 79);
    planeta_t planeta4 = planeta_crear(encontrar_figura("PLANETA4", vector_figuras, cant_figuras), 204, 455);
    planeta_t planeta5 = planeta_crear(encontrar_figura("PLANETA5", vector_figuras, cant_figuras), 111, 307);

    //Creamos referencias a las figuras del vector_figuras para no buscarlas nuevamente por cada dt
    
    figura_t *nave_leida = encontrar_figura("NAVE", vector_figuras, cant_figuras);
    figura_t *nave_mas_chorro_leida = encontrar_figura("NAVE+CHORRO", vector_figuras, cant_figuras);

    figura_t *disparo_leido = encontrar_figura("DISPARO", vector_figuras, cant_figuras);

    figura_t *nivel1_leido = encontrar_figura("NIVEL1NE", vector_figuras, cant_figuras);

    figura_t *nivel4_leido = encontrar_figura("NIVEL1NW", vector_figuras, cant_figuras);




    //Creación de listase e iteradores para elementos repetidos.
    lista_t *lista_disparos = lista_crear();


//----------------------------------------------------------------------------------------------------------------------
    //Boleeanos de estado
    bool chorro_prendido = false;
    bool disparo = false;
    double tiempo_para_disparar = 0;
    bool listo_para_disparar = true;
    
    //Boleeanos de movimiento
    bool rotacion_horaria = false;
    bool rotacion_antihoraria = false;
    bool avanzar = false;

    size_t nivel = 0;

    double f = 1;
    
    bool spawn = true;

    // END código del alumno
        float a = 1;

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
                        avanzar = true;
                        chorro_prendido = true;
                        break;

                    case SDLK_DOWN:
                        break;
                        

                    case SDLK_RIGHT:
                        rotacion_horaria = true;
                        break;

                    case SDLK_LEFT:
                        rotacion_antihoraria = true;
                        break;

                    case SDLK_SPACE:
                        disparo = true;
                        break;

                    case SDLK_w:
                        a = a + 0.1;
                        f++;
                        break;

                    case SDLK_s:
                        a = a - 0.1;
                        f--;
                        break;

                    case SDLK_a:
                        break;
                    
                    case SDLK_d:
                        break;
                    
                    case SDLK_ESCAPE:
                        return 0;
                }
            }
            else if (event.type == SDL_KEYUP) {
                // Se soltó una tecla
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        avanzar = false;
                        chorro_prendido = false;
                        break;
                    case SDLK_RIGHT:
                        rotacion_horaria = false;
                        break;
                    case SDLK_LEFT:
                        rotacion_antihoraria = false;
                        break;
                    case SDLK_SPACE:
                        disparo = false;
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
        
        nivel_t *nivel_4 = nivel_crear(nivel4_leido, 1, 1);
/*        
        escala = VENTANA_ALTO * 1.0 / planeta_alto;
        if(VENTANA_ANCHO * 1.0 / (planeta_ancho + planeta_x_min) < escala)
            escala = VENTANA_ANCHO * 1.0 / (planeta_ancho + planeta_x_min);
        centro = (planeta_ancho + planeta_x_min) / 2;*/

        float escala_no_infinito = VENTANA_ALTO * 1.0 / 596 + 150;
        if(VENTANA_ANCHO * 1.0 / (989 + 150) < escala_no_infinito)
            escala_no_infinito = VENTANA_ANCHO * 1.0 / (989 + 150);
        float centro = (989 + 150)/2; 

        printf("MIN X = %f\n", figura_get_extremo_x(nivel4_leido, false));
        printf("MAX X = %f\n", figura_get_extremo_x(nivel4_leido, true));

        printf("MIN Y = %f\n", figura_get_extremo_y(nivel4_leido, false));
        printf("MAX Y = %f\n", figura_get_extremo_y(nivel4_leido, true));

        printf("Posición en X = %f; Posición en Y = %f\n", nivel_get_pos_x(nivel_4), nivel_get_pos_y(nivel_4));

        //nivel_act_figura(nivel_4, nivel4_leido);
        
        printf("Posición en X = %f; Posición en Y = %f\n", nivel_get_pos_x(nivel_4), nivel_get_pos_y(nivel_4));


        //nivel_trasladar(nivel_4, 989/2 + 300/2, 596/2 + 300/2);
        
        //Creamos entidad nivel
        //centramos entidad nivel (con margen incluido)
        //trasladamos la entidad nivel
        //trasladamos la entidad nivel
        printf("ESCALA = %f\n", a);

        nivel_imprimir(renderer, nivel_4, a);


        nave_act_figura(nave, nave_leida, nave_mas_chorro_leida);
        
        if(nivel == 0){
            if(spawn){
                nave_setear_posicion(nave, planeta_get_pos_x(base), planeta_get_pos_y(base));
                spawn = false;
            }
            planeta_dibujar(renderer, base);
            planeta_dibujar(renderer, estrella);
            planeta_dibujar(renderer, planeta1);
            planeta_dibujar(renderer, planeta2);
            planeta_dibujar(renderer, planeta3);
            planeta_dibujar(renderer, planeta4);
            planeta_dibujar(renderer, planeta5);

            if(nave_get_pos_x(nave) < 0 || nave_get_pos_x(nave) > VENTANA_ANCHO){
                nave_invertir_vel_x(nave);
            }
            if(nave_get_pos_y(nave) < 0 || nave_get_pos_y(nave) > VENTANA_ALTO){
                nave_invertir_vel_y(nave);
            }

            nave_acercar(nave, G, planeta_get_pos_x(estrella), planeta_get_pos_y(estrella), 1.f/JUEGO_FPS);

            if(distancia_a_planeta(estrella, nave) < 20) printf("AUCH\n");
            if(distancia_a_planeta(planeta1, nave) < 20) printf("PLANETA1\n");
            if(distancia_a_planeta(planeta2, nave) < 20) printf("PLANETA2\n");
            if(distancia_a_planeta(planeta3, nave) < 20) printf("PLANETA3\n");
            if(distancia_a_planeta(planeta4, nave) < 20) printf("PLANETA4\n");
            if(distancia_a_planeta(planeta5, nave) < 20) printf("PLANETA5\n");
        }

        if(rotacion_antihoraria){
            nave_rotar(nave, + NAVE_ROTACION_PASO);
        } 

        if(rotacion_horaria){
            nave_rotar(nave, - NAVE_ROTACION_PASO);
        } 

        if(avanzar){
            nave_avanzar(nave, NAVE_ACELERACION, 1.f/JUEGO_FPS);
        }else{
            nave_avanzar(nave, 0, 1.f/JUEGO_FPS);
        }

        if(chorro_prendido){
            nave_imprimir(renderer, nave, f, true);
        }
            nave_imprimir(renderer, nave, f, false);
        
        
        if(disparo && listo_para_disparar){
            double a = (VEL_DISPARO * cos(nave_get_angulo(nave)));
            double b = VEL_DISPARO * sin(nave_get_angulo(nave));
            lista_insertar_ultimo(lista_disparos, disparo_crear(nave_get_pos_x(nave), nave_get_pos_y(nave), a, b, nave_get_angulo(nave)));
            listo_para_disparar = false;
        }
        tiempo_para_disparar += 1.f/JUEGO_FPS;

        if(tiempo_para_disparar >= COOLDOWN){
            tiempo_para_disparar = 0;
            listo_para_disparar = true;
        }

        //Creamos iterar para lista disparos
        lista_iter_t *iter_disparos = lista_iter_crear(lista_disparos);        


        for(size_t i = 0; i < lista_largo(lista_disparos); i++){
            disparo_t *disp_act = lista_iter_ver_actual(iter_disparos);
            disparo_aumentar_tiempo(disp_act, 1.f/JUEGO_FPS);
            
            if(disparo_get_tiempo(disp_act) > TIEMPO_MAX_DISPAROS){
                disparo_destruir(disp_act);
                lista_iter_borrar(iter_disparos);
                continue;
            }

            if(!disparo_act_figura(disp_act, disparo_leido)){
                fprintf(stderr, "Error en memoria\n");
                return 1;
            }
            disparo_avanzar(disp_act, 1.f/JUEGO_FPS);

            disparo_imprimir(renderer, disp_act, f);

            lista_iter_avanzar(iter_disparos);
        }

        //eliminamos iterar para lista disparos
        lista_iter_destruir(iter_disparos);


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

