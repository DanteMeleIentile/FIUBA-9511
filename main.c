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
#include "torreta.h"


#define TIEMPO_MAX_DISPAROS 2
#define VEL_DISPARO 150

#define DT 1.f/JUEGO_FPS
#define COOLDOWN_NAVE 0.5
#define COOLDOWN_TORRETA 2

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

    //Leemos figuras de cada nivel y definimos varibales de impresión:


    figura_t *nivel4_leido = encontrar_figura("NIVEL1NW", vector_figuras, cant_figuras);

    figura_t *nivel5_leido = encontrar_figura("NIVEL1R", vector_figuras, cant_figuras);

    float ancho_nivel_x = 0;
    float alto_nivel_y = 0;

    float margen_nivel_x = 0;
    float margen_nivel_y = 0;



    figura_t *torreta_leida = encontrar_figura("TORRETA", vector_figuras, cant_figuras);
    figura_t *torreta_disparando_leida = encontrar_figura("TORRETA+DISPARO", vector_figuras, cant_figuras);




/*    nivel_t *nivel1 = nivel_crear();
    nivel_t *nivel2 = nivel_crear();
    nivel_t *nivel3 = nivel_crear();
    nivel_t *nivel4 = nivel_crear();
    nivel_t *nivel5 = nivel_crear(); */

    //Creación de listase e iteradores para elementos repetidos.
    lista_t *lista_disparos = lista_crear();


    torreta_t *torreta1 = torreta_crear();
    torreta_t *torreta2 = torreta_crear();

    torreta_set_cooldown(torreta1, COOLDOWN_TORRETA);


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
    int vidas = 3;

    double f = 1;
    
    bool spawn = true;

    // END código del alumno
        float a = 1;

    unsigned int ticks = SDL_GetTicks();
    while(1) {
        if(vidas == 0) return 0;
        if(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                break;
            // BEGIN código del alumno
            if (event.type == SDL_KEYDOWN) {
                // Se apretó una tecla
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        a = a + 0.3;

                        avanzar = true;
                        chorro_prendido = true;
                        break;

                    case SDLK_DOWN:
                        a = a -  0.3;

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
                        f++;
                        break;

                    case SDLK_s:
                        f--;
                        break;

                    case SDLK_a:
                        nivel = 4;
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


        nave_act_figura(nave, nave_leida, nave_mas_chorro_leida);

        if(nivel == 0){
            if(spawn){
                nave_setear_posicion(nave, planeta_get_pos_x(base), planeta_get_pos_y(base));

                torreta_setear_en_lugar(torreta1, 200, 200, 0);
                torreta_setear_en_lugar(torreta2, 400, 400, 0);
                spawn = false;
            }

            if(torreta_get_cooldown(torreta1) <= 0 && torreta_apuntar(torreta1, nave_get_pos_x(nave), nave_get_pos_y(nave))){
                double a = (VEL_DISPARO * cos(torreta_get_angulo_apuntado(torreta1)));
                double b = (VEL_DISPARO * sin(torreta_get_angulo_apuntado(torreta1)));
                lista_insertar_ultimo(lista_disparos, disparo_crear(torreta_get_pos_x(torreta1), torreta_get_pos_y(torreta1), a, b, torreta_get_angulo_apuntado(torreta1), true));
                torreta_set_cooldown(torreta1, COOLDOWN_TORRETA);
            }

            torreta_act_figura(torreta1, torreta_leida, torreta_disparando_leida);
            torreta_act_figura(torreta2, torreta_leida, torreta_disparando_leida);

            torreta_restar_cooldown(torreta1, DT);
            torreta_imprimir(renderer, torreta1, f, false);
            torreta_imprimir(renderer, torreta2, f, true);



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

            if(distancia_a_planeta(estrella, nave_get_pos_x(nave), nave_get_pos_y(nave)) < 20) printf("AUCH\n");
            if(distancia_a_planeta(planeta1, nave_get_pos_x(nave), nave_get_pos_y(nave)) < 20) printf("PLANETA1\n");
            if(distancia_a_planeta(planeta2, nave_get_pos_x(nave), nave_get_pos_y(nave)) < 20) printf("PLANETA2\n");
            if(distancia_a_planeta(planeta3, nave_get_pos_x(nave), nave_get_pos_y(nave)) < 20) printf("PLANETA3\n");

            if(distancia_a_planeta(planeta4, nave_get_pos_x(nave), nave_get_pos_y(nave)) < 20){
                printf("PLANETA4\n");
                nivel = 4;
            }
            
            if(distancia_a_planeta(planeta5, nave_get_pos_x(nave), nave_get_pos_y(nave)) < 20){
                printf("PLANETA5\n");
                nivel = 5;
            }
        }


        
        float escala_nivel;


        if(nivel == 4){
            nivel_t *nivel_4 = nivel_crear(nivel4_leido, 1, 1);

            ancho_nivel_x = nivel_get_extremo_x(nivel_4, true);
            margen_nivel_x = nivel_get_extremo_x(nivel_4, false);

            alto_nivel_y = nivel_get_extremo_y(nivel_4, true);
            margen_nivel_y = nivel_get_extremo_y(nivel_4, false);

            escala_nivel = VENTANA_ALTO * 1.0 / alto_nivel_y;
            
            if(VENTANA_ANCHO * 1.0 / (ancho_nivel_x + margen_nivel_x) < escala_nivel)
                escala_nivel = VENTANA_ANCHO * 1.0 / (ancho_nivel_x + margen_nivel_x);
            
            nivel_imprimir(renderer, nivel_4, escala_nivel, 0, margen_nivel_y * escala_nivel);

            nave_acercar(nave, -G, 0, VENTANA_ALTO, 1.f/JUEGO_FPS);
        }


        if(nivel == 5){
            nivel_t *nivel_5 = nivel_crear(nivel5_leido, 1, 1);

            ancho_nivel_x = nivel_get_extremo_x(nivel_5, true);
            margen_nivel_x = nivel_get_extremo_x(nivel_5, false);

            alto_nivel_y = nivel_get_extremo_y(nivel_5, true);
            margen_nivel_y = nivel_get_extremo_y(nivel_5, false);


            escala_nivel = VENTANA_ALTO * 1.0 / alto_nivel_y;
            
            if(VENTANA_ANCHO * 1.0 / (ancho_nivel_x + margen_nivel_x) < escala_nivel)
                escala_nivel = VENTANA_ANCHO * 1.0 / (ancho_nivel_x + margen_nivel_x);

            nivel_imprimir(renderer, nivel_5, escala_nivel, 0, 0);

            nave_acercar(nave, -G, 0, VENTANA_ALTO, 1.f/JUEGO_FPS);
        }

        if(rotacion_antihoraria){
            nave_rotar(nave, + NAVE_ROTACION_PASO);
        } 

        if(rotacion_horaria){
            nave_rotar(nave, - NAVE_ROTACION_PASO);
        } 

        if(avanzar){
            nave_avanzar(nave, NAVE_ACELERACION, DT);
        }else{
            nave_avanzar(nave, 0, DT);
        }

        if(chorro_prendido){
            nave_imprimir(renderer, nave, f, true);
        }
            nave_imprimir(renderer, nave, f, false);
        
        
        if(disparo && listo_para_disparar){
            double c = (VEL_DISPARO * cos(nave_get_angulo(nave)));
            double d = VEL_DISPARO * sin(nave_get_angulo(nave));
            lista_insertar_ultimo(lista_disparos, disparo_crear(nave_get_pos_x(nave), nave_get_pos_y(nave), c, d, nave_get_angulo(nave), false));
            listo_para_disparar = false;
        }
        tiempo_para_disparar += DT;

        if(tiempo_para_disparar >= COOLDOWN_NAVE){
            tiempo_para_disparar = 0;
            listo_para_disparar = true;
        }

        //Creamos iterar para lista disparos
        lista_iter_t *iter_disparos = lista_iter_crear(lista_disparos);        

        for(size_t i = 0; i < lista_largo(lista_disparos); i++){
            disparo_t *disp_act = lista_iter_ver_actual(iter_disparos);
            disparo_aumentar_tiempo(disp_act, DT);
            
            if(disparo_get_tiempo(disp_act) > TIEMPO_MAX_DISPAROS){
                disparo_destruir(disp_act);
                lista_iter_borrar(iter_disparos);
                continue;
            }

            if(!disparo_act_figura(disp_act, disparo_leido)){
                fprintf(stderr, "Error en memoria\n");
                return 1;
            }
            disparo_avanzar(disp_act, DT);
            
/*             if(disparo_can_kill(disp_act) && (distancia_a_disparo(disp_act, nave_get_pos_x(nave), nave_get_pos_y(nave) < 5))){
                vidas++;
                printf("VIDAS RESTANTES: %d\n", vidas);

            }else{
            } */

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

