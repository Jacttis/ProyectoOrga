//
// Created by julian acttis on 12/9/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"


 extern void Eliminar(int * elem){
    free(elem);
}
int main(){
    char crear;
    tLista l;
    int accion=6;
    tPosicion posicion;
    char direccion;
    printf("Desea crear una nueva lista ingrese 'y' para crear o 'n' para cerrar \n");
    scanf("%c",&crear);
    if(crear=='y'){
        crear_lista(&l);
        while(accion!=4){
            printf("Que desea realizar, ingrese '1' para agregar a lista,'2' para eliminar de la lista,'3' para recuperar un elemento de la lista, '4' para destruir la lista");
            scanf("%d",&accion);
            if(accion==1){
                printf(" Si desea ingresar en el final ingrese 'f' ,si desea en la ultima ingrese 'u', de lo contrario ingrese 'p' se comenzara del principio y se pedira siguiente");
                scanf("%c",&direccion);
                if(direccion=='f'){
                    posicion=l_fin(l);
                }
            }


        }

    }
    else{
        exit(11);
    }



}