#include <stdio.h>
#include <stdlib.h>
#include "partida.h"
#include <string.h>
#include <time.h>
#include "ia.h"

void checkearMovimiento(int *x, int *y, tPartida partida) {
    while (*x < 0 || *x > 2 ||*y < 0 || *y > 2 || partida->tablero->grilla[*x][*y] != PART_SIN_MOVIMIENTO) {
        fflush(stdin);
        printf("\n\nPosicion invalida\nInserte un valor valido...\n");

        printf("Inserte una fila: ");
        scanf("%d", x);

        printf("Inserte una columna: ");
        scanf("%d", y);
    }
}

int ganaaux(int grilla[3][3], int jugador_max) {
    int ganaMax = 0;

    if (grilla[0][0] == jugador_max) {
        ganaMax = grilla[0][1] == jugador_max && grilla[0][2] == jugador_max;

        if (!ganaMax)
            ganaMax = grilla[1][0] == jugador_max && grilla[2][0] == jugador_max;

        if (!ganaMax)
            ganaMax = grilla[1][1] == jugador_max && grilla[2][2] == jugador_max;
    }

    if (!ganaMax && grilla[1][1] == jugador_max) {
        ganaMax = grilla[0][1] == jugador_max && grilla[2][1] == jugador_max;

        if (!ganaMax)
            ganaMax = grilla[1][0] == jugador_max && grilla[1][2] == jugador_max;

        if (!ganaMax && grilla[2][0] == jugador_max)
            ganaMax = grilla[1][1] == jugador_max && grilla[0][2] == jugador_max;
    }
    if (!ganaMax && grilla[2][2] == jugador_max) {
        ganaMax = grilla[0][2] == jugador_max && grilla[1][2] == jugador_max;

        if (!ganaMax)
            ganaMax = grilla[2][0] == jugador_max && grilla[2][1] == jugador_max;
    }

    return ganaMax;
}

int llenoaux(int grilla[3][3]) {
    int termina = 0;

    for (int i = 0; i < 3 && !termina; i++) {
        for (int j = 0; j < 3 && !termina; j++)
            termina = grilla[i][j] == PART_SIN_MOVIMIENTO;
    }

    return !termina;
}

void print(int grilla[3][3]) {
    printf("\n|");
    for (int  i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grilla[i][j] == PART_SIN_MOVIMIENTO)
                printf("  .");
            else if (grilla[i][j] == PART_JUGADOR_1)
                printf(" X.");
            else
                printf(" O.");
        }
        if (i != 2)
            printf("|\n|");
        else
            printf("|\n\n");
    }
}

void usuario_vs_usuario(tPartida partida, int comienza) {
    int x,y;

    print(partida->tablero->grilla);
    while (partida->estado == PART_EN_JUEGO) {
        printf("Inserte una fila: ");
        scanf("%d", &x);

        printf("Inserte una columna: ");
        scanf("%d", &y);

        checkearMovimiento(&x, &y, partida);

        nuevo_movimiento(partida, x, y);

        print(partida->tablero->grilla);

        if (ganaaux(partida->tablero->grilla, PART_JUGADOR_1)) {
            partida->estado = PART_GANA_JUGADOR_1;
            printf("Gana %s!\n", partida->nombre_jugador_1);
        }
        else if (ganaaux(partida->tablero->grilla, PART_JUGADOR_2)) {
            partida->estado = PART_GANA_JUGADOR_2;
            printf("Gana %s!\n", partida->nombre_jugador_2);
        }
        else if (llenoaux(partida->tablero->grilla)) {
            partida->estado = PART_EMPATE;
            printf("Los jugadores empatan!\n");
        }
    }
}

void usuario_vs_maquina(tPartida partida, int comienza) {
    int x,y;

    print(partida->tablero->grilla);
    while (partida->estado == PART_EN_JUEGO) {
        if (partida->turno_de == PART_JUGADOR_1) {
            printf("Inserte una fila: ");
            scanf("%d", &x);

            printf("Inserte una columna: ");
            scanf("%d", &y);
            checkearMovimiento(&x, &y, partida);

            nuevo_movimiento(partida, x, y);
            print(partida->tablero->grilla);
        }

        if (!llenoaux(partida->tablero->grilla)) {
            tBusquedaAdversaria busqueda;

            crear_busqueda_adversaria(&busqueda, partida);
            proximo_movimiento(busqueda, &x, &y);
            destruir_busqueda_adversaria(&busqueda);

            nuevo_movimiento(partida, x, y);

            print(partida->tablero->grilla);
        }

        if (ganaaux(partida->tablero->grilla, PART_JUGADOR_1)) {
            partida->estado = PART_GANA_JUGADOR_1;
            printf("Gana %s!\n", partida->nombre_jugador_1);
        }
        else if (ganaaux(partida->tablero->grilla, PART_JUGADOR_2)) {
            partida->estado = PART_GANA_JUGADOR_2;
            printf("Gana %s!\n", partida->nombre_jugador_2);
        }
        else if (llenoaux(partida->tablero->grilla)) {
            partida->estado = PART_EMPATE;
            printf("Los jugadores empatan!\n");
        }
    }
}

