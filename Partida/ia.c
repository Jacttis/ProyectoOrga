#include <stdlib.h>
#include <stdio.h>
#include "../TDALista/lista.h"
#include "../TDAArbol/arbol.h"
#include "ia.h"
#include <time.h>
// Prototipos de funciones auxiliares.
static void ejecutar_min_max(tBusquedaAdversaria b);
static void crear_sucesores_min_max(tArbol a, tNodo n, int es_max, int alpha, int beta, int jugador_max, int jugador_min);
static int valor_utilidad(tEstado e, int jugador_max);
static tLista estados_sucesores(tEstado e, int ficha_jugador);
static void diferencia_estados(tEstado anterior, tEstado nuevo, int * x, int * y);
static tEstado clonar_estado(tEstado e);
int ganaIA(tEstado estado,int jugador);
int lleno(tEstado estado);
int MIN(int v1,int v2);
int MAX(int v1,int v2);
void crear_busqueda_adversaria(tBusquedaAdversaria * b, tPartida p){
    int i, j;
    tEstado estado;

    (*b) = (tBusquedaAdversaria) malloc(sizeof(struct busqueda_adversaria));
    if ((*b) == NULL) exit(IA_ERROR_MEMORIA);

    estado = (tEstado) malloc(sizeof(struct estado));
    if (estado == NULL) exit(IA_ERROR_MEMORIA);

    // Se clona el estado del tablero de la partida, al estado inicial de la b�squeda adversaria.
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            estado->grilla[i][j] = p->tablero->grilla[i][j];
        }
    }

	// Se asume que el estado de la partida es PART_EN_JUEGO por lo que, la utilidad del estado
	// inicialmente es IA_NO_TERMINO
    estado->utilidad = IA_NO_TERMINO;

    // Inicializa los valores que representar�n a los jugadores MAX y MIN respectivamente.
    (*b)->jugador_max = p->turno_de;
    (*b)->jugador_min = (p->turno_de == PART_JUGADOR_1) ? PART_JUGADOR_2 : PART_JUGADOR_1;

    // Inicializa un �rbol para la b�squeda adversaria inicialmente vac�o.
    crear_arbol(&((*b)->arbol_busqueda));

    // Inicializa la ra�z del �rbol de b�squeda con el estado del tablero T.
    crear_raiz((*b)->arbol_busqueda, estado);
    // Ejecuta algoritmo Min-Max con podas Alpha-Beta.
    ejecutar_min_max((*b));
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
*/
void proximo_movimiento(tBusquedaAdversaria b, int * x, int * y) {
    tArbol arbol = b->arbol_busqueda;
    tNodo raiz=arbol->raiz;
    tEstado mejorEstado, Inicial;
    tPosicion PosActual, PosFinal;
    int ValorAComparar, actualUtilidad;

    PosActual = l_primera(arbol->raiz->hijos);
    PosFinal = l_fin(arbol->raiz->hijos);
    Inicial = a_recuperar(arbol, arbol->raiz);
    mejorEstado = NULL;
    ValorAComparar = 0;
    while (PosActual != PosFinal && ValorAComparar != IA_GANA_MAX) {
        tEstado estadoSucesor=a_recuperar(arbol, l_recuperar(raiz->hijos, PosActual));
        actualUtilidad = estadoSucesor->utilidad;
        if (actualUtilidad > ValorAComparar && actualUtilidad != IA_NO_TERMINO) {
            mejorEstado = ((tEstado)a_recuperar(arbol, l_recuperar(raiz->hijos, PosActual)));
            ValorAComparar = actualUtilidad;
        }
        PosActual = l_siguiente(raiz->hijos, PosActual);
    }
    if (mejorEstado == NULL)
        mejorEstado = ((tEstado)a_recuperar(arbol, l_recuperar(raiz->hijos, l_ultima(raiz->hijos))));

    diferencia_estados(Inicial, mejorEstado, x, y);
}

void EliminarEstado(tEstado *e){
    free((*e)->grilla);
}
/**
>>>>>  A IMPLEMENTAR   <<<<<
**/
void destruir_busqueda_adversaria(tBusquedaAdversaria * b){
    a_destruir(&(*b)->arbol_busqueda, (void (*)(tElemento)) &EliminarEstado);
    free(*b);
}

// ===============================================================================================================
// FUNCIONES Y PROCEDEMIENTOS AUXILIARES
// ===============================================================================================================

