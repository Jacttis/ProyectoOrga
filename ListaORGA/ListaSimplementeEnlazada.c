#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/**
 Inicializa una lista vac�a.
 Una referencia a la lista creada es referenciada en *L.
**/
extern void crear_lista(tLista * l){

    *l= (tLista) malloc((sizeof(struct celda)));//Guardo Memoria
    if(!*l){
        exit(LST_ERROR_MEMORIA);
    }
    (*l)->elemento=NULL;
    (*l)->siguiente=NULL;
}

/**
 Inserta el elemento E, en la posici�n P, en L.
 Con L = A,B,C,D y la posici�n P direccionando C, luego:
 L' = A,B,E,C,D
**/
extern void l_insertar(tLista l, tPosicion p, tElemento e){

    tPosicion nuevoNodo=(tPosicion)malloc(sizeof(struct celda));//Guardo memoria para la nueva celda
    if(!nuevoNodo){
        exit(LST_ERROR_MEMORIA);
    }
    nuevoNodo->elemento=e;//Seteo el elemento
    nuevoNodo->siguiente=p->siguiente;//Seteo el siguiente del Nuevo nodo
    p->siguiente=nuevoNodo;//Cambio el apuntado del nodo anterior al nuevo nodo
}

/**
 Elimina el nodo que se encuentra en la posici�n P de L.
 El elemento almacenado en la posici�n P es eliminado mediante la funci�n fEliminar parametrizada.
 Si P es fin(L), finaliza indicando LST_POSICION_INVALIDA.
**/
extern void l_eliminar(tLista l, tPosicion p, void (*fEliminar)(tElemento)){
    if(p->siguiente==NULL){
        exit(LST_POSICION_INVALIDA);
    }
    tPosicion posAeliminar=p->siguiente;
    p->siguiente=posAeliminar->siguiente;
    fEliminar(posAeliminar->elemento);
    free(posAeliminar->elemento);// preguntar
    free(posAeliminar);
}

/**
 Destruye la lista L, elimininando cada una de sus posiciones. Los elementos almacenados en las posiciones son eliminados mediante la funci�n fEliminar parametrizada.
**/
extern void l_destruir(tLista * l, void (*fEliminar)(tElemento)){
    tPosicion posActual=(*l)->siguiente;//preguntar esta wea
    while(posActual->siguiente!=NULL){
        tPosicion posAEliminar;
        posAEliminar=posActual;
        posActual=posActual->siguiente;
        fEliminar(posAEliminar->elemento);
        free(posAEliminar);
    }
    fEliminar(posActual->elemento);
    free(posActual);//elimina ultima posicion
   // free(l);//?
}

/**
Recupera y retorna el elemento en la posici�n P.
Si P es fin(L), finaliza indicando LST_POSICION_INVALIDA.
**/
extern tElemento l_recuperar(tLista l, tPosicion p){
  if(p->siguiente==NULL){
      exit(LST_POSICION_INVALIDA);
  }
    return p->siguiente->elemento;//Se devuelve el siguiente
}
/**
 Recupera y retorna la primera posici�n de L.
 Si L es vac�a, primera(L) = ultima(L) = fin(L).
**/
extern tPosicion l_primera(tLista l){
    return l;
}


/**
 Recupera y retorna la posici�n siguiente a P en L.
 Si P es fin(L), finaliza indicando LST_NO_EXISTE_SIGUIENTE.
**/
extern tPosicion l_siguiente(tLista l, tPosicion p){

    if(p->siguiente==NULL){
        exit(LST_NO_EXISTE_SIGUIENTE);//Mirar el caso que siguiente es nulo
    }
    return p->siguiente;
}

/**
 Recupera y retorna la posici�n anterior a P en L.
 Si P es primera(L), finaliza indicando LST_NO_EXISTE_ANTERIOR.
**/
extern tPosicion l_anterior(tLista l, tPosicion p){

    tPosicion posActual=l->siguiente;
    if(posActual==p){
        exit(LST_POSICION_INVALIDA);
    }
    while(posActual->siguiente!=p && posActual->siguiente!=NULL){
        posActual=posActual->siguiente;
    }
    if(posActual->siguiente==p){
        return posActual;
    }
    else{
        exit(LST_POSICION_INVALIDA);
    }
}

/**
Recupera y retorna la �ltima posici�n de L.
Si L es vac�a, primera(L) = ultima(L) = fin(L).
**/
extern tPosicion l_ultima(tLista l){
    tPosicion posActual=l->siguiente;
    if(posActual==NULL){
        return l;
    }
    while(posActual->siguiente->siguiente!=NULL){
        posActual=posActual->siguiente;
    }
    return posActual;
}


/**
Recupera y retorna la posici�n fin de L.
Si L es vac�a, primera(L) = ultima(L) = fin(L).
**/
extern tPosicion l_fin(tLista l){

    tPosicion posActual=l->siguiente;
    while(posActual->siguiente!=NULL){
        posActual=posActual->siguiente;
    }
    return posActual;
}


