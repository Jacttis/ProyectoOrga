//
// Created by Axel and Julian on 10/1/2019.
//
#include "arbol.h"
#include <stdlib.h>
#include <stdio.h>
#include "../TDALista/lista.h"


void (*EliminarElemento)(tElemento);
/**
Inicializa un �rbol vac�o.
Una referencia al �rbol creado es referenciado en *A.
**/
extern void crear_arbol(tArbol * a){
    *a=(tArbol)malloc(sizeof(struct arbol));
    (*a)->raiz=NULL;
}

/**
Crea la ra�z de A.
Si A no es vac�o, finaliza indicando ARB_OPERACION_INVALIDA.
**/
extern void crear_raiz(tArbol a, tElemento e){

    if(a->raiz!=NULL){
        exit(ARB_OPERACION_INVALIDA);
    }
    tNodo  nodoN;
    tLista lista;
    nodoN=(tNodo)malloc(sizeof(struct nodo));
    crear_lista(&lista);
    nodoN->elemento=e;
    nodoN->hijos=lista;
    nodoN->padre=NULL;
    a->raiz=nodoN;
}
tPosicion buscar(tLista l,tNodo nodo);
/**
 Inserta y retorna un nuevo nodo en A.
 El nuevo nodo se agrega en A como hijo de NP, hermano izquierdo de NH, y cuyo r�tulo es E.
 Si NH es NULL, el nuevo nodo se agrega como �ltimo hijo de NP.
 Si NH no corresponde a un nodo hijo de NP, finaliza indicando ARB_POSICION_INVALIDA.
 NP direcciona al nodo padre, mientras NH al nodo hermano derecho del nuevo nodo a insertar.
**/
extern tNodo a_insertar(tArbol a, tNodo np, tNodo nh, tElemento e){

    tNodo nodoN;
    tLista listaH;
    crear_lista(&listaH);
    nodoN=(tNodo)malloc((sizeof(struct nodo)));
    nodoN->elemento = e;
    nodoN->padre = np;
    nodoN->hijos = listaH;
    // el hermano es nullo entonces el nodo nuevo se inserta al final
    if(nh==NULL){
        l_insertar(np->hijos,l_fin(np->hijos),nodoN);
    }
    else{ //recorremos desde el primer hijo de np

        tPosicion pos=buscar(np->hijos,nh);

        if (pos==NULL){
            exit(ARB_POSICION_INVALIDA);
        }
        else{
            l_insertar(np->hijos,pos,nodoN);
        }
    }
    return nodoN;
}
void eliminarNVacio(tNodo nodo){

}
void eliminarN(tNodo nodo){
    EliminarElemento(nodo->elemento);
    free(nodo->elemento);
    free(nodo->hijos);
    free(nodo);

}
void eliminarNSub(tNodo nodo){
    EliminarElemento(nodo->elemento);
    if(nodo->padre!=NULL){
        l_eliminar(nodo->padre->hijos,buscar(nodo->padre->hijos,nodo),EliminarElemento);
    }
    free(nodo->hijos);

}
tPosicion buscar(tLista l,tNodo nodo){
    tPosicion posicion=l_primera(l);
    int encontre=0;
    while(posicion!=NULL && encontre!=1){
        if(l_recuperar(l,posicion)==nodo){
            encontre=1;
        }
        else{
            posicion=l_siguiente(l,posicion)!=NULL?l_siguiente(l,posicion):NULL;
        }
    }
    return posicion;
}
/**
 Elimina el nodo N de A.
 El elemento almacenado en el �rbol es eliminado mediante la funci�n fEliminar parametrizada.
 Si N es la ra�z de A, y tiene un s�lo hijo, este pasa a ser la nueva ra�z del �rbol.
 Si N es la ra�z de A, y a su vez tiene m�s de un hijo, finaliza retornando ARB_OPERACION_INVALIDA.
 Si N no es la ra�z de A y tiene hijos, estos pasan a ser hijos del padre de N, en el mismo orden y a partir de la posici�n que ocupa N en la lista de hijos de su padre.
**/
extern void a_eliminar(tArbol a, tNodo n, void (*fEliminar)(tElemento)){
    tLista hijos=n->hijos;
    tNodo padre=n->padre;
    tLista hermanos;
    tNodo hijoraiz;
    tLista listaaux;
    tPosicion posEnHermanos;
    tPosicion posHijos;
    EliminarElemento=fEliminar;
    if(n==a->raiz){
        if(l_primera(hijos)==l_fin(hijos)){
            eliminarN(n);
            a->raiz=NULL;
        }
        else{
            if(l_siguiente(hijos,l_primera(hijos))==l_fin(hijos)){
                hijoraiz=l_recuperar(n->hijos,l_primera(n->hijos));
                listaaux=n->hijos;
                EliminarElemento(n->elemento);
                n->hijos=hijoraiz->hijos;
                n->elemento=hijoraiz->elemento;
                l_destruir(&listaaux, (void (*)(tElemento)) eliminarN);
            }
            else{
                exit(ARB_OPERACION_INVALIDA);
            }
        }
    }
    else{
        hermanos=padre->hijos;
        posEnHermanos=buscar(hermanos,n);
        if(l_primera(hijos)==l_fin(hijos)){
            l_destruir(&hijos, (void (*)(tElemento)) &eliminarN);
            l_eliminar(hermanos, posEnHermanos, (void (*)(tElemento)) &eliminarN);
        }
        else{
            posHijos = l_ultima(hijos);
            while(posHijos!=l_primera(hijos)) {
                l_insertar(hermanos, l_siguiente(hermanos,posEnHermanos), l_recuperar(hijos, posHijos));
                posHijos=l_anterior(hijos,posHijos);
            }
            l_insertar(hermanos, l_siguiente(hermanos,posEnHermanos), l_recuperar(hijos, posHijos));
            l_destruir(&hijos, (void (*)(tElemento)) &eliminarNVacio);
            posEnHermanos=buscar(hermanos,n);
            l_eliminar(hermanos, posEnHermanos, (void (*)(tElemento)) &eliminarN);
        }
    }
    printf("termina eliminar\n");
}