/**
Ordena la ejecuci�n del algoritmo Min-Max para la generaci�n del �rbol de b�squeda adversaria, considerando como
estado inicial el estado de la partida almacenado en el �rbol almacenado en B.
**/
static void ejecutar_min_max(tBusquedaAdversaria b){
    tArbol a = b->arbol_busqueda;
    tNodo r = a_raiz(a);
    int jugador_max = b->jugador_max;
    int jugador_min = b->jugador_min;
    crear_sucesores_min_max(a, r, 1, IA_INFINITO_NEG, IA_INFINITO_POS, jugador_max, jugador_min);
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
Implementa la estrategia del algoritmo Min-Max con podas Alpha-Beta, a partir del estado almacenado en N.
- A referencia al �rbol de b�squeda adversaria.
- N referencia al nodo a partir del cual se construye el sub�rbol de b�squeda adversaria.
- ES_MAX indica si N representa un nodo MAX en el �rbol de b�squeda adversaria.
- ALPHA y BETA indican sendos valores correspondientes a los nodos ancestros a N en el �rbol de b�squeda A.
- JUGADOR_MAX y JUGADOR_MIN indican las fichas con las que juegan los respectivos jugadores.
**/
static void crear_sucesores_min_max(tArbol a, tNodo n, int es_max, int alpha, int beta, int jugador_max, int jugador_min){
    tEstado estado = a_recuperar(a,n);
    tEstado hijoEstado;
    tPosicion posActual;
    tLista sucesores;
    int utilidad=valor_utilidad(estado,jugador_max);
    int mayor_valor_sucesor;

    if(utilidad!=IA_NO_TERMINO){
        estado->utilidad=utilidad;
    }
    else {
        if (es_max) {

            mayor_valor_sucesor = IA_INFINITO_NEG;//se hace para calcular alpha
            sucesores = estados_sucesores(estado, jugador_max);
            posActual = l_primera(sucesores);

            while (posActual != NULL) {
                //Incializo el estado hijo
                hijoEstado = l_recuperar(sucesores, posActual);
                hijoEstado->utilidad = valor_utilidad(hijoEstado, jugador_max);
                //Inserto el estado hijo
                a_insertar(a, n, NULL, hijoEstado);
                //llamo recursivamente con el nuevo hijo, y cambio al estado a min con 0
                crear_sucesores_min_max(a, l_recuperar(a_hijos(a, n), l_ultima(a_hijos(a, n))), 0, alpha, beta,
                                        jugador_max, jugador_min);
                //se calcula el valor de alpha
                mayor_valor_sucesor=MAX(mayor_valor_sucesor,hijoEstado->utilidad);
                alpha = MAX(alpha, mayor_valor_sucesor);
                estado->utilidad = alpha;
                if (beta <= alpha) {
                    break;
                }
                posActual = posActual == l_ultima(sucesores) ? NULL : l_siguiente(sucesores, posActual);
            }

        } else {

            mayor_valor_sucesor = IA_INFINITO_POS;//se hace para calcular beta
            sucesores = estados_sucesores(estado, jugador_min);
            posActual = l_primera(sucesores);

            while (posActual != NULL) {
                //inicializo el estado hijo
                hijoEstado = l_recuperar(sucesores, posActual);
                hijoEstado->utilidad = valor_utilidad(hijoEstado, jugador_min);
                //inserto el estado hijo
                a_insertar(a, n, NULL, hijoEstado);
                //llamo recursivameente con el nuevo hijo y cambio al estado max con 1
                crear_sucesores_min_max(a, l_recuperar(a_hijos(a, n), l_ultima(a_hijos(a, n))), 1, alpha, beta,
                                        jugador_max, jugador_min);
                //se calcula el valor para beta
                mayor_valor_sucesor=MIN(mayor_valor_sucesor,hijoEstado->utilidad);
                beta = MIN(beta, mayor_valor_sucesor);
                estado->utilidad = beta;
                if (beta <= alpha) {
                    break;
                }
                posActual = posActual == l_ultima(sucesores) ? NULL : l_siguiente(sucesores, posActual);
            }


        }
    }
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
Computa el valor de utilidad correspondiente al estado E, y la ficha correspondiente al JUGADOR_MAX, retornado:
- IA_GANA_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX gan� la partida.
- IA_EMPATA_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX empat� la partida.
- IA_PIERDE_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX perdi� la partida.
- IA_NO_TERMINO en caso contrario.
**/
static int valor_utilidad(tEstado e, int jugador_max){
    int jugador_min=jugador_max==PART_JUGADOR_1?PART_GANA_JUGADOR_2:PART_JUGADOR_1;
    if(ganaIA(e,jugador_max)){
        return IA_GANA_MAX;
    }
    else{
        if(ganaIA(e,jugador_min)){
            return IA_PIERDE_MAX;
        }
        else{
            if(lleno(e)){
                return IA_EMPATA_MAX;
            }
            else{
                return IA_NO_TERMINO;
            }
        }
    }

}

/**
>>>>>  A IMPLEMENTAR   <<<<<
Computa y retorna una lista con aquellos estados que representan estados sucesores al estado E.
Un estado sucesor corresponde a la clonaci�n del estado E, junto con la incorporaci�n de un nuevo movimiento
realizado por el jugador cuya ficha es FICHA_JUGADOR por sobre una posici�n que se encuentra libre en el estado E.
La lista de estados sucesores se debe ordenar de forma aleatoria, de forma tal que una doble invocaci�n de la funci�n
estados_sucesores(estado, ficha) retornar�a dos listas L1 y L2 tal que:
- L1 y L2 tienen exactamente los mismos estados sucesores de ESTADO a partir de jugar FICHA.
- El orden de los estado en L1 posiblemente sea diferente al orden de los estados en L2.
**/
static tLista estados_sucesores(tEstado e, int ficha_jugador){
    tEstado toCreate;
    tLista list;
    tPosicion actual, fin;
    crear_lista(&list);
    int pos, size;
    srand(time(NULL));

    size = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (e->grilla[i][j] == PART_SIN_MOVIMIENTO) {
                size++;
                toCreate = clonar_estado(e);

                toCreate->grilla[i][j] = ficha_jugador;

                pos = rand() % size;
                actual = l_primera(list);
                fin = l_fin(list);

                while(pos != 0 && actual != fin) {
                    actual = l_siguiente(list, actual);
                    pos--;
                }

                l_insertar(list, actual, toCreate);
            }
        }
    }

    return list;
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
Inicializa y retorna un nuevo estado que resulta de la clonaci�n del estado E.
Para esto copia en el estado a retornar los valores actuales de la grilla del estado E, como su valor
de utilidad.
**/
static tEstado clonar_estado(tEstado e){
    int i,j;
    tEstado estadoN=(tEstado)malloc(sizeof(struct estado));
    if(estadoN==NULL){
        exit(PART_ERROR_MEMORIA);
    }
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            estadoN->grilla[i][j]=e->grilla[i][j];
        }
    }
    estadoN->utilidad=e->utilidad;
}

