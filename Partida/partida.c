//
// Created by julian on 10/26/2019.
//
#include "partida.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<time.h>
int gana(tPartida partida,int jugador);
/**
Inicializa una nueva partida, indicando:
 - Modo de partida (Usuario vs. Usuario o Usuario vs. Agente IA).
 - Jugador que comienza la partida (Jugador 1, Jugador 2, o elecci�n al azar).
 - Nombre que representa al Jugador 1.
 - Nombre que representa al Jugador 2.
**/
extern void nueva_partida(tPartida * p, int modo_partida, int comienza, char * j1_nombre, char * j2_nombre){
    (*p)=(tPartida)malloc(sizeof(struct partida));
    (*p)->tablero=(tTablero)malloc(sizeof(struct tablero));
    if(*p==NULL){
        exit(PART_ERROR_MEMORIA);
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            (*p)->tablero->grilla[i][j]=PART_SIN_MOVIMIENTO;
        }
    }
    (*p)->modo_partida=modo_partida;
    if(comienza==PART_JUGADOR_RANDOM){
        srand(time(NULL));
        int random=rand()%2;
        if(random==0){
            (*p)->turno_de=PART_JUGADOR_1;
            printf("Empieza Jugador 1");
        }
        else{
            (*p)->turno_de=PART_JUGADOR_2;
            printf("Empieza Jugador 2");
        }

    }
    else{
        (*p)->turno_de=comienza;
    }
    (*p)->estado=PART_EN_JUEGO;
    strcpy((*p)->nombre_jugador_1,j1_nombre);
    strcpy((*p)->nombre_jugador_2,j2_nombre);
}

/**
Actualiza, si corresponde, el estado de la partida considerando que el jugador al que le corresponde jugar, decide hacerlo en la posici�n indicada (X,Y).
En caso de que el movimiento a dicha posici�n sea posible, retorna PART_MOVIMIENTO_OK; en caso contrario, retorna PART_MOVIMIENTO_ERROR.
Las posiciones (X,Y) deben corresponderse al rango [0-2]; X representa el n�mero de fila, mientras Y el n�mero de columna.
**/
extern int nuevo_movimiento(tPartida p, int mov_x, int mov_y){
    if(mov_x>2 || mov_x<0 || mov_y>2 || mov_y<0){
        return PART_MOVIMIENTO_ERROR;
    }
    if (p->tablero->grilla[mov_x][mov_y] == PART_SIN_MOVIMIENTO) {
        p->tablero->grilla[mov_x][mov_y] = p->turno_de;

        p->turno_de = p->turno_de == PART_JUGADOR_1? PART_JUGADOR_2: PART_JUGADOR_1;
    }
    else{
        return PART_MOVIMIENTO_ERROR;
    }
    return PART_MOVIMIENTO_OK;
}

/**
Finaliza la partida referenciada por P, liberando toda la memoria utilizada.
**/
extern void finalizar_partida(tPartida * p){
    free((*p)->tablero);
    free(*p);
}



