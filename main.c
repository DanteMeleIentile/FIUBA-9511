#include <SDL2/SDL.h>
#include <stdbool.h>

#include "polilinea.h"
#include "lista.h"
#include "figura.h"
#include "lectura.h"
#include "fisicas.h"
#include "config.h"

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
    
    //QUEDAN FIJAS:

    float escala_planeta = 1;
    float escala_nave = 1;
    size_t nivel_actual = 0;

    figura_t *base = encontrar_figura("BASE", vector_figuras, cant_figuras);

    figura_t *planeta1 = encontrar_figura("PLANETA1", vector_figuras, cant_figuras);
    figura_t *planeta2 = encontrar_figura("PLANETA2", vector_figuras, cant_figuras);
    figura_t *planeta3 = encontrar_figura("PLANETA3", vector_figuras, cant_figuras);
    figura_t *planeta4 = encontrar_figura("PLANETA4", vector_figuras, cant_figuras);
    figura_t *planeta5 = encontrar_figura("PLANETA5", vector_figuras, cant_figuras);

    figura_t *estrella = encontrar_figura("ESTRELLA", vector_figuras, cant_figuras);

    figura_t *nave = encontrar_figura("NAVE", vector_figuras, cant_figuras);
    figura_t *nave_mas_chorro = encontrar_figura("NAVE+CHORRO", vector_figuras, cant_figuras);
    //figura_t *disparo = encontrar_figura("DISPARO", vector_figuras, cant_figuras);  

    //figura_t *combustible = encontrar_figura("COMBUSTIBLE", vector_figuras, cant_figuras);
    
    //figura_t *torreta = encontrar_figura("TORRETA", vector_figuras, cant_figuras);
    //figura_t *torreta_mas_disparo = encontrar_figura("TORRETA+DISPARO", vector_figuras, cant_figuras);

    //figura_t *reactor = encontrar_figura("REACTOR", vector_figuras, cant_figuras);
    //figura_t *nivel1 = encontrar_figura("NIVEL1NE", vector_figuras, cant_figuras);
    //figura_t *nivel2 = encontrar_figura("NIVEL1SE", vector_figuras, cant_figuras);
    //figura_t *nivel3 = encontrar_figura("NIVEL1SW", vector_figuras, cant_figuras);
    //figura_t *nivel4 = encontrar_figura("NIVEL1NW", vector_figuras, cant_figuras);
    //figura_t *nivel5 = encontrar_figura("NIVEL1R", vector_figuras, cant_figuras);

    //figura_t *escudo = encontrar_figura("ESCUDO", vector_figuras, cant_figuras);
    //figura_t *escudo2 = encontrar_figura("ESCUDO2", vector_figuras, cant_figuras);

    //figura_t *enemigo1 = encontrar_figura("ENEMIGO1", vector_figuras, cant_figuras);
    //figura_t *enemigo2 = encontrar_figura("ENEMIGO2", vector_figuras, cant_figuras);
    //figura_t *enemigo3 = encontrar_figura("ENEMIGO3", vector_figuras, cant_figuras);



//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//CREACIÓN DE "LISTA ACTIVA"
    //lista_t *lista_activa = lista_crear();
//----------------------------------------------------------------------------------------------------------------------
    
    
    // Mi nave:
