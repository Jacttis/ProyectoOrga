cmake_minimum_required(VERSION 3.14)
project(Proyecto C)

set(CMAKE_C_STANDARD 99)

add_executable(Proyecto TDAArbol/arbol.c TDAArbol/arbol.h TDAArbol/mainArbol.c TDALista/lista.h TDALista/TDALista.c)