void maquina_vs_maquina(tPartida partida, int comienza) {
    int x,y;
    while (!ganaaux(partida->tablero->grilla, PART_JUGADOR_1) && !ganaaux(partida->tablero->grilla, PART_JUGADOR_2) && !llenoaux(partida->tablero->grilla)) {
        tBusquedaAdversaria busqueda;

        crear_busqueda_adversaria(&busqueda, partida);
        proximo_movimiento(busqueda, &x, &y);
        destruir_busqueda_adversaria(&busqueda);

        nuevo_movimiento(partida, x, y);
        print(partida->tablero->grilla);
    }

    print(partida->tablero->grilla);

    if (ganaaux(partida->tablero->grilla, PART_JUGADOR_1)) {
        partida->estado = PART_GANA_JUGADOR_1;
        printf("Gana %s!\n", partida->nombre_jugador_1);
    }
    else if (ganaaux(partida->tablero->grilla, PART_JUGADOR_2)) {
        partida->estado = PART_GANA_JUGADOR_2;
        printf("Gana %s!\n", partida->nombre_jugador_2);
    }
    else if (llenoaux(partida->tablero->grilla)) {
        partida->estado = PART_EMPATE;
        printf("Los jugadores empatan!\n");
    }
}

int main() {
    tPartida partida;
    int modo, salir, orden, comienza;
    char j1[50], j2[50];
    salir = 0;

    printf("Inserte el nombre del jugador 1: ");
    scanf("%s", j1);
    printf("Inserte el nombre del jugador 2: ");
    scanf("%s", j2);
    srand(time(NULL));

    while (!salir) {
        printf("\nTa-Te-Ti\n");
        printf("Que modo jugar?\nJugador vs Jugador -> 1\nJugador vs Maquina -> 2\nMaquina vs Maquina -> 3\nModo: ");

        scanf("%d", &modo);

        while (modo < 1 || modo > 3) {
            fflush(stdin);
            printf("Inserte un numero valido.\nJugador vs Jugador -> 1\nJugador vs Maquina -> 2\nMaquina vs Maquina -> 3\n");
            scanf("%d", &modo);
        }

        printf("\nQuien comienza?\nJugador 1 -> 1\nJugador 2 -> 2\nRandom -> 3\nSeleccione: ");
        scanf("%d", &orden);

        while (orden < 1 || orden > 3) {
            fflush(stdin);
            printf("Inserte un numero valido.\nJugador 1 -> 1\nJugador 2 -> 2\nRandom -> 3\nSeleccione: ");
            scanf("%d", &orden);
        }

        if (orden == 1)
            comienza = PART_JUGADOR_1;
        else if (orden == 2)
            comienza = PART_JUGADOR_2;
        else if (orden == 3){
            comienza = rand() % 2 == 0?PART_JUGADOR_1:PART_JUGADOR_2;

            if (comienza == PART_JUGADOR_1)
                printf("Comienza %s\n", j1);
            else
                printf("Comienza %s\n", j2);

        }

        if (modo == 1) {
            nueva_partida(&partida, PART_MODO_USUARIO_VS_USUARIO, comienza, "", "");
            strcpy(partida->nombre_jugador_1, j1);
            strcpy(partida->nombre_jugador_2, j2);

            usuario_vs_usuario(partida, comienza);
        }
        else if (modo == 2) {
            nueva_partida(&partida, PART_MODO_USUARIO_VS_AGENTE_IA, comienza, "", "Maquina");
            strcpy(partida->nombre_jugador_1, j1);

            usuario_vs_maquina(partida, comienza);
        }
        else {
            nueva_partida(&partida, PART_MODO_AGENTE_IA_VS_AGENTE_IA, comienza, "Maquina 1", "Maquina 2");
            maquina_vs_maquina(partida, comienza);
        }

        printf("\nSalir del juego? \n1 -> Si\n2 -> No\nSalir: ");
        scanf("%d", &salir);

        while (salir < 1 || salir > 2) {
            fflush(stdin);
            printf("\nSalir del juego? \n1 -> Si\n2 -> No\nSalir: ");
            scanf("%d", &salir);
        }
        printf("\n");
        salir = salir % 2;

        finalizar_partida(&partida);
    }

    return 0;
}