/*
    float nave[][2] = {{8, 0}, {-1, 6}, {-4, 4}, {-4, 2}, {-2, 0}, {-4, -2}, {-4, -4}, {-1, -6}, {8, 0}};
    size_t nave_tam = 9;

    // El chorro de la nave:
    float chorro[][2] = {{-4, 2}, {-8, 0}, {-4, -2}};
    size_t chorro_tam = 3;
*/
    double rotacion_nave = 0;
    double velocidad_nave = 0;
    double angulo_velocidad = 0;
    double pos_x = POS_BASE_X;
    double pos_y = POS_BASE_Y;

    bool chorro_prendido = false;
    bool rotacion_derecha = false;
    bool rotacion_izquierda = false;
    

    // Queremos que todo se dibuje escalado por f:
    float f = 1;
    
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
                    case SDLK_RIGHT:
                        // Rota hacia la derecha:
                        rotacion_derecha = true;
                        break;
                    case SDLK_LEFT:
                        // Rota hacia la izquierda:
                        rotacion_izquierda = true;
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
                        // Deja de rotar hacia la derecha:
                        rotacion_derecha = false;
                        break;
                    case SDLK_LEFT:
                        // Deja de rotar hacia la izquierda:
                        rotacion_izquierda = false;
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

        figura_t *base_2 = rototrasladar_figura(base, 388, 218, 0, escala_planeta, 0, 0);
        imprimir_figura(base_2, renderer); //ojo! se modifica la polilinea clonada, luego de trasladar "base_2" nunca va a ser como antes

        figura_t *estrella_2 = rototrasladar_figura(estrella, 457, 364, 0, escala_planeta, 0, 0);
        imprimir_figura(estrella_2, renderer); 

        figura_t *planeta1_2 = rototrasladar_figura(planeta1, 663, 473, 0, escala_planeta, 0, 0);
        imprimir_figura(planeta1_2, renderer);

        figura_t *planeta2_2 = rototrasladar_figura(planeta2, 671, 145, 0, escala_planeta, 0, 0);
        imprimir_figura(planeta2_2, renderer);

        figura_t *planeta3_2 = rototrasladar_figura(planeta3, 110, 79, 0, escala_planeta, 0, 0);
        imprimir_figura(planeta3_2, renderer);

        figura_t *planeta4_2 = rototrasladar_figura(planeta4, 204, 455, 0, escala_planeta, 0, 0);
        imprimir_figura(planeta4_2, renderer);

        figura_t *planeta5_2 = rototrasladar_figura(planeta5, 111, 307, 0, escala_planeta, 0, 0);
        imprimir_figura(planeta5_2, renderer);

        figura_t *nave_2 = rototrasladar_figura(nave, 388, 218, 0, escala_planeta, 0, 0);
        figura_t *nave_mas_chorro_2 = rototrasladar_figura(nave_mas_chorro, 388, 218, 0, escala_planeta, 0, 0);

        //if(nivel = 1)
/*
        figura_agregar_en_lista("BASE", lista_activa);
        figura_agregar_en_lista("ESTRELLA", lista_activa);
        figura_agregar_en_lista("PLANETA1", lista_activa);
        figura_agregar_en_lista("PLANETA2", lista_activa);
        figura_agregar_en_lista("PLANETA3", lista_activa);
        figura_agregar_en_lista("PLANETA4", lista_activa);
        figura_agregar_en_lista("PLANETA5", lista_activa);
    
        lista_iter_t *iter = lista_iter_crear(lista_activa);

//IMPLEMENTAR FUNCION ROTOTRASLACION.

        
        for(size_t i = 0; i < lista_largo(lista_activa); i++){
            figura_t *fig = encontrar_figura("BASE", vector_figuras, cant_figuras);
            //ROTAR Y TRASLADAR FIGURA
                for(size_t k = 0; k < fig->cant_polilineas; k++){
                    rotar(fig->polilineas[k]->puntos, fig->polilineas[k]->n, 0);
                    trasladar(fig->polilineas[k]->puntos, fig->polilineas[k]->n, 388, 218);
                }
                imprimir_figura(fig, f, renderer);
                figura_destruir(fig);
            lista_iter_avanzar(iter);
        }

        lista_iter_destruir(iter);
*/
        // Dibujamos la nave escalada por f en el centro de la pantalla:        
        
       
        if(rotacion_izquierda) {
            rotar_figura(nave_2, NAVE_ROTACION_PASO);
            rotar_figura(nave_mas_chorro_2, NAVE_ROTACION_PASO);
            rotacion_nave += NAVE_ROTACION_PASO;
        }

        if(rotacion_derecha) {
            rotar_figura(nave_2, -NAVE_ROTACION_PASO);
            rotar_figura(nave_mas_chorro_2, -NAVE_ROTACION_PASO);
            rotacion_nave -= NAVE_ROTACION_PASO;
        }

        trasladar_figura(nave_2, pos_x, pos_y);
        trasladar_figura(nave_mas_chorro_2, pos_x, pos_y);

        if(chorro_prendido) {
            /*computar_velocidad(&velocidad_nave, &angulo_velocidad, NAVE_ACELERACION, 1.0/JUEGO_FPS);
            movimiento(nave_mas_chorro_2, angulo_velocidad, velocidad_nave);*/
            imprimir_figura(nave_mas_chorro_2, renderer);
        }else{
            //movimiento(nave_2, angulo_velocidad, velocidad_nave);
            imprimir_figura(nave_2, renderer);
        }
        
        figura_destruir(nave_2);
        figura_destruir(nave_mas_chorro_2);

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

