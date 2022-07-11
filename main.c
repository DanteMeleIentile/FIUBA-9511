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

//SI DISPARO_LEIDO SE VUELVE FALSE, HUBO UN ERROR EN LA MEMORIA
void main_disparo_en_pantalla(SDL_Renderer *renderer, lista_t *lista_disparos, figura_t *disparo_leido, double escala){
    lista_iter_t *iter = lista_iter_crear(lista_disparos);

    for(size_t i = 0; i < lista_largo(lista_disparos); i++){
        disparo_t *disp_act = lista_iter_ver_actual(iter);
        disparo_aumentar_tiempo(disp_act, DT);
        
        if(disparo_get_tiempo(disp_act) > TIEMPO_MAX_DISPAROS){
            disparo_destruir(disp_act);
            lista_iter_borrar(iter);
            continue;
        }

        if(!disparo_act_figura(disp_act, disparo_leido)){
            fprintf(stderr, "Error en memoria\n");
            disparo_leido = NULL;
        }

        disparo_avanzar(disp_act, DT);
        
            disparo_imprimir(renderer, disp_act, escala);
            lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
}

bool main_disparo_pego(lista_t *lista_disparos, figura_t *figura, double dmin, bool friendly){
    lista_iter_t *iter = lista_iter_crear(lista_disparos);
    for(size_t i = 0; i < lista_largo(lista_disparos); i++){
        disparo_t *disp_act = lista_iter_ver_actual(iter);
        if((disparo_friendly(disp_act) && !friendly) || (!disparo_friendly(disp_act) && friendly)){
            if(distancia_punto_a_figura(figura, disparo_get_pos_x(disp_act), disparo_get_pos_y(disp_act)) <= dmin){
                disparo_destruir(disp_act);
                lista_iter_borrar(iter);
                lista_iter_destruir(iter);
                return true;
            }
        }
        
        lista_iter_avanzar(iter);
    }

    lista_iter_destruir(iter);
    return false;
}

void lista_iterar_torretas(SDL_Renderer *renderer, lista_t *lista_torreta, lista_t *lista_disparos, double movil_x, double movil_y, double escala, figura_t *torreta_leida, figura_t *torreta_disparo_leida){
    lista_iter_t *iter = lista_iter_crear(lista_torreta);
    for(size_t i = 0; i < lista_largo(lista_torreta); i++){
        torreta_t *torreta_act = lista_iter_ver_actual(iter);

        if(main_disparo_pego(lista_disparos, torreta_get_figura_principal(torreta_act), 5, false)){
            torreta_destruir(torreta_act);
            lista_iter_borrar(iter);
            continue;
        } 
        if(torreta_get_cooldown(torreta_act) <= 0 && torreta_apuntar(torreta_act, movil_x, movil_y)){
            double a = (VEL_DISPARO * cos(torreta_get_angulo_apuntado(torreta_act)));
            double b = (VEL_DISPARO * sin(torreta_get_angulo_apuntado(torreta_act)));
            lista_insertar_ultimo(lista_disparos, disparo_crear(torreta_get_pos_x(torreta_act)+10*cos(torreta_get_angulo(torreta_act)), torreta_get_pos_y(torreta_act)+10*sin(torreta_get_angulo(torreta_act)), a, b, torreta_get_angulo_apuntado(torreta_act), false));
            torreta_set_cooldown(torreta_act, COOLDOWN_TORRETA);
        }
        torreta_act_figura(torreta_act, torreta_leida, torreta_disparo_leida);
        torreta_restar_cooldown(torreta_act, DT);
        torreta_imprimir(renderer, torreta_act, escala, false);
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
}

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

    planeta_t base = planeta_crear(encontrar_figura("BASE", vector_figuras, cant_figuras), 388, 218);
    planeta_t estrella = planeta_crear(encontrar_figura("ESTRELLA", vector_figuras, cant_figuras), 457, 364);
    planeta_t planeta1 = planeta_crear(encontrar_figura("PLANETA1", vector_figuras, cant_figuras), 663, 473);
    planeta_t planeta2 = planeta_crear(encontrar_figura("PLANETA2", vector_figuras, cant_figuras), 671, 145);
    planeta_t planeta3 = planeta_crear(encontrar_figura("PLANETA3", vector_figuras, cant_figuras), 110, 79);
    planeta_t planeta4 = planeta_crear(encontrar_figura("PLANETA4", vector_figuras, cant_figuras), 204, 455);
    planeta_t planeta5 = planeta_crear(encontrar_figura("PLANETA5", vector_figuras, cant_figuras), 111, 307);

    //Creamos referencias a las figuras del vector_figuras para no buscarlas nuevamente por cada dt
    
    nave_t *nave = nave_crear();
    if(nave == NULL){
        fprintf(stderr, "Error de memoria");
        return 1;
    }
    
    figura_t *nave_leida = encontrar_figura("NAVE", vector_figuras, cant_figuras);
    if(nave_leida == NULL){
        fprintf(stderr, "Error en la memoria");
        return 1;
    }

    figura_t *nave_mas_chorro_leida = encontrar_figura("NAVE+CHORRO", vector_figuras, cant_figuras);
    if(nave_mas_chorro_leida == NULL){
        fprintf(stderr, "Error en la memoria");
        return 1;
    }

    figura_t *escudo_leido = encontrar_figura("ESCUDO", vector_figuras, cant_figuras);
    if(escudo_leido == NULL){
        fprintf(stderr, "Error en la memoria");
        return 1;
    }

    figura_t *escudo2_leido = encontrar_figura("ESCUDO2", vector_figuras, cant_figuras);
    if(escudo2_leido == NULL){
        fprintf(stderr, "Error en la memoria");
        return 1;
    }

    figura_t *disparo_leido = encontrar_figura("DISPARO", vector_figuras, cant_figuras);
    if(disparo_leido == NULL){
        fprintf(stderr, "Error en la memoria");
        return 1;
    }

    figura_t *nivel1_leido = encontrar_figura("NIVEL1NE", vector_figuras, cant_figuras);
    if(nivel1_leido == NULL){
        fprintf(stderr, "Error en la memoria");
        return 1;
    }

    figura_t *nivel4_leido = encontrar_figura("NIVEL1NW", vector_figuras, cant_figuras);
    if(nivel4_leido == NULL){
        fprintf(stderr, "Error en la memoria");
        return 1;
    }

    figura_t *nivel5_leido = encontrar_figura("NIVEL1R", vector_figuras, cant_figuras);
    if(nivel5_leido == NULL){
        fprintf(stderr, "Error en la memoria");
        return 1;
    }

    figura_t *torreta_leida = encontrar_figura("TORRETA", vector_figuras, cant_figuras);
    if(torreta_leida == NULL){
        fprintf(stderr, "Error en la memoria");
        return 1;
    }

    figura_t *torreta_disparando_leida = encontrar_figura("TORRETA+DISPARO", vector_figuras, cant_figuras);
    if(torreta_disparando_leida == NULL){
        fprintf(stderr, "Error en la memoria");
        return 1;
    }


/*     nivel_t *nivel1 = nivel_crear();
    nivel_t *nivel2 = nivel_crear();
    nivel_t *nivel3 = nivel_crear();
    nivel_t *nivel4 = nivel_crear();
    nivel_t *nivel5 = nivel_crear(); */

    //Creación de listase e iteradores para elementos repetidos.
    lista_t *lista_disparos = lista_crear();


    //lista_t *lista_combustibles_4 = lista_crear();

    lista_t *lista_torretas_4 = lista_crear();

    lista_insertar_ultimo(lista_torretas_4, torreta_crear(COOLDOWN_TORRETA, 0.62 * 257, 0.62 * (440 + 56), 0.66));
    lista_insertar_ultimo(lista_torretas_4, torreta_crear(COOLDOWN_TORRETA, 0.62 * 719, 0.62 * (674 + 56), 2.23));
    lista_insertar_ultimo(lista_torretas_4, torreta_crear(COOLDOWN_TORRETA, 0.62 * 985, 0.62 * (565 + 56), 0));
    lista_insertar_ultimo(lista_torretas_4, torreta_crear(COOLDOWN_TORRETA, 0.62 * 1125, 0.62 * (417 + 56), 3.8));
    lista_insertar_ultimo(lista_torretas_4, torreta_crear(COOLDOWN_TORRETA, 0.62 * 862, 0.62 * (163 + 56), 3.8));
    lista_insertar_ultimo(lista_torretas_4, torreta_crear(COOLDOWN_TORRETA, 0.62 * 626, 0.62 * (323 + 56), 2.23));
    lista_insertar_ultimo(lista_torretas_4, torreta_crear(COOLDOWN_TORRETA, 0.62 * 505, 0.62 * (331 + 56), 3.8));
    lista_insertar_ultimo(lista_torretas_4, torreta_crear(COOLDOWN_TORRETA, 0.62 * 378, 0.62 * (296 + 56), 2.23));

    //lista_t *lista_torretas_5 = lista_crear();





//----------------------------------------------------------------------------------------------------------------------
    //Boleeanos de estado
    bool chorro_prendido = false;
    bool escudo_prendido = false;

    bool disparo = false;
    double tiempo_para_disparar = 0;
    bool listo_para_disparar = true;
    
    //Boleeanos de movimiento
    bool rotacion_horaria = false;
    bool rotacion_antihoraria = false;
    bool avanzar = false;

    size_t nivel = 0;
    int vidas = 20;

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
                        nave_setear_velocidad(nave, 0, 0);
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
                    
                    case SDLK_LALT:
                        escudo_prendido = true;
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
                    case SDLK_LALT:
                        escudo_prendido = false;
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
        
        float escala_no_infinito = VENTANA_ALTO * 1.0 / 596;
        if(VENTANA_ANCHO * 1.0 / (989 + 150) < escala_no_infinito)
            escala_no_infinito = VENTANA_ANCHO * 1.0 / (989 + 150);
        //float centro = (989 + 150)/2; 

        //printf("MIN X = %f\n", figura_get_extremo_x(nivel4_leido, false));
        //printf("MAX X = %f\n", figura_get_extremo_x(nivel4_leido, true));

        //printf("MIN Y = %f\n", figura_get_extremo_y(nivel4_leido, false));
        //printf("MAX Y = %f\n", figura_get_extremo_y(nivel4_leido, true));

        nave_act_figura(nave, nave_leida, nave_mas_chorro_leida, escudo_leido, escudo2_leido);
        nave_apagar(nave, true, true, true);

        if(nivel == 0){
            if(spawn){
                nave_setear_velocidad(nave, 0, 0);
                nave_setear_posicion(nave, planeta_get_pos_x(base), planeta_get_pos_y(base), 0);
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

            if(distancia_a_planeta(estrella, nave_get_pos_x(nave), nave_get_pos_y(nave)) < 25){
                nivel = 0;
                spawn = true;
            }

            if(distancia_a_planeta(planeta1, nave_get_pos_x(nave), nave_get_pos_y(nave)) < 25){
                spawn = true;
                printf("PLANETA1\n");
                //nivel = 1;
            }
            if(distancia_a_planeta(planeta2, nave_get_pos_x(nave), nave_get_pos_y(nave)) < 25){
                spawn = true;
                printf("PLANETA2\n");
                //nivel = 2;
            }
            if(distancia_a_planeta(planeta3, nave_get_pos_x(nave), nave_get_pos_y(nave)) < 25){
                spawn = true;
                printf("PLANETA3\n");
                //nivel = 3;
            }

            if(distancia_a_planeta(planeta4, nave_get_pos_x(nave), nave_get_pos_y(nave)) < 25){
                spawn = true;
                printf("PLANETA4\n");
                nivel = 4;
            }
            
            if(distancia_a_planeta(planeta5, nave_get_pos_x(nave), nave_get_pos_y(nave)) < 25){
                spawn = true;
                printf("PLANETA5\n");
                //nivel = 5;
            }
        }

        if(nivel == 3){
            nave_acercar_direccion(nave, G, PI / 2, 1.f/JUEGO_FPS);
        }

        if(nivel == 4){
            if(spawn == true){
                nave_setear_velocidad(nave, 0, 0);
                nave_setear_posicion(nave, VENTANA_ANCHO/2, 500, 0);
                spawn = false;
            }
            nivel_t *nivel_4 = nivel_crear(nivel4_leido, 1, 1);
            if(VENTANA_ANCHO * 1.0 / (989 + 150 + 150) < escala_no_infinito)
                escala_no_infinito = VENTANA_ANCHO * 1.0 / (989 + 150 + 150);
            //nivel_trasladar(nivel_4, -150 - 989/2 + VENTANA_ANCHO/2, -150);
            
            //nivel_trasladar(nivel_4, +150 * escala_no_infinito/2, 0);
            nivel_imprimir(renderer, nivel_4, escala_no_infinito);
            nave_acercar_direccion(nave, -G, PI / 2, 1.f/JUEGO_FPS);
            lista_iterar_torretas(renderer, lista_torretas_4, lista_disparos, nave_get_pos_x(nave), nave_get_pos_y(nave), escala_no_infinito, torreta_leida, torreta_disparando_leida);
            if(distancia_punto_a_figura(nivel_get_figura(nivel_4), nave_get_pos_x(nave), nave_get_pos_y(nave)) < 5){
                //vidas--;
                printf("VIDAS = %d\n", vidas);
                //spawn = true;
            }

            if(nave_get_pos_x(nave) < 0){
                nave_setear_posicion(nave, VENTANA_ANCHO, nave_get_pos_y(nave), nave_get_angulo(nave));
            }

            if(nave_get_pos_x(nave) > VENTANA_ANCHO){
                nave_setear_posicion(nave, 0, nave_get_pos_y(nave), nave_get_angulo(nave));
            }

            if(nave_get_pos_y(nave) < 0){
                nave_invertir_vel_y(nave);
            }

            if(nave_get_pos_y(nave) > VENTANA_ALTO * 1.25){
                nivel = 0;
                spawn = true;
            }

        }

        if(nivel == 5){
            nivel_t *nivel_5 = nivel_crear(nivel5_leido, 1, 1);
            nivel_imprimir(renderer, nivel_5, escala_no_infinito);
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
            nave_prender(nave, true, false, false);
        }

        if(escudo_prendido && (nivel != 0 && nivel != 5)){
            nave_prender(nave, false, false, true);
        } else if(escudo_prendido){
            nave_prender(nave, false, true, false);
        }

        nave_imprimir(renderer, nave, f);
        
        if(main_disparo_pego(lista_disparos, nave_get_figura_principal(nave), 5, true)){
            vidas--;
            printf("VIDAS = %d\n", vidas);
            spawn = true;
        }

        if(disparo && listo_para_disparar){
            double c = (VEL_DISPARO * cos(nave_get_angulo(nave)));
            double d = VEL_DISPARO * sin(nave_get_angulo(nave));
            lista_insertar_ultimo(lista_disparos, disparo_crear(nave_get_pos_x(nave), nave_get_pos_y(nave), c, d, nave_get_angulo(nave), true));
            listo_para_disparar = false;
        }
        tiempo_para_disparar += DT;

        if(tiempo_para_disparar >= COOLDOWN_NAVE){
            tiempo_para_disparar = 0;
            listo_para_disparar = true;
        }

        main_disparo_en_pantalla(renderer, lista_disparos, disparo_leido, f);
        if(disparo_leido == NULL){
            fprintf(stderr, "Error en la memoria");
            return 1;
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
    return 0;
}

