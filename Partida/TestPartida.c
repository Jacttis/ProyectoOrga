//
// Created by julia on 10/28/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include "ia.h"
#include "partida.h"
int printTablero(int grilla[][3],int filas);
int VerGanador(tPartida p,int llenoo);
int main(){
    tPartida nueva;
    int x,y;
    int HayGanador=0;
    nueva_partida(&nueva,103,PART_JUGADOR_RANDOM,"julian","axel");
    while(!HayGanador){
        scanf("%d",&x);
        scanf("%d",&y);
        nuevo_movimiento(nueva,x,y);
        int lleno=printTablero(nueva->tablero->grilla,3);
        int Ganador= VerGanador(nueva,lleno);
        if(Ganador==PART_GANA_JUGADOR_1 || Ganador==PART_GANA_JUGADOR_2 || Ganador==PART_EMPATE ){
            HayGanador=1;
        }
    }




    return 0;
}
int printTablero(int grilla[][3],int filas) {
    int lleno=1;
    printf("\n");   //MEJORAARRrrrr???
    for (int  i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grilla[i][j] == PART_SIN_MOVIMIENTO){
                printf("  -");
                lleno=0;
            }
            else {
                if (grilla[i][j] == PART_JUGADOR_1){
                    printf("  X");
                }
                else{

                    if (grilla[i][j] == PART_JUGADOR_2){
                        printf("  O");
                    }
                }
            }
        }
        if (i != 2)
            printf("\n");
        else
            printf("\n\n");
    }
    return lleno;
}
int gana(tPartida partida,int jugador) {
    int gana = 0;
    if ((partida->tablero->grilla[0][0] == jugador && partida->tablero->grilla[1][1] == jugador && partida->tablero->grilla[2][2] == jugador) ||
        (partida->tablero->grilla[2][0] == jugador && partida->tablero->grilla[1][1] == jugador && partida->tablero->grilla[0][2] == jugador)) {
        gana = 1;
    }
    else {
        for(int i=0;i<2;i++){
            if((partida->tablero->grilla[i][i]==jugador && partida->tablero->grilla[i][i+1]==jugador && partida->tablero->grilla[i][i+2]==jugador) ||
               (partida->tablero->grilla[i][i]==jugador && partida->tablero->grilla[i+1][i]==jugador && partida->tablero->grilla[i+2][i]==jugador) ){
                gana=1;
                break;
            }
        }
    }

    return gana;
}
int VerGanador(tPartida p,int llenoo){
    int turno=p->turno_de==PART_JUGADOR_1?PART_JUGADOR_2:PART_JUGADOR_1;
    if(gana(p,turno)){
        int gana = p->turno_de == PART_JUGADOR_1? PART_GANA_JUGADOR_2: PART_GANA_JUGADOR_1;
        if(gana==PART_GANA_JUGADOR_1) {
            printf("Gana Jugador 1");
        }
        else{
            printf("Gana Jugador 2");
        }
        return gana;
    }
    else{
        if(llenoo){
            printf("Empate");
            return PART_EMPATE;
        }
    }
    return PART_EN_JUEGO;
}