void posOrden(tArbol arbol,tNodo nodo){
   tNodo hijo=NULL;
    tPosicion posicionHijo=NULL;
    if(l_primera(nodo->hijos)!=l_fin(nodo->hijos)){
     hijo=l_recuperar(nodo->hijos,l_primera(nodo->hijos));
     posicionHijo=l_primera(nodo->hijos);
   }
   while(hijo!=NULL && posicionHijo!=NULL){
       posOrden(arbol,hijo);
       posicionHijo=posicionHijo!=l_ultima(nodo->hijos)?l_siguiente(nodo->hijos,posicionHijo):NULL;
       hijo=posicionHijo!=NULL?l_recuperar(nodo->hijos,posicionHijo):NULL;
   }
   l_destruir(&(nodo->hijos),EliminarElemento);
   eliminarN(nodo);

}
void posOrdenSub(tArbol arbol,tNodo nodo){
    tNodo hijo=NULL;
    tPosicion posicionHijo=NULL;
    if(l_primera(nodo->hijos)!=l_fin(nodo->hijos)){
        hijo=l_recuperar(nodo->hijos,l_primera(nodo->hijos));
        posicionHijo=l_primera(nodo->hijos);
    }
    while(hijo!=NULL && posicionHijo!=NULL){
        posOrdenSub(arbol,hijo);
        posicionHijo=posicionHijo!=l_ultima(nodo->hijos)?l_siguiente(nodo->hijos,posicionHijo):NULL;
        hijo=posicionHijo!=NULL?l_recuperar(nodo->hijos,posicionHijo):NULL;
    }
    l_destruir(&(nodo->hijos),EliminarElemento);
    eliminarNSub(nodo);

}
/**
 Destruye el �rbol A, eliminando cada uno de sus nodos.
 Los elementos almacenados en el �rbol son eliminados mediante la funci�n fEliminar parametrizada.
**/
extern void a_destruir(tArbol * a, void (*fEliminar)(tElemento)){
    EliminarElemento=fEliminar;
    posOrden(*a,(*a)->raiz);
    free(*a);
    (*a)=NULL;
}

/**
Recupera y retorna el elemento del nodo N.
*/
extern tElemento a_recuperar(tArbol a, tNodo n){
    if(n==NULL){
        printf("Null");
        exit(4);
    }

    return n->elemento;
}

/**
Recupera y retorna el nodo correspondiente a la ra�z de A.
**/
extern tNodo a_raiz(tArbol a){

    return a->raiz;
}

/**
 Obtiene y retorna una lista con los nodos hijos de N en A.
**/
extern tLista a_hijos(tArbol a, tNodo n){
    return n->hijos;
}
void ClonarArbol(tArbol *a,tArbol * copiaA,tNodo padreA,tNodo padreC){

    tLista listaHijosPA=a_hijos(*a,padreA);
    tNodo nodoInsertar;
    tNodo nodoRecuperar;
    tPosicion posActual;
    if(l_primera(listaHijosPA)!=l_fin(listaHijosPA)){//si tiene hijos

        posActual=l_primera(listaHijosPA);//centinela

        while(posActual!=NULL){

            nodoRecuperar=l_recuperar(listaHijosPA,posActual);
            nodoInsertar=a_insertar(*copiaA,padreC,NULL,nodoRecuperar->elemento);

            ClonarArbol(a,copiaA,nodoRecuperar,nodoInsertar);

            posActual=posActual!=l_ultima(listaHijosPA)?l_siguiente(listaHijosPA,posActual):NULL;
        }
    }
}
/**
 Inicializa un nuevo �rbol en *SA.
 El nuevo �rbol en *SA se compone de los nodos del sub�rbol de A a partir de N.
 El subarbol de A a partir de N debe ser eliminado de A.
**/
extern void a_sub_arbol(tArbol a, tNodo n, tArbol * sa){
    crear_raiz(*sa,n->elemento);
    ClonarArbol(&a,sa,n,a_raiz(*sa));
    EliminarElemento= (void (*)(tElemento))  &eliminarNVacio ;
    posOrdenSub(a,n);

}
