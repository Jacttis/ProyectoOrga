
#include "../TDALista/lista.h"
#include "arbol.h"
#include <stdio.h>
#include <stdlib.h>

void eliminar(int *el){
    free(el);
}
//Nodo actual empieza siendo raiz
void mostrarElementosPreOrden(tArbol arbol,tNodo nodoActual){


    tLista listaHijosNA=a_hijos(arbol,nodoActual);

    int *a=a_recuperar(arbol,nodoActual);
    printf("%d\n",*a);

    if(l_primera(listaHijosNA)!=l_fin(listaHijosNA)){

        tNodo tposActual;
        tPosicion posActual=l_primera(listaHijosNA);//centinela de hijos nodoActual
        while(posActual!=NULL){
            tposActual=l_recuperar(listaHijosNA,posActual);// primer hijo de NodoActual
            mostrarElementosPreOrden(arbol,tposActual);
            posActual=posActual->siguiente->siguiente!=NULL?l_siguiente(listaHijosNA,posActual):NULL;
        }


    }

}

int main(){

    tArbol arbol;
    tArbol copiaA;

    crear_arbol(&arbol);
    crear_arbol(&copiaA);

    int *raiz;
    int *elem2;
    int *elem3;
    int*elem4;
    int*elem5;
    int*elem6;
    int*elem7;
    int*elem8;
    int*elem9;

    raiz=malloc(sizeof(int));
    elem2=malloc(sizeof(int));
    elem3=malloc(sizeof(int));
    elem4=malloc(sizeof(int));
    elem5=malloc(sizeof(int));
    elem6=malloc(sizeof(int));
    elem7=malloc(sizeof(int));
    elem8=malloc(sizeof(int));
    elem9=malloc(sizeof(int));

    scanf("%i",raiz);
    scanf("%i",elem2);
    scanf("%i",elem3);
    scanf("%i",elem4);
    scanf("%i",elem5);
    scanf("%i",elem6);
    scanf("%i",elem7);
    scanf("%i",elem8);
    scanf("%i",elem9);

    crear_raiz(arbol,raiz);
    //  tLista hijos=a_hijos(arbol,a_raiz(arbol));
    tNodo segundoinsertado=a_insertar(arbol,a_raiz(arbol),NULL,elem2);//inserto 2 hijo de raiz
    tNodo terceroInsertado=a_insertar(arbol,a_raiz(arbol),NULL,elem3);//inserto 3 hermano de 2

    tNodo cuartoInsertado= a_insertar(arbol,segundoinsertado,NULL,elem4);
    a_insertar(arbol,cuartoInsertado,NULL,elem5);
    a_insertar(arbol,cuartoInsertado,NULL,elem6);
    tNodo septimoInsertado=a_insertar(arbol,terceroInsertado,NULL,elem7);
    a_insertar(arbol,terceroInsertado,NULL,elem8);
    a_insertar(arbol,septimoInsertado,NULL,elem9);

    mostrarElementosPreOrden(arbol,a_raiz(arbol));
    a_sub_arbol(arbol,terceroInsertado,&copiaA);

    printf("elementos subArbol:\n");

    mostrarElementosPreOrden(copiaA,a_raiz(copiaA));
    printf("\n\n");
    mostrarElementosPreOrden(arbol,a_raiz(arbol));
    a_destruir(&arbol, (void (*)(tElemento)) &eliminar);
    printf("Destrui\n");
    mostrarElementosPreOrden(arbol,a_raiz(arbol));



}