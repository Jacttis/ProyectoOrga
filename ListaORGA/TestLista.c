//
// Created by Axel on 13/9/2019.
//
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

extern void eliminar(int *el){
    free(el);
}

int main(){
    tLista l;
    int e=1;
    int e2=2;
    crear_lista(&l);
    l_insertar(l,l_primera(l),&e);
    int *e1=l_recuperar(l,l_primera(l));
    printf("%d \n",*e1);
    l_insertar(l,l_siguiente(l,l_primera(l)),&e2);
    int *e3=l_recuperar(l,l_siguiente(l,l_primera(l)));
    printf("%d \n",*e3);
    void (*Eliminar)(int*)=eliminar;
   /* l_eliminar(l, l_primera(l), (void (*)(tElemento)) Eliminar);
    int *e13=l_recuperar(l,l_primera(l));
    printf("%d \n",*e13);*/
   l_destruir(&l, (void (*)(tElemento)) Eliminar);
   int *e54=l_recuperar(l,l_primera(l));
   printf("%d \n",*e54);
}