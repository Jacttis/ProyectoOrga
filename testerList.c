//
// Created by julia on 9/18/2019.
//
#include <stdlib.h>
#include <stdio.h>
#include "lista.h"
#include "conio.h"
void eliminar(int *e){
    free(e);
}

void insertar(tLista list){
    int  pos;
    tPosicion posicion;
    int * e;
    e=malloc(sizeof(int));
    printf("Ingrese el elemento a ingresar: \n");
    scanf("%i",e);
    printf("\n\n");
    printf("Si desea insertar en el comienzo ingrese 1\n");
    printf("Si desea insertar en la ultima posicion ingrese 2\n");
    printf("Si desea insertar en el final ingrese 3\n");
    scanf("%i",&pos);
    printf("\n\n");

    switch(pos){
        case 1:
            posicion=l_primera(list);
            l_insertar(list,posicion,e);
            break;
        case 2:
            posicion=l_ultima(list);
            l_insertar(list,posicion,e);
            break;
        case 3:
            posicion=l_fin(list);
            l_insertar(list,posicion,e);
            break;
        default:
            printf("opcion no valida");
            break;
    }

}
void Eliminar(tLista list){
    int pos;
    tPosicion posicion;
    printf("Si desea eliminar en el comienzo ingrese '1'\n");
    printf("Si desea eliminar en la ultima posicion ingrese '2'\n");
    printf("Si desea eliminar en el final ingrese '3'\n");
    scanf("%d",&pos);
    switch(pos){
        case 1:
            posicion=l_primera(list);
            l_eliminar(list, posicion, (void (*)(tElemento)) eliminar);
            break;
        case 2:
            posicion=l_ultima(list);
            l_eliminar(list, posicion, (void (*)(tElemento)) eliminar);
            break;
        case 3:
            posicion=l_fin(list);
            l_eliminar(list, posicion, (void (*)(tElemento)) eliminar);
            break;
        default:
            printf("opcion no valida");
            break;
    }
    printf("\n\n");
}





int main(){
    char crear;
    int opcion;
    tLista lista;
   printf("Desea crear una nueva lista ingrese 'y' para crear o 'n' para cerrar \n");
    scanf("%c",&crear);
    if(crear=='y') {
        crear_lista(&lista);
        do {
            printf("///////menu///////\n");
            printf(" Ingrese '1' para agregar a lista\n");
            printf("'2' para eliminar de la lista\n");
            printf("'3' para mostrar elementos\n");
            printf("'4' para destruir la lista\n");
            scanf("%i", &opcion);
            switch (opcion) {
                case 1:
                    insertar(lista);
                    break;
                case 2:
                    Eliminar(lista);
                    break;
                case 3:
                    printf("Mostrar: \n");
                    int * e=l_recuperar(lista,l_primera(lista));
                    printf("%d",*e);
                case 4:
                    exit(11);
                default:
                    exit(11);
            }

        } while (opcion != 4);

    }
    else{
        exit(11);
    }
return 0;
}
