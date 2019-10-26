//
// Created by julia on 10/8/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include "TDALista/lista.h"
void mostrarElementos(tLista list){
    tPosicion posM=l_primera(list);


    while(posM!=l_fin(list)){

        int *m=(l_recuperar(list,posM));
        printf("%d ->",*m);
        posM=l_siguiente(list,posM);
    }
    printf("Fin");
    printf("\n\n");

}
int main(){
    tLista lista;
    tLista listaC;
    crear_lista(&lista);
  //  crear_lista(&listaC);
    int * num;
    int e=2;
    num=&e;
    l_insertar(lista,l_fin(lista),num);
    int * num2;
    int e2=3;
    num2=&e2;
    l_insertar(lista,l_fin(lista),num2);
    int * num3;
    num3=(int)malloc(sizeof(int));
    *num3=4;
    l_insertar(lista,l_fin(lista),num3);
    mostrarElementos(lista);
   listaC=clonar(lista);
    mostrarElementos(listaC);
}