//
// Created by julia on 10/28/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include "ia.h"
#include "partida.h"
int main(){
    tPartida nueva;
    int x,y;
    nueva_partida(&nueva,103,PART_JUGADOR_RANDOM,"julian","axel");
    scanf("%d",&x);
    scanf("%d",&y);
    while(nuevo_movimiento(nueva,x,y)!=PART_GANA_JUGADOR_2){
        scanf("%d",&x);
        scanf("%d",&y);
    }




    return 0;
}