/**
Computa la diferencia existente entre dos estados.
Se asume que entre ambos existe s�lo una posici�n en el que la ficha del estado anterior y nuevo difiere.
La posici�n en la que los estados difiere, es retornada en los par�metros *X e *Y.
**/
static void diferencia_estados(tEstado anterior, tEstado nuevo, int * x, int * y){
    int i,j, hallado = 0;
    for(i=0; i<3 && !hallado; i++){
        for(j=0; j<3 && !hallado; j++){
            if (anterior->grilla[i][j] != nuevo->grilla[i][j]){
                *x = i;
                *y = j;
                hallado = 1;
            }
        }
    }
}

int ganaIA(tEstado estado,int jugador) {
    int gana = 0;
    if ((estado->grilla[0][0] == jugador && estado->grilla[1][1] == jugador && estado->grilla[2][2] == jugador) ||
        (estado->grilla[2][0] == jugador && estado->grilla[1][1] == jugador && estado->grilla[0][2] == jugador)) {
        gana = 1;
    }
    else {
        for(int i=0;i<3;i++){
            if((estado->grilla[i][0]==jugador && estado->grilla[i][1]==jugador && estado->grilla[i][2]==jugador) ||
               (estado->grilla[0][i]==jugador && estado->grilla[1][i]==jugador && estado->grilla[2][i]==jugador) ){
                    gana=1;
                    break;
            }
        }
    }

    return gana;
}
int lleno(tEstado estado){
    int lleno=1;
    for(int i=0;i<3 && lleno;i++){
        for(int j=0;j<3 && lleno;j++){
            if(estado->grilla[i][j]==PART_SIN_MOVIMIENTO){
                lleno=0;
            }
        }
    }
    return lleno;
}
int MAX(int v1,int v2){
    int ret;
    if(v1>=v2){
        ret=v1;
    }
    else{
        ret=v2;
    }
    return ret;
}
int MIN(int v1,int v2){
    int ret;
    if(v1>=v2){
        ret=v2;
    }
    else{
        ret=v1;
    }
    return ret;
}
