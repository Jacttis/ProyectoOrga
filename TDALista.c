//
// Created by julian acttis on 8/9/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

#define LST_ELEMENTO_NULO           1
#define LST_NO_EXISTE_SIGUIENTE     2
#define LST_NO_EXISTE_ANTERIOR      3
#define LST_POSICION_INVALIDA       4
#define LST_ERROR_MEMORIA           5


/**
 Inicializa una lista vac�a.
 Una referencia a la lista creada es referenciada en *L.
**/
extern void crear_lista(tLista * l){
    *l=(tLista)malloc(sizeof(struct celda)); // guarda memoria para la lista
    if(!*l){
        exit(LST_ERROR_MEMORIA);
    }
    (*l)->elemento=NULL;     //se crea un centinela con elemento null y siguiente null(Lista Vacia)
    (*l)->siguiente=NULL;

}

/**
 Inserta el elemento E, en la posici�n P, en L.
 Con L = A,B,C,D y la posici�n P direccionando C, luego:
 L' = A,B,E,C,D
**/
extern void l_insertar(tLista l, tPosicion p, tElemento e) {
    tPosicion nuevoNodo;   // se asigna un nuevo nodo
    nuevoNodo = (tPosicion) malloc(sizeof(struct celda)); // se guarda lugar en memoria para el nodo
    if (!nuevoNodo ) {
        exit(LST_ERROR_MEMORIA);
    }
    nuevoNodo->elemento = e;                              // setea el elemento en nuevoNodo
    nuevoNodo->siguiente = p->siguiente;                  //Setea el Nodo siguiente al nuevoNodo como el siguiente del pasado como parametro
    p->siguiente = nuevoNodo;                          //Setea el siguiente del pasado como parametro como el nuevoN1odo

}

/**
 Elimina el nodo que se encuentra en la posici�n P de L.
 El elemento almacenado en la posici�n P es eliminado mediante la funci�n fEliminar parametrizada.
 Si P es fin(L), finaliza indicando LST_POSICION_INVALIDA.
**/
extern void l_eliminar(tLista l, tPosicion p, void (*fEliminar)(tElemento)){
    tPosicion posicionAEliminar=p->siguiente;
    if(posicionAEliminar==NULL){
        exit(LST_POSICION_INVALIDA);
    }
    p->siguiente=posicionAEliminar->siguiente;
    fEliminar(posicionAEliminar->elemento);
    free(posicionAEliminar->elemento); //?? preguntar
    free(posicionAEliminar);

}

/**
 Destruye la lista L, elimininando cada una de sus posiciones. Los elementos almacenados en las posiciones son eliminados mediante la funci�n fEliminar parametrizada.
**/
extern void l_destruir(tLista * l, void (*fEliminar)(tElemento)){

    tPosicion posicionAEliminar=(*l);
    tPosicion posicionSiguienteAEliminar;
    while(posicionAEliminar!=NULL){
        posicionSiguienteAEliminar=posicionAEliminar->siguiente;
        fEliminar(posicionAEliminar->elemento);
        free(posicionAEliminar->elemento);
        free(posicionAEliminar);
        posicionAEliminar=posicionSiguienteAEliminar;
    }
    free(*l);
}

/**
Recupera y retorna el elemento en la posici�n P.
Si P es fin(L), finaliza indicando LST_POSICION_INVALIDA.
**/
extern tElemento l_recuperar(tLista l, tPosicion p){
   if(p==NULL){
       exit(LST_POSICION_INVALIDA);
   }
    return p->siguiente->elemento; //devuelvo la siguiente posicion
}

/**
 Recupera y retorna la primera posici�n de L.
 Si L es vac�a, primera(L) = ultima(L) = fin(L).
**/
extern tPosicion l_primera(tLista l){

    return l;  // devuelvo sentinela
}

/**
 Recupera y retorna la posici�n siguiente a P en L.
 Si P es fin(L), finaliza indicando LST_NO_EXISTE_SIGUIENTE.
**/

extern tPosicion l_siguiente(tLista l, tPosicion p){
    if(p->siguiente==NULL ){
        exit(LST_NO_EXISTE_SIGUIENTE);
    }
    return p->siguiente;
}

/**
 Recupera y retorna la posici�n anterior a P en L.
 Si P es primera(L), finaliza indicando LST_NO_EXISTE_ANTERIOR.
**/
extern tPosicion l_anterior(tLista l, tPosicion p){
    tPosicion posicionActual=l->siguiente; // posicionActual variable que busca el anterior a p,Empezando desde el primer elemento
    if(posicionActual==p){     //si es la primera posicion no tiene anterior
        exit(LST_NO_EXISTE_ANTERIOR);
    }
        while(posicionActual->siguiente!=p && posicionActual->siguiente!=NULL){  //mientras no sea el ultimo y no se encuentre la posicion pasada
            posicionActual=posicionActual->siguiente;                            //se le asigna el siguiente a posicionActual
        }
        return posicionActual;                     // retorna el anterior a p
}

/**
Recupera y retorna la �ltima posici�n de L.
Si L es vac�a, primera(L) = ultima(L) = fin(L).
**/
extern tPosicion l_ultima(tLista l){
    tPosicion posicionActual=l->siguiente; //posicionActual busca el ultimo empezando desde el primer elemento
    while(posicionActual->siguiente->siguiente!=NULL){     //mientras no sea el ultimo a posicionActual se le asigna el siguiente
        posicionActual=posicionActual->siguiente;
    }

    return posicionActual;   // retorna ultimo elemento
}

/**
Recupera y retorna la posici�n fin de L.
Si L es vac�a, primera(L) = ultima(L) = fin(L).
**/
extern tPosicion l_fin(tLista l){
    tPosicion posicionActual=l->siguiente; //posicionActual busca el ultimo empezando desde el primer elemento
    if(l->siguiente==NULL){
        return l;
    }
    while(posicionActual->siguiente!=NULL){     //mientras no sea el ultimo a posicionActual se le asigna el siguiente
        posicionActual=posicionActual->siguiente;
    }

    return posicionActual;   // retorna ultimo elemento
